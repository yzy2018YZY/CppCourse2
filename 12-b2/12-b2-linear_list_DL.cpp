//1850059 计1班 杨志远

#include <iostream>
#include <cstdlib>
#include "12-b2-linear_list_DL.h"	//形式定义

using namespace std;

/* 构造函数（初始化线性表） */
template <class ElemType>
LinkList<ElemType>::LinkList()
{
	/* 申请头结点空间，赋值给头指针 */
	head = new LNode<ElemType>;
	if (head == NULL)
		exit(MEMORY_OVERFLOW);

	head->next = NULL;
	head->prior = NULL;
}

/* 析构函数（删除线性表） */
template <class ElemType>
LinkList<ElemType>::~LinkList()
{
	LNode<ElemType> *q, *p = head;

	/* 从头结点开始依次释放（含头结点） */
	while (p) 
	{    //若链表为空，则循环不执行
		q = p->next; //抓住链表的下一个结点
		delete p;
		p = q;
	}

	head = NULL;	//头指针置NULL
}

/* 清除线性表（保留头结点） */
template <class ElemType>
Status LinkList<ElemType>::ClearList()
{
	LNode<ElemType> *q, *p = head->next;

	/* 从首元结点开始依次释放 */
	while (p) 
	{
		q = p->next;   //抓住链表的下一个结点
		delete p;
		p = q;
	}

	head->next = NULL;	//头结点的next域置NULL
	head->prior = NULL;	//头结点的prior域置NULL
	return OK;
}

/* 判断是否为空表 */
template <class ElemType>
Status LinkList<ElemType>::ListEmpty()
{
	/* 判断头结点的next域即可 */
	if (head->next == NULL)
		return TRUE;
	else
		return FALSE;
}

/* 求表的长度 */
template <class ElemType>
int LinkList<ElemType>::ListLength()
{
	LNode<ElemType> *p = head->next; //指向首元结点
	int    len = 0;

	/* 循环整个链表，进行计数 */
	while (p) 
	{
		p = p->next;
		len++;
	}

	return len;
}

/* 取表中元素 */
template <class ElemType>
Status LinkList<ElemType>::GetElem(int i, ElemType &e)
{
	LNode<ElemType> *p = head->next;	//指向首元结点
	int  pos = 1;		//初始位置为1

	/* 链表不为NULL 且 未到第i个元素 */
	while (p != NULL && pos < i) 
	{
		p = p->next;
		pos++;
	}

	if (p == NULL || pos > i)
		return ERROR;

	e = p->data;
	return OK;
}

/* 查找符合指定条件的元素 */
template <class ElemType>
int LinkList<ElemType>::LocateElem(ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
	LNode<ElemType> *p = head->next;	//指向首元结点
	int  pos = 1;		//初始位置为1

	/* 循环整个链表  */
	while (p && (*compare)(e, p->data) == FALSE) 
	{
		p = p->next;
		pos++;
	}

	return (p) ? pos : 0;
}

/* 查找符合指定条件的元素的前驱元素 */
template <class ElemType>
Status LinkList<ElemType>::PriorElem(ElemType cur_e, ElemType &pre_e)
{
	LNode<ElemType> *p = head->next;	//指向首元结点

	if (p == NULL)	//空表直接返回
		return ERROR;

	/* 从第2个结点开始循环整个链表(如果比较相等，保证有前驱) */
	while (p->next && p->next->data != cur_e)
		p = p->next;

	if (p->next == NULL) //未找到
		return ERROR;

	pre_e = p->data;
	return OK;
}

/* 查找符合指定条件的元素的后继元素 */
template <class ElemType>
Status LinkList<ElemType>::NextElem(ElemType cur_e, ElemType &next_e)
{
	LNode<ElemType> *p = head->next;  //首元结点

	if (p == NULL)	//空表直接返回
		return ERROR;

	/* 有后继结点且当前结点值不等时继续 */
	while (p->next && p->data != cur_e)
		p = p->next;

	if (p->next == NULL)
		return ERROR;

	next_e = p->next->data;
	return OK;
}

/* 在指定位置前插入一个新元素 */
template <class ElemType>
Status LinkList<ElemType>::ListInsert(int i, ElemType e)
{
	LNode<ElemType> *s, *p = head;	//p指向头结点
	int   pos = 0;

	/* 寻找第i-1个结点 */
	while (p && pos < i - 1) {
		p = p->next;
		pos++;
	}

	if (p == NULL || pos > i)  //i值非法则返回
		return ERROR;

	s = new LNode<ElemType>;
	if (s == NULL)
		return MEMORY_OVERFLOW;

	s->data = e; 	//新结点数据域赋值
	s->next = p->next;	//新结点的next是第i个
	s->prior = p;	//新节点的prior是第i-1个
	if (p->next)
		p->next->prior = s;
	p->next = s;	//第i-1个的next是新结点

	return OK;
}

/* 删除指定位置的元素，并将被删除元素的值放入e中返回 */
template <class ElemType>
Status LinkList<ElemType>::ListDelete(int i, ElemType &e)
{
	LNode<ElemType> *q, *p = head;	//p指向头结点
	int   pos = 0;

	/* 寻找第i个结点（p->next是第i个结点） */
	while (p->next && pos < i - 1) {
		p = p->next;
		pos++;
	}

	if (p->next == NULL || pos > i - 1)	//i值非法则返回
		return ERROR;

	//执行到此表示找到了第i个结点，此时p指向第i-1个结点

	q = p->next;		//q指向第i个结点
	p->next = q->next;	//第i-1个结点的next域指向第i+1个
	if (q->next)
		q->next->prior = p;	//第i+1个节点的prior域指向第i-1个
	e = q->data;		//取第i个结点的值
	delete q;			//释放第i个结点

	return OK;
}

/* 遍历线性表 */
template <class ElemType>
Status LinkList<ElemType>::ListTraverse(Status(*visit)(ElemType e))
{
	extern int line_count; //在main中定义的打印换行计数器（与算法无关）
	LNode<ElemType> *p = head->next;

	line_count = 0;		//计数器恢复初始值（与算法无关）
	while (p && (*visit)(p->data) == TRUE)
		p = p->next;

	cout << endl;	//最后打印一个换行，只是为了好看，与算法无关
	return OK;
}