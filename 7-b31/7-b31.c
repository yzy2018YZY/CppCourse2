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


/* ��ʼ�����Ա� */
Status InitList(LinkList *L)
{
	/* ����ͷ���ռ䣬��ֵ��ͷָ�� */
	*L = (LNode *)malloc(sizeof(LNode));
	if (*L == NULL)
		exit(LISTOVERFLOW);

	(*L)->next = NULL;
	return OK;
}

/* ɾ�����Ա� */
Status DestroyList(LinkList *L)
{
	LinkList q, p = *L;	//ָ����Ԫ

	/* ��������(��ͷ���)�����ͷ� */
	while (p)	//������Ϊ�գ���ѭ����ִ��
	{    
		q = p->next;	//ץס�������һ�����
		free(p);
		p = q;
	}

	*L = NULL;	//ͷָ����NULL
	return OK;
}

/* �������Ա� */
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;	//ָ����Ԫ
	int lineCount = 0;

	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
		lineCount++;
		if ((lineCount) % MAX_NUM_PER_LINE == 0)	//���������һ����Ŀʱ�س�
			printf("\n");
	}
		
	if (p)
		return ERROR;

	if ((lineCount) % MAX_NUM_PER_LINE != 0)	//����س�
		printf("\n");
	return OK;
}

Status SetCreate(LinkList *L)
{
	InitList(L);
	ElemType e;
	while (scanf("%d", &e) == 1)
	{
		if (e == -1)	//�˳�
			break;
		else
		{
			LinkList p = (*L);	//ָ���׽ڵ����Ԫ�ڵ�
			while (p->next)		//p�������һ���ڵ�
			{
				if (p->data == e)	//�����ظ�Ԫ�أ������ϼ��϶���
				{
					p = NULL;
					break;
				}
				p = p->next;
			}
			if (p && p->data != e)	//β�ڵ����⴦��
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
	while (b)	//����Lb
	{
		LinkList p = La->next, q = La;
		while (p->next)
		{
			if (p->data == b->data)	//����Ƿ����ظ�Ԫ��
				break;
			q = p;
			p = p->next;
		}
		if (p->data == b->data)	//��La��ɾ���ظ�Ԫ��
		{
			q->next = p->next;
			free(p);
		}
		else	//��La�������Ԫ��
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
	printf("�����뼯��A�ĸ���Ԫ�أ��ÿո������-1������\n");
	SetCreate(&La);
	printf("�����뼯��B�ĸ���Ԫ�أ��ÿո������-1������\n");
	SetCreate(&Lb);
	printf("����A�е�Ԫ��Ϊ��\n");
	ListTraverse(La);
	printf("����B�е�Ԫ��Ϊ��\n");
	ListTraverse(Lb);
	SetDifference(La, Lb);
	printf("�����ļ���Ϊ��\n");
	ListTraverse(La);
	DestroyList(&La);
	DestroyList(&Lb);
	return 0;
}