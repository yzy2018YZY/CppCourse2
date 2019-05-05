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
} ElemType;

typedef struct LNode {
	ElemType      data;		//�������
	struct LNode *prior;	//���ǰ����ָ��
	struct LNode *next;		//��ź�̵�ָ��
} LNode, *LinkList;

/* ��ʼ�����Ա� */
Status InitList(LinkList *L)
{
	/* ����ͷ���ռ䣬��ֵ��ͷָ�� */
	*L = (LNode *)malloc(sizeof(LNode));
	if (*L == NULL)
		exit(LISTOVERFLOW);

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

/* �������Ա� */
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;	//ָ����Ԫ

	while (p != L)	//�������нڵ�
	{
		printf("%d-%s-%c-%f-%s->\n", p->data.num, p->data.name, p->data.sex, p->data.score, p->data.addr);
		p = p->next;
	}
	
	return OK;
}

/*��ȡԪ�����ڵ�ָ�룬����Ϊ�������������Ϊ�������*/
LinkList GetElemP_Dul(LinkList L, int i)
{
	LinkList p = L->next;	//ָ����Ԫ���
	int pos = 1;			//��ʼλ��Ϊ1

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
Status ListInsert_Dul(LinkList *L, int i, ElemType *e)
{
	LinkList p, s;
	if (!(p = GetElemP_Dul(*L, i)))	//��L��ȷ������λ��
		return ERROR;	//����λ�ò��Ϸ�
	if (!(s = (LinkList)malloc(sizeof(LNode))))
		return LISTOVERFLOW;
	memcpy(&(s->data), e, sizeof(ElemType));
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return OK;
}

int main()
{
	char tempStr[100] = "";
	srand((unsigned int)time(0));
	ElemType s1;
	LinkList L;
	InitList(&L);
	
	printf("������Ҫ�����Ԫ�أ�ѧ�š��������Ա𡢷�������ַ���������������˳�������ѧ��������abc��\n");
	while (scanf("%d%s%s%f%s", &s1.num, s1.name, tempStr, &s1.score, &s1.addr) == 5)
	{
		s1.sex = tempStr[0];
		printf("����Ԫ֮ǰ���룺\n");
		ListInsert_Dul(&L, 0, &s1);
		ListTraverse(L);
		int ran = rand() % ListLength(L) + 1;
		printf("���м�(%d)���룺\n", ran);
		ListInsert_Dul(&L, ran, &s1);
		ListTraverse(L);
		printf("��β�ڵ�(%d)����룺\n", ListLength(L));
		ListInsert_Dul(&L, ListLength(L) + 1, &s1);
		ListTraverse(L);
		printf("������Ҫ�����Ԫ�أ�ѧ�š��������Ա𡢷�������ַ���������������˳�������ѧ��������abc����\n");
	}

	printf("��������\n");
	DestroyList(&L);
	return 0;
}