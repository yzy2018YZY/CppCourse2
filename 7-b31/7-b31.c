//1850059 计1班 杨志远

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
#include <Windows.h>
#else
#include <unistd.h>		//exit函数
#endif

#define MAX_NUM_PER_LINE 10

#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define LISTOVERFLOW	-2

typedef int Status;
typedef int ElemType;

typedef struct LNode {
	ElemType      data;	//存放数据
	struct LNode *next;	//存放后继的指针
} LNode, *LinkList;


/* 初始化线性表 */
Status InitList(LinkList *L)
{
	/* 申请头结点空间，赋值给头指针 */
	*L = (LNode *)malloc(sizeof(LNode));
	if (*L == NULL)
		exit(LISTOVERFLOW);

	(*L)->next = NULL;
	return OK;
}

/* 删除线性表 */
Status DestroyList(LinkList *L)
{
	LinkList q, p = *L;	//指向首元

	/* 整个链表(含头结点)依次释放 */
	while (p)	//若链表为空，则循环不执行
	{    
		q = p->next;	//抓住链表的下一个结点
		free(p);
		p = q;
	}

	*L = NULL;	//头指针置NULL
	return OK;
}

/* 遍历线性表 */
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;	//指向首元
	int lineCount = 0;

	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
		lineCount++;
		if ((lineCount) % MAX_NUM_PER_LINE == 0)	//输出数字满一定数目时回车
			printf("\n");
	}
		
	if (p)
		return ERROR;

	if ((lineCount) % MAX_NUM_PER_LINE != 0)	//补齐回车
		printf("\n");
	return OK;
}

Status SetCreate(LinkList *L)
{
	InitList(L);
	ElemType e;
	while (scanf("%d", &e) == 1)
	{
		if (e == -1)	//退出
			break;
		else
		{
			LinkList p = (*L);	//指向首节点非首元节点
			while (p->next)		//p不是最后一个节点
			{
				if (p->data == e)	//出现重复元素，不符合集合定义
				{
					p = NULL;
					break;
				}
				p = p->next;
			}
			if (p && p->data != e)	//尾节点特殊处理
			{
				LinkList q = (LinkList)malloc(sizeof(LNode));
				q->next = NULL;
				q->data = e;
				p->next = q;
			}
		}
	}
	return OK;
}

Status SetDifference(LinkList La, LinkList Lb)
{
	LinkList b = Lb->next;
	while (b)	//遍历Lb
	{
		LinkList p = La->next, q = La;
		while (p->next)
		{
			if (p->data == b->data)	//检查是否有重复元素
				break;
			q = p;
			p = p->next;
		}
		if (p->data == b->data)	//在La中删除重复元素
		{
			q->next = p->next;
			free(p);
		}
		else	//向La中添加新元素
		{
			LinkList t = (LinkList)malloc(sizeof(LNode));
			t->next = NULL;
			t->data = b->data;
			p->next = t;
		}
		b = b->next;
	}
	return OK;
}

int main()
{
	LinkList La, Lb;
	printf("请输入集合A的各个元素，用空格隔开，-1结束：\n");
	SetCreate(&La);
	printf("请输入集合B的各个元素，用空格隔开，-1结束：\n");
	SetCreate(&Lb);
	printf("集合A中的元素为：\n");
	ListTraverse(La);
	printf("集合B中的元素为：\n");
	ListTraverse(Lb);
	SetDifference(La, Lb);
	printf("计算后的集合为：\n");
	ListTraverse(La);
	DestroyList(&La);
	DestroyList(&Lb);
	return 0;
}