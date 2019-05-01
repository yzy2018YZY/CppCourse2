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
	LinkList p = L->next;	//指向首元

	while (p != L)	//遍历所有节点
	{
		printf("%d-%s-%c-%f-%s->\n", p->data->num, p->data->name, p->data->sex, p->data->score, p->data->addr);
		p = p->next;
	}

	return OK;
}

/*获取元素所在的指针，正数为正向计数，负数为反向计数*/
LinkList GetElemP_Dul(LinkList L, int i)
{
	LinkList p = L->next;	//指向首元结点
	int pos = 1;	//初始位置为1

	/* 链表不为NULL 且 未到第i个元素 */
	if (i >= 1)	//正向搜索
	{
		while (pos < i)
		{
			p = p->next;
			pos++;
		}
	}
	else		//逆向搜索
	{
		while (pos > i)
		{
			p = p->prior;
			pos--;
		}
	}

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

	if (!(p = GetElemP_Dul(*L, i)))	//在L中确定删除位置
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
	ET       e[] = { {1001, "张三", 'M', 76.5, "上海市杨浦区"},
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
	for (i = 5; i >= 0; i--)
		ListInsert_Dul(&L, 1, e + i);

	ListTraverse(L);
	while (ListLength(L) > 0)	//链表为空时退出
	{
		printf("请输入要删除数据的学号，错误的输入会退出：\n");
		if (scanf("%d", &num) != 1) //输入错误的数字时退出
			break;
		e1->num = num;
		if ((i = LocateElem(L, e1, compare)) > 0)	//删除节点
		{
			printf("%d\n", i);
			ListDelete_Dul(&L, i, e1);
			printf("删除%d完成\n", num);
			ListTraverse(L);
		}
		else	//没有找到节点
		{
			printf("没有找到%d\n", num);
		}
	}

	free(e1);
	printf("销毁链表\n");
	DestroyList(&L);
	return 0;
}