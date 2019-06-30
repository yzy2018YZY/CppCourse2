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

Status compare(ElemType e1, ElemType e2)
{
	if (e1 == e2)
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

	(*L)->next = (*L);
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

/* 在指定位置前插入一个新元素 */
Status ListInsert(LinkList *L, int i, ElemType e)
{
	LinkList s, p = *L;	//p指向头结点
	int      pos = 0;

	if (i == 1)
		goto INSERT;

	/* 寻找第i-1个结点 */
	do 
	{
		p = p->next;
		pos++;
	} while (p != (*L) && pos < i - 1);

	if (p == (*L) || pos > i - 1)  //i值非法则返回
		return ERROR;

	//执行到此表示找到指定位置，p指向第i-1个结点
INSERT:
	s = (LinkList)malloc(sizeof(LNode));
	if (s == NULL)
		return LISTOVERFLOW;

	s->data = e; 	//新结点数据域赋值
	s->next = p->next;	//新结点的next是第i个
	p->next = s;	//第i-1个的next是新结点
	
	return OK;
}

/* 删除节点 */
Status ListDelete(LinkList L, LinkList *prior, LinkList *p)
{
	(*prior)->next = (*p)->next;	//删除p节点
	free((*p));
	(*p) = (*prior)->next;
	if ((*p) == L)	//忽略头结点
	{
		(*prior) = (*p);
		(*p) = (*p)->next;
	}
	return OK;
}

/* 向前k次，获取节点对应的指针 */
Status JumpList(LinkList L, int k, LinkList *prior, LinkList *p)
{
	int i;
	for (i = 0; i < k; i++)
	{
		(*prior) = (*p);
		(*p) = (*p)->next;
		if ((*p) == L)	//忽略头结点
		{
			(*prior) = (*p);
			(*p) = (*p)->next;
		}
	}
	return OK;
}

int main()
{
	LinkList L, p, q;
	int i, n, m, k;
	InitList(&L);
	printf("请输入n，m，k：\n");
	if (scanf("%d%d%d", &n, &m, &k) != 3 || n <= 0 || m <= 0 || k <= 0)
	{
		printf("输入错误\n");
		return 0;
	}
	for (i = n - 1; i >= 0; i--)	//插入数字
		ListInsert(&L, 1, i + 1);
	p = L->next;
	q = L;
	JumpList(L, (k - 1) % n, &q, &p);	//向前移动(k-1)%n次
	printf("出列顺序：\n");
	while (ListLength(L) > 1)	//直到只剩1人
	{
		JumpList(L, (m - 1) % n, &q, &p);	//跳过(m-1)%n人
		printf("%d\n", p->data);	//输出被删除的节点
		ListDelete(L, &q, &p);	//删除p节点
		n--;	//总人数变动
	}
	printf("%d\n", L->next->data);
	DestroyList(&L);
	return 0;
}