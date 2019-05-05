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
} ElemType;

typedef struct LNode {
	ElemType      data;		//存放数据
	struct LNode *prior;	//存放前驱的指针
	struct LNode *next;		//存放后继的指针
} LNode, *LinkList;

/* 初始化线性表 */
Status InitList(LinkList *L)
{
	/* 申请头结点空间，赋值给头指针 */
	*L = (LNode *)malloc(sizeof(LNode));
	if (*L == NULL)
		exit(LISTOVERFLOW);

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
		q = p->next; //抓住链表的下一个结点，若空表则q直接为NULL
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

/* 遍历线性表 */
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;	//指向首元

	while (p != L)	//遍历所有节点
	{
		printf("%d-%s-%c-%f-%s->\n", p->data.num, p->data.name, p->data.sex, p->data.score, p->data.addr);
		p = p->next;
	}
	
	return OK;
}

/*获取元素所在的指针，正数为正向计数，负数为反向计数*/
LinkList GetElemP_Dul(LinkList L, int i)
{
	LinkList p = L->next;	//指向首元结点
	int pos = 1;			//初始位置为1

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
Status ListInsert_Dul(LinkList *L, int i, ElemType *e)
{
	LinkList p, s;
	if (!(p = GetElemP_Dul(*L, i)))	//在L中确定插入位置
		return ERROR;	//插入位置不合法
	if (!(s = (LinkList)malloc(sizeof(LNode))))
		return LISTOVERFLOW;
	memcpy(&(s->data), e, sizeof(ElemType));
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return OK;
}

int main()
{
	char tempStr[100] = "";
	srand((unsigned int)time(0));
	ElemType s1;
	LinkList L;
	InitList(&L);
	
	printf("请输入要插入的元素（学号、姓名、性别、分数、地址），错误的输入会退出（例如学号输入了abc）\n");
	while (scanf("%d%s%s%f%s", &s1.num, s1.name, tempStr, &s1.score, &s1.addr) == 5)
	{
		s1.sex = tempStr[0];
		printf("在首元之前插入：\n");
		ListInsert_Dul(&L, 0, &s1);
		ListTraverse(L);
		int ran = rand() % ListLength(L) + 1;
		printf("在中间(%d)插入：\n", ran);
		ListInsert_Dul(&L, ran, &s1);
		ListTraverse(L);
		printf("在尾节点(%d)后插入：\n", ListLength(L));
		ListInsert_Dul(&L, ListLength(L) + 1, &s1);
		ListTraverse(L);
		printf("请输入要插入的元素（学号、姓名、性别、分数、地址），错误的输入会退出（例如学号输入了abc）：\n");
	}

	printf("销毁链表\n");
	DestroyList(&L);
	return 0;
}