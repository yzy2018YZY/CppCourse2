//1850059 ��1�� ��־Զ

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
#include <Windows.h>
#else
#include <unistd.h>		//exit����
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
	ElemType      data;	//�������
	struct LNode *prior;//���ǰ����ָ��
	struct LNode *next;	//��ź�̵�ָ��
} LNode, *LinkList;

Status compare(ElemType e1, ElemType e2)
{
	if (e1 == e2)
		return TRUE;
	else
		return FALSE;
}

/* ��ʼ�����Ա� */
Status InitList(LinkList *L)
{
	/* ����ͷ���ռ䣬��ֵ��ͷָ�� */
	*L = (LNode *)malloc(sizeof(LNode));
	if (*L == NULL)
		exit(LISTOVERFLOW);

	(*L)->prior = (*L);
	(*L)->next = (*L);
	return OK;
}

/* ɾ�����Ա� */
Status DestroyList(LinkList *L)
{
	LinkList q, p = *L; //ָ����Ԫ

	/* ��������(��ͷ���)�����ͷ�
	   ������whileѭ�� */
	do
	{
		q = p->next; //ץס�������һ����㣬���ձ���qֱ��ΪNULL
		free(p);
		p = q;
	} while (p != (*L));   //������Ϊ�գ���ѭ����ִ��

	(*L) = NULL;	//ͷ�����NULL
	return OK;
}

/* ���ĳ��� */
int ListLength(LinkList L)
{
	LinkList p = L->next; //ָ����Ԫ���
	int len = 0;

	/* ѭ�������������м��� */
	while (p != L)
	{
		p = p->next;
		len++;
	}

	return len;
}

/*��ȡԪ�����ڵ�ָ�룬����Ϊ�������������Ϊ�������*/
LinkList GetElemP_Dul(LinkList L, int i)
{
	LinkList p = L->next;	//ָ����Ԫ���
	int pos = 1;	//��ʼλ��Ϊ1

	/* ����ΪNULL �� δ����i��Ԫ�� */
	if (i >= 1)	//��������
	{
		while (pos < i)
		{
			p = p->next;
			pos++;
		}
	}
	else		//��������
	{
		while (pos > i)
		{
			p = p->prior;
			pos--;
		}
	}

	return p;
}

/*��ָ��λ�ò���Ԫ�أ�����Ϊ�������������Ϊ�������*/
Status ListInsert_Dul(LinkList *L, int i, ElemType e)
{
	LinkList p, s;
	if (!(p = GetElemP_Dul(*L, i)))	//��L��ȷ������λ��
		return ERROR;	//����λ�ò��Ϸ�
	if (!(s = (LinkList)malloc(sizeof(LNode))))
		return LISTOVERFLOW;
	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return OK;
}

/* ɾ���ڵ� */
Status ListDelete(LinkList L, LinkList *p)
{
	LinkList prior = (*p)->prior, next = (*p)->next;
	prior->next = (*p)->next;
	next->prior = (*p)->prior;
	free(*p);
	if (prior == L)	//����ͷ���
		(*p) = prior->prior;
	else
		(*p) = prior;
	return OK;
}

/* ��ǰk�Σ���ȡ�ڵ��Ӧ��ָ�� */
Status JumpList(LinkList L, int k, LinkList *p)
{
	int i;
	for (i = 0; i < k; i++)
	{
		(*p) = (*p)->prior;
		if ((*p) == L)	//����ͷ���
			(*p) = (*p)->prior;
	}
	return OK;
}

int main()
{
	LinkList L, p;
	InitList(&L);
	int i, n, m, k;
	printf("������n��m��k��\n");
	if (scanf("%d%d%d", &n, &m, &k) != 3 || n <= 0 || m <= 0 || k <= 0)
	{
		printf("�������\n");
		return 0;
	}
	for (i = 0; i < n; i++)	//��������
		ListInsert_Dul(&L, 1, i + 1);
	p = L->prior;
	JumpList(L, (k - 1) % n, &p);	//��ǰ�ƶ�(k-1)%n��
	printf("����˳��\n");
	while (ListLength(L) > 1)	//ֱ��ֻʣ1��
	{
		JumpList(L, (m - 1) % n, &p);	//����(m-1)%n��
		printf("%d\n", p->data);	//�����ɾ���Ľڵ�
		ListDelete(L, &p);	//ɾ��p�ڵ�
		n--;	//�������䶯
	}
	printf("%d\n", L->prior->data);
	DestroyList(&L);
	return 0;
}