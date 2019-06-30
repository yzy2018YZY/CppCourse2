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
	struct LNode *prior;//存放前驱的指针
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

	(*L)->prior = (*L);
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

	(*L) = NULL;	//头结点置NULL
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
	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return OK;
}

/* 删除节点 */
Status ListDelete(LinkList L, LinkList *p)
{
	LinkList prior = (*p)->prior, next = (*p)->next;
	prior->next = (*p)->next;
	next->prior = (*p)->prior;
	free(*p);
	if (prior == L)	//忽略头结点
		(*p) = prior->prior;
	else
		(*p) = prior;
	return OK;
}

/* 向前k次，获取节点对应的指针 */
Status JumpList(LinkList L, int k, LinkList *p)
{
	int i;
	for (i = 0; i < k; i++)
	{
		(*p) = (*p)->prior;
		if ((*p) == L)	//忽略头结点
			(*p) = (*p)->prior;
	}
	return OK;
}

int main()
{
	LinkList L, p;
	InitList(&L);
	int i, n, m, k;
	printf("请输入n，m，k：\n");
	if (scanf("%d%d%d", &n, &m, &k) != 3 || n <= 0 || m <= 0 || k <= 0)
	{
		printf("输入错误\n");
		return 0;
	}
	for (i = 0; i < n; i++)	//插入数字
		ListInsert_Dul(&L, 1, i + 1);
	p = L->prior;
	JumpList(L, (k - 1) % n, &p);	//向前移动(k-1)%n次
	printf("出列顺序：\n");
	while (ListLength(L) > 1)	//直到只剩1人
	{
		JumpList(L, (m - 1) % n, &p);	//跳过(m-1)%n人
		printf("%d\n", p->data);	//输出被删除的节点
		ListDelete(L, &p);	//删除p节点
		n--;	//总人数变动
	}
	printf("%d\n", L->prior->data);
	DestroyList(&L);
	return 0;
}