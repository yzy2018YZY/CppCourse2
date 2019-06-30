//1850059 ��1�� ��־Զ

#include <iostream>
#include <cstdlib>
#include "12-b2-linear_list_DL.h"	//��ʽ����

using namespace std;

/* ���캯������ʼ�����Ա� */
template <class ElemType>
LinkList<ElemType>::LinkList()
{
	/* ����ͷ���ռ䣬��ֵ��ͷָ�� */
	head = new LNode<ElemType>;
	if (head == NULL)
		exit(MEMORY_OVERFLOW);

	head->next = NULL;
	head->prior = NULL;
}

/* ����������ɾ�����Ա� */
template <class ElemType>
LinkList<ElemType>::~LinkList()
{
	LNode<ElemType> *q, *p = head;

	/* ��ͷ��㿪ʼ�����ͷţ���ͷ��㣩 */
	while (p) 
	{    //������Ϊ�գ���ѭ����ִ��
		q = p->next; //ץס�������һ�����
		delete p;
		p = q;
	}

	head = NULL;	//ͷָ����NULL
}

/* ������Ա�����ͷ��㣩 */
template <class ElemType>
Status LinkList<ElemType>::ClearList()
{
	LNode<ElemType> *q, *p = head->next;

	/* ����Ԫ��㿪ʼ�����ͷ� */
	while (p) 
	{
		q = p->next;   //ץס�������һ�����
		delete p;
		p = q;
	}

	head->next = NULL;	//ͷ����next����NULL
	head->prior = NULL;	//ͷ����prior����NULL
	return OK;
}

/* �ж��Ƿ�Ϊ�ձ� */
template <class ElemType>
Status LinkList<ElemType>::ListEmpty()
{
	/* �ж�ͷ����next�򼴿� */
	if (head->next == NULL)
		return TRUE;
	else
		return FALSE;
}

/* ���ĳ��� */
template <class ElemType>
int LinkList<ElemType>::ListLength()
{
	LNode<ElemType> *p = head->next; //ָ����Ԫ���
	int    len = 0;

	/* ѭ�������������м��� */
	while (p) 
	{
		p = p->next;
		len++;
	}

	return len;
}

/* ȡ����Ԫ�� */
template <class ElemType>
Status LinkList<ElemType>::GetElem(int i, ElemType &e)
{
	LNode<ElemType> *p = head->next;	//ָ����Ԫ���
	int  pos = 1;		//��ʼλ��Ϊ1

	/* ����ΪNULL �� δ����i��Ԫ�� */
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

/* ���ҷ���ָ��������Ԫ�� */
template <class ElemType>
int LinkList<ElemType>::LocateElem(ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
	LNode<ElemType> *p = head->next;	//ָ����Ԫ���
	int  pos = 1;		//��ʼλ��Ϊ1

	/* ѭ����������  */
	while (p && (*compare)(e, p->data) == FALSE) 
	{
		p = p->next;
		pos++;
	}

	return (p) ? pos : 0;
}

/* ���ҷ���ָ��������Ԫ�ص�ǰ��Ԫ�� */
template <class ElemType>
Status LinkList<ElemType>::PriorElem(ElemType cur_e, ElemType &pre_e)
{
	LNode<ElemType> *p = head->next;	//ָ����Ԫ���

	if (p == NULL)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �ӵ�2����㿪ʼѭ����������(����Ƚ���ȣ���֤��ǰ��) */
	while (p->next && p->next->data != cur_e)
		p = p->next;

	if (p->next == NULL) //δ�ҵ�
		return ERROR;

	pre_e = p->data;
	return OK;
}

/* ���ҷ���ָ��������Ԫ�صĺ��Ԫ�� */
template <class ElemType>
Status LinkList<ElemType>::NextElem(ElemType cur_e, ElemType &next_e)
{
	LNode<ElemType> *p = head->next;  //��Ԫ���

	if (p == NULL)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �к�̽���ҵ�ǰ���ֵ����ʱ���� */
	while (p->next && p->data != cur_e)
		p = p->next;

	if (p->next == NULL)
		return ERROR;

	next_e = p->next->data;
	return OK;
}

/* ��ָ��λ��ǰ����һ����Ԫ�� */
template <class ElemType>
Status LinkList<ElemType>::ListInsert(int i, ElemType e)
{
	LNode<ElemType> *s, *p = head;	//pָ��ͷ���
	int   pos = 0;

	/* Ѱ�ҵ�i-1����� */
	while (p && pos < i - 1) {
		p = p->next;
		pos++;
	}

	if (p == NULL || pos > i)  //iֵ�Ƿ��򷵻�
		return ERROR;

	s = new LNode<ElemType>;
	if (s == NULL)
		return MEMORY_OVERFLOW;

	s->data = e; 	//�½��������ֵ
	s->next = p->next;	//�½���next�ǵ�i��
	s->prior = p;	//�½ڵ��prior�ǵ�i-1��
	if (p->next)
		p->next->prior = s;
	p->next = s;	//��i-1����next���½��

	return OK;
}

/* ɾ��ָ��λ�õ�Ԫ�أ�������ɾ��Ԫ�ص�ֵ����e�з��� */
template <class ElemType>
Status LinkList<ElemType>::ListDelete(int i, ElemType &e)
{
	LNode<ElemType> *q, *p = head;	//pָ��ͷ���
	int   pos = 0;

	/* Ѱ�ҵ�i����㣨p->next�ǵ�i����㣩 */
	while (p->next && pos < i - 1) {
		p = p->next;
		pos++;
	}

	if (p->next == NULL || pos > i - 1)	//iֵ�Ƿ��򷵻�
		return ERROR;

	//ִ�е��˱�ʾ�ҵ��˵�i����㣬��ʱpָ���i-1�����

	q = p->next;		//qָ���i�����
	p->next = q->next;	//��i-1������next��ָ���i+1��
	if (q->next)
		q->next->prior = p;	//��i+1���ڵ��prior��ָ���i-1��
	e = q->data;		//ȡ��i������ֵ
	delete q;			//�ͷŵ�i�����

	return OK;
}

/* �������Ա� */
template <class ElemType>
Status LinkList<ElemType>::ListTraverse(Status(*visit)(ElemType e))
{
	extern int line_count; //��main�ж���Ĵ�ӡ���м����������㷨�޹أ�
	LNode<ElemType> *p = head->next;

	line_count = 0;		//�������ָ���ʼֵ�����㷨�޹أ�
	while (p && (*visit)(p->data) == TRUE)
		p = p->next;

	cout << endl;	//����ӡһ�����У�ֻ��Ϊ�˺ÿ������㷨�޹�
	return OK;
}