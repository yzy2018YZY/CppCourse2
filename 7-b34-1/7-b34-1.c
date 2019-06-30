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

	(*L) = NULL;	//ͷ����next��NULL
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

/* ��ָ��λ��ǰ����һ����Ԫ�� */
Status ListInsert(LinkList *L, int i, ElemType e)
{
	LinkList s, p = *L;	//pָ��ͷ���
	int      pos = 0;

	if (i == 1)
		goto INSERT;

	/* Ѱ�ҵ�i-1����� */
	do 
	{
		p = p->next;
		pos++;
	} while (p != (*L) && pos < i - 1);

	if (p == (*L) || pos > i - 1)  //iֵ�Ƿ��򷵻�
		return ERROR;

	//ִ�е��˱�ʾ�ҵ�ָ��λ�ã�pָ���i-1�����
INSERT:
	s = (LinkList)malloc(sizeof(LNode));
	if (s == NULL)
		return LISTOVERFLOW;

	s->data = e; 	//�½��������ֵ
	s->next = p->next;	//�½���next�ǵ�i��
	p->next = s;	//��i-1����next���½��
	
	return OK;
}

/* ɾ���ڵ� */
Status ListDelete(LinkList L, LinkList *prior, LinkList *p)
{
	(*prior)->next = (*p)->next;	//ɾ��p�ڵ�
	free((*p));
	(*p) = (*prior)->next;
	if ((*p) == L)	//����ͷ���
	{
		(*prior) = (*p);
		(*p) = (*p)->next;
	}
	return OK;
}

/* ��ǰk�Σ���ȡ�ڵ��Ӧ��ָ�� */
Status JumpList(LinkList L, int k, LinkList *prior, LinkList *p)
{
	int i;
	for (i = 0; i < k; i++)
	{
		(*prior) = (*p);
		(*p) = (*p)->next;
		if ((*p) == L)	//����ͷ���
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
	printf("������n��m��k��\n");
	if (scanf("%d%d%d", &n, &m, &k) != 3 || n <= 0 || m <= 0 || k <= 0)
	{
		printf("�������\n");
		return 0;
	}
	for (i = n - 1; i >= 0; i--)	//��������
		ListInsert(&L, 1, i + 1);
	p = L->next;
	q = L;
	JumpList(L, (k - 1) % n, &q, &p);	//��ǰ�ƶ�(k-1)%n��
	printf("����˳��\n");
	while (ListLength(L) > 1)	//ֱ��ֻʣ1��
	{
		JumpList(L, (m - 1) % n, &q, &p);	//����(m-1)%n��
		printf("%d\n", p->data);	//�����ɾ���Ľڵ�
		ListDelete(L, &q, &p);	//ɾ��p�ڵ�
		n--;	//�������䶯
	}
	printf("%d\n", L->next->data);
	DestroyList(&L);
	return 0;
}