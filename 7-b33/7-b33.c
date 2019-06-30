//1850059 计1班 杨志远

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _MSC_VER
#include <Windows.h>
#else
#include <unistd.h>		//exit函数
#endif

#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define LISTOVERFLOW	-2

typedef int Status;
typedef struct student {
	int   num;
	char  name[10];
	char  sex;
	float score;
	char  addr[30];
} ET, *ElemType;

typedef struct LNode {
	ElemType      data;		//存放数据
	struct LNode *prior;	//存放前驱的指针
	struct LNode *next;		//存放后继的指针
} LNode, *LinkList;

Status compare(ElemType e1, ElemType e2)
{
	if (e1->num == e2->num)
		return TRUE;
	else
		return FALSE;
}

/* 初始化线性表 */
Status InitList(LinkList *L)
{
	/* 申请头结点空间，赋值给头指针 */
	*L = (LNode *)malloc(sizeof(LNode));
	if (*L == NULL)
		exit(LISTOVERFLOW);
	
	(*L)->data = NULL;	//头结点不存储数据
	(*L)->next = (*L);	//头结点的next指向自己
	(*L)->prior = (*L);	//头结点的prior指向自己
	return OK;
}

/* 删除线性表 */
Status DestroyList(LinkList *L)
{
	LinkList q, p = *L; //指向首元

	/* 整个链表(含头结点)依次释放
	   不能用while循环 */
	do
	{
		q = p->next;	//抓住链表的下一个结点，若空表则q直接为NULL
		if (p->data)	//二次释放非头结点的数据
			free(p->data);
		free(p);
		p = q;
	} while (p != (*L));   //若链表为空，则循环不执行

	(*L) = NULL;	//头结点的next置NULL
	return OK;
}

/* 求表的长度 */
int ListLength(LinkList L)
{
	LinkList p = L->next; //指向首元结点
	int len = 0;

	/* 循环整个链表，进行计数 */
	while (p != L)
	{
		p = p->next;
		len++;
	}

	return len;
}

/* 查找符合指定条件的元素 */
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
	LinkList p = L->next;	//首元结点(链表为空时值就是L)
	int    pos = 1;		//初始位置

	/* 循环整个链表  */
	while (p != L && (*compare)(e, p->data) == FALSE) 
	{
		p = p->next;
		pos++;
	}

	return (p != L) ? pos : 0;
}

/* 遍历线性表 */
Status ListTraverse(LinkList L)
{
	LinkList p = L->prior;	//指向首元

	while (p != L)	//遍历所有节点
	{
		printf("%d-%s-%c-%f-%s->\n", p->data->num, p->data->name, p->data->sex, p->data->score, p->data->addr);
		p = p->prior;
	}

	return OK;
}

/*获取元素所在的指针*/
LinkList GetElemP_Dul(LinkList L, int i)
{
	if (L == 0 || i <= 0)	//链表不能为NULL并且i需要大于0
		return NULL;
	LinkList p = L->prior;	//指向首元结点
	int pos = 1;			//初始位置为1

	while (pos < i && p != L)	//未到第i个元素并且未到达末尾
	{
		p = p->prior;
		pos++;
	}

	if (pos < i && p == L)	//i超出了范围
		return NULL;
	else
		return p;
}

/*在指定位置插入元素，正数为正向计数，负数为反向计数*/
Status ListInsert_Dul(LinkList *L, int i, ElemType e)
{
	LinkList p, s;

	if (!(p = GetElemP_Dul(*L, i)))	//在L中确定插入位置
		return ERROR;	//插入位置不合法

	if (!(s = (LinkList)malloc(sizeof(LNode))))
		return LISTOVERFLOW;
	if (!(s->data = (ElemType)malloc(sizeof(ET))))
		return LISTOVERFLOW;
	memcpy(s->data, e, sizeof(ET));	//复制数据

	s->prior = p->prior;	//添加节点
	p->prior->next = s;
	s->next = p;
	p->prior = s;

	return OK;
}

Status ListDelete_Dul(LinkList *L, int i, ElemType e)
{
	LinkList p = (*L)->next;

	if (!(p = GetElemP_Dul(*L, i)) || p == *L)	//在L中确定删除位置，这里与书上的实现不同，需要考虑到i的范围问题（2.18与2.19的i范围不同），不能删除头结点
		return ERROR;

	memcpy(e, p->data, sizeof(ET));	//复制数据
	p->prior->next = p->next;		//删除节点
	p->next->prior = p->prior;
	free(p->data);
	free(p);

	return OK;
}

int main()
{
	char tempStr[100] = "";
	ET       e[] = { 
		  {1001, "张三", 'M', 76.5, "上海市杨浦区"},
		  {1002, "李四", 'F', 87, "上海市普陀区"},
		  {1003, "王五", 'M', 80, "浙江省杭州市"},
		  {1004, "赵六", 'M', 54, "浙江省绍兴市"},
		  {1005, "牛七", 'F', 85, "江苏省南京市"},
		  {1006, "马八", 'M', 60, "江苏省苏州市"} };
	ElemType e1;
	LinkList L;
	InitList(&L);
	e1 = (ElemType)malloc(sizeof(ET));
	int i, num;
	for (i = sizeof(e) / sizeof(ET) - 1; i >= 0; i--)
		ListInsert_Dul(&L, ListLength(L) + 1, e + i);

	ListTraverse(L);
	while (ListLength(L) > 0)	//链表为空时退出
	{
		printf("\n删除首元元素\n");
		if (ListDelete_Dul(&L, 1, e1))
			printf("删除首元元素完成\n");
		else
			printf("首元元素不存在\n");
		if (ListLength(L) <= 0)
			break;
		ListTraverse(L);
		printf("\n请输入要删除数据的序号（注意逆序），错误的输入会退出（例如输入了abc）：\n");
		if (scanf("%d", &num) != 1)	//输入错误的数字时退出
			break;
		if (ListDelete_Dul(&L, num, e1))
			printf("删除第%d个元素完成\n", num);
		else
			printf("第%d个元素不存在\n", num);
		if (ListLength(L) <= 0)
			break;
		ListTraverse(L);
		printf("\n删除末尾元素\n");
		if (ListDelete_Dul(&L, ListLength(L), e1))
			printf("删除末尾元素完成\n");
		else
			printf("末尾元素不存在\n");
		ListTraverse(L);
	}

	free(e1);
	printf("\n销毁链表\n");
	DestroyList(&L);
	return 0;
}