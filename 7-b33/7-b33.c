//1850059 ��1�� ��־Զ

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _MSC_VER
#include <Windows.h>
#else
#include <unistd.h>		//exit����
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
} ET, *ElemType;

typedef struct LNode {
	ElemType      data;		//�������
	struct LNode *prior;	//���ǰ����ָ��
	struct LNode *next;		//��ź�̵�ָ��
} LNode, *LinkList;

Status compare(ElemType e1, ElemType e2)
{
	if (e1->num == e2->num)
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
	
	(*L)->data = NULL;	//ͷ��㲻�洢����
	(*L)->next = (*L);	//ͷ����nextָ���Լ�
	(*L)->prior = (*L);	//ͷ����priorָ���Լ�
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
		q = p->next;	//ץס�������һ����㣬���ձ���qֱ��ΪNULL
		if (p->data)	//�����ͷŷ�ͷ��������
			free(p->data);
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

/* ���ҷ���ָ��������Ԫ�� */
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
	LinkList p = L->next;	//��Ԫ���(����Ϊ��ʱֵ����L)
	int    pos = 1;		//��ʼλ��

	/* ѭ����������  */
	while (p != L && (*compare)(e, p->data) == FALSE) 
	{
		p = p->next;
		pos++;
	}

	return (p != L) ? pos : 0;
}


/* �������Ա� */
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;	//ָ����Ԫ

	while (p != L)	//�������нڵ�
	{
		printf("%d-%s-%c-%f-%s->\n", p->data->num, p->data->name, p->data->sex, p->data->score, p->data->addr);
		p = p->next;
	}

	return OK;
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
	if (!(s->data = (ElemType)malloc(sizeof(ET))))
		return LISTOVERFLOW;
	memcpy(s->data, e, sizeof(ET));	//��������

	s->prior = p->prior;	//��ӽڵ�
	p->prior->next = s;
	s->next = p;
	p->prior = s;

	return OK;
}

Status ListDelete_Dul(LinkList *L, int i, ElemType e)
{
	LinkList p = (*L)->next;

	if (!(p = GetElemP_Dul(*L, i)))	//��L��ȷ��ɾ��λ��
		return ERROR;

	memcpy(e, p->data, sizeof(ET));	//��������
	p->prior->next = p->next;		//ɾ���ڵ�
	p->next->prior = p->prior;
	free(p->data);
	free(p);

	return OK;
}

int main()
{
	char tempStr[100] = "";
	ET       e[] = { {1001, "����", 'M', 76.5, "�Ϻ���������"},
		  {1002, "����", 'F', 87, "�Ϻ���������"},
		  {1003, "����", 'M', 80, "�㽭ʡ������"},
		  {1004, "����", 'M', 54, "�㽭ʡ������"},
		  {1005, "ţ��", 'F', 85, "����ʡ�Ͼ���"},
		  {1006, "���", 'M', 60, "����ʡ������"} };
	ElemType e1;
	LinkList L;
	InitList(&L);
	e1 = (ElemType)malloc(sizeof(ET));
	int i, num;
	for (i = 5; i >= 0; i--)
		ListInsert_Dul(&L, 1, e + i);

	ListTraverse(L);
	while (ListLength(L) > 0)	//����Ϊ��ʱ�˳�
	{
		printf("������Ҫɾ�����ݵ�ѧ�ţ������������˳���\n");
		if (scanf("%d", &num) != 1) //������������ʱ�˳�
			break;
		e1->num = num;
		if ((i = LocateElem(L, e1, compare)) > 0)	//ɾ���ڵ�
		{
			printf("%d\n", i);
			ListDelete_Dul(&L, i, e1);
			printf("ɾ��%d���\n", num);
			ListTraverse(L);
		}
		else	//û���ҵ��ڵ�
		{
			printf("û���ҵ�%d\n", num);
		}
	}

	free(e1);
	printf("��������\n");
	DestroyList(&L);
	return 0;
}