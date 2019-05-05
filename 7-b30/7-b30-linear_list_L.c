//1850059 ��1�� ��־Զ

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>		//malloc/realloc����
#include <math.h>               //fabs����
#include <string.h>		//strcpy/strcmp�Ⱥ���
#include "7-b30-linear_list_L.h"	//��ʽ����

#ifdef _MSC_VER
#include <Windows.h>
#else
#include <unistd.h>		//exit����
#endif

/* ��ʼ�����Ա� */
Status InitList(LinkList *L)
{
	*L = NULL;  //ͷָ��ֱ�Ӹ�NULL
	return OK;
}

/* ɾ�����Ա� */
Status DestroyList(LinkList *L)
{
	LinkList q, p = *L; //ָ����Ԫ

	/* ����ָ��������Ҫ�ͷŶ����ռ� */
#if defined (ELEMTYPE_IS_CHAR_P) || defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
	/* �����ͷŶ����ռ� */
	while (p)
	{
		q = p->next;
		free(p->data);
		p = q;
	}
#endif

	p = *L; //ָ����Ԫ
	/* ��������(��ͷ���)�����ͷ� */
	while (p) //������Ϊ�գ���ѭ����ִ��
	{
		q = p->next; //ץס�������һ�����
		free(p);
		p = q;
	}

	*L = NULL;	//ͷָ����NULL
	return OK;
}

/* ������Ա���DestroyList��ȫ��ͬ�� */
Status ClearList(LinkList *L)
{
	LinkList q, p = *L; //ָ���׽ڵ�

	p = *L; //ָ���׽ڵ�
	/* ��������(��ͷ���)�����ͷ� */
	while (p) //������Ϊ�գ���ѭ����ִ��
	{
		q = p->next; //ץס�������һ�����
#if defined (ELEMTYPE_IS_CHAR_P) || defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
		free(p->data);/* ����ָ��������Ҫ�ͷŶ����ռ� */
#endif
		free(p);
		p = q;
	}

	*L = NULL; //ͷָ����NULL
	return OK;
}

/* �ж��Ƿ�Ϊ�ձ� */
Status ListEmpty(LinkList L)
{
	/* �ж�ͷָ�뼴�� */
	if (L == NULL)
		return TRUE;
	else
		return FALSE;
}

/* ���ĳ��� */
int ListLength(LinkList L)
{
	LinkList p = L; //ָ����Ԫ���
	int len = 0;

	/* ѭ�������������м��� */
	while (p)
	{
		p = p->next;
		len++;
	}

	return len;
}

/* ȡ����Ԫ�� */
Status GetElem(LinkList L, int i, ElemType *e)
{
	LinkList p = L;	//ָ����Ԫ���
	int    pos = 1;		//��ʼλ��Ϊ1

	/* ����ΪNULL �� δ����i��Ԫ�� */
	while (p != NULL && pos < i)
	{
		p = p->next;
		pos++;
	}

	if (!p || pos > i)
		return ERROR;

#if defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
	strcpy(*e, (p->data));
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
	memcpy(e, &(p->data), sizeof(ElemType));
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
	memcpy(*e, (p->data), sizeof(ET));
#else	//int��double
	*e = p->data;
#endif

	return OK;
}

/* ���ҷ���ָ��������Ԫ�� */
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
	LinkList p = L;		//��Ԫ���
	int    pos = 1;		//��ʼλ��

	/* ѭ����������  */
	while (p && (*compare)(e, p->data) == FALSE)
	{
		p = p->next;
		pos++;
	}

	return p ? pos : 0;
}

/* ���ҷ���ָ��������Ԫ�ص�ǰ��Ԫ�� */
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e)
{
	LinkList p = L;	//ָ����Ԫ���

	if (p == NULL)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �ӵ�2����㿪ʼѭ����������(����Ƚ���ȣ���֤��ǰ��) */
#ifdef ELEMTYPE_IS_DOUBLE
	while (p->next && fabs(p->next->data - cur_e) >= 1e-6)
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
	while (p->next && strcmp(p->next->data, cur_e))
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
	while (p->next &&  p->next->data.num != cur_e.num)
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
	while (p->next && p->next->data->num != cur_e->num)
#else	//ȱʡ����int����
	while (p->next && p->next->data != cur_e)
#endif
		p = p->next;

	if (p->next == NULL) //δ�ҵ�
		return ERROR;

#if defined (ELEMTYPE_IS_CHAR_ARRAY) || defined(ELEMTYPE_IS_CHAR_P)
	strcpy(*pre_e, p->data);	//ȡǰ��Ԫ�ص�ֵ
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
	memcpy(pre_e, &(p->data), sizeof(ElemType));	//ȡǰ��Ԫ�ص�ֵ
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
	memcpy(*pre_e, p->data, sizeof(ET));	//ȡǰ��Ԫ�ص�ֵ
#else	//int��doubleֱ�Ӹ�ֵ
	*pre_e = p->data;	//ȡǰ��Ԫ�ص�ֵ
#endif

	return OK;
}

/* ���ҷ���ָ��������Ԫ�صĺ��Ԫ�� */
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e)
{
	LinkList p = L;	//ָ����Ԫ���

	if (p == NULL)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �к�̽���ҵ�ǰ���ֵ����ʱ���� */
#ifdef ELEMTYPE_IS_DOUBLE
	while (p->next && fabs(p->data - cur_e) >= 1e-6)
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
	while (p->next && strcmp(p->data, cur_e))
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
	while (p->next && p->data.num != cur_e.num)
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
	while (p->next && p->data->num != cur_e->num)
#else	//ȱʡ����int����
	while (p->next && p->data != cur_e)
#endif
		p = p->next;

	if (p->next == NULL) //δ�ҵ�
		return ERROR;

#if defined (ELEMTYPE_IS_CHAR_ARRAY) || defined(ELEMTYPE_IS_CHAR_P)
	strcpy(*next_e, p->next->data);	//ȡ���Ԫ�ص�ֵ
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
	memcpy(next_e, &(p->next->data), sizeof(ElemType));	//ȡ���Ԫ�ص�ֵ
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
	memcpy(*next_e, p->next->data, sizeof(ET));	//ȡ���Ԫ�ص�ֵ
#else	//int��doubleֱ�Ӹ�ֵ
	*next_e = p->next->data;	//ȡ���Ԫ�ص�ֵ
#endif

	return OK;
}

/* ��ָ��λ��ǰ����һ����Ԫ�� */
Status ListInsert(LinkList *L, int i, ElemType e)
{
	LinkList s, p = *L;	//pָ����Ԫ���(����ΪNULL)
	int      pos = 1;	//��Ϊp��ָ����Ԫ������ʼλ����1

	/* ����½���Ϊ��Ԫ������Ҫ�ı�L��ֵ������λ�ò�����L���� */
	if (i != 1)
	{
		/* Ѱ�ҵ�i-1����� */
		while (p && pos < i - 1)
		{
			p = p->next;
			pos++;
		}

		if (p == NULL || pos > i - 1)  //iֵ�Ƿ��򷵻�
			return ERROR;
	}

	//ִ�е��˱�ʾ�ҵ�ָ��λ�ã�pָ���i-1�����

	s = (LinkList)malloc(sizeof(LNode));
	if (s == NULL)
		return LISTOVERFLOW;

#if defined (ELEMTYPE_IS_CHAR_ARRAY)
	strcpy(s->data, e);	//�½��������ֵ
#elif defined(ELEMTYPE_IS_CHAR_P)
	s->data = (ElemType)malloc((strlen(e) + 1) * sizeof(char));	//�ڲ�ָ����������ڴ�
	if (s->data == NULL)
		return LISTOVERFLOW;
	strcpy(s->data, e);	//�½��������ֵ
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
	memcpy(&s->data, &e, sizeof(ElemType));	//�½��������ֵ
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
	s->data = (ElemType)malloc(sizeof(ET));	//�ڲ�ָ����������ڴ�
	if (s->data == NULL)
		return LISTOVERFLOW;
	memcpy(s->data, e, sizeof(ET));	//�½��������ֵ
#else	//int��doubleֱ�Ӹ�ֵ
	s->data = e;	//�½��������ֵ
#endif

	if (i != 1)	//����λ�÷���Ԫ����ʱpָ���i-1�����
	{
		s->next = p->next;	//�½���next��p->next
		p->next = s;		//��i-1����next���½��
	}
	else		//����λ������Ԫ
	{
		s->next = p;	//��ʱp����L������L=NULL�������
		*L = s;			//ͷָ��ָ���½��
	}

	return OK;
}

/* ɾ��ָ��λ�õ�Ԫ�أ�������ɾ��Ԫ�ص�ֵ����e�з��� */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	LinkList q, p = *L;	//pָ����Ԫ���(����ΪNULL)
	int      pos = 1;	//��Ϊp��ָ����Ԫ������ʼλ����1

	/* ���ɾ���Ĳ�����Ԫ������ҵ�i����� */
	if (i != 1)
	{
		/* Ѱ�ҵ�i����㣨p->next�ǵ�i����㣩 */
		while (p->next && pos < i - 1)
		{
			p = p->next;
			pos++;
		}

		if (p == NULL || pos > i - 1)	//iֵ�Ƿ��򷵻�
			return ERROR;

		q = p->next;       //qָ���i�����
		p->next = q->next; //��i-1������next��ָ���i+1��
	}
	else	//Ҫɾ��������Ԫ
	{ 
		q = p;
		*L = q->next;	//���ֻ��һ����㣬��q->nextΪNULL
	}


#if defined (ELEMTYPE_IS_CHAR_ARRAY) || defined(ELEMTYPE_IS_CHAR_P)
	strcpy(*e, q->data);	//ȡ��i������ֵ
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
	memcpy(e, &(q->data), sizeof(ElemType));	//ȡ��i������ֵ
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
	memcpy(*e, q->data, sizeof(ET));	//ȡ��i������ֵ
#else	//int��doubleֱ�Ӹ�ֵ
	*e = q->data;	//ȡ��i������ֵ
#endif
	free(q);           //�ͷŵ�i�����

	return OK;
}

/* �������Ա� */
Status ListTraverse(LinkList L, Status(*visit)(ElemType e))
{
	extern int line_count; //��main�ж���Ĵ�ӡ���м����������㷨�޹أ�
	LinkList p = L;

	line_count = 0;		//�������ָ���ʼֵ�����㷨�޹أ�
	while (p && (*visit)(p->data) == TRUE)
		p = p->next;

	if (p)
		return ERROR;

	printf("\n");//����ӡһ�����У�ֻ��Ϊ�˺ÿ������㷨�޹�
	return OK;
}
