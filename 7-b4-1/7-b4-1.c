//1850059 ��1�� ��־Զ

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
	int *no;
	char *name;
	int *score;
	struct student *next;
};

int main()
{
	//system("7-b3-maketxt.exe");
	//system("type student.txt");
	//cout << endl;
	//freopen("list.txt", "r", stdin);
	int no, score;
	char name[20];
	struct student *head = NULL, *temp = NULL;
	for (;;)//����������������
	{
		struct student *pre = temp;
		scanf("%d%s%d", &no, name, &score);
		if (no >= 9999999)
			break;
		temp = malloc(sizeof(struct student));
		if (temp == NULL)
		{
			printf("�ڴ�����ʧ��\n");
			return -1;
		}
		if (head == NULL)
			head = temp;
		else
			pre->next = temp;
		temp->no = malloc(sizeof(int));
		if (temp->no == NULL)
		{
			printf("�ڴ�����ʧ��\n");
			return -1;
		}
		*temp->no = no;
		temp->score = malloc(sizeof(int));
		if (temp->score == NULL)
		{
			printf("�ڴ�����ʧ��\n");
			return -1;
		}
		*temp->score = score;
		temp->name = malloc(sizeof(char) * (strlen(name) + 1));
		if (temp->name == NULL)
		{
			printf("�ڴ�����ʧ��\n");
			return -1;
		}
		strcpy(temp->name, name);
		temp->next = NULL;
	}
	temp = head;//�����Ϣ
	while (temp != NULL)
	{
		printf("%d %s %d\n", *temp->no, temp->name, *temp->score);
		temp = temp->next;
	}
	temp = head;//��������
	while (temp != NULL)
	{
		struct student *pre = temp;
		temp = temp->next;
		free(pre->no);
		free(pre->name);
		free(pre->score);
		free(pre);
		pre = NULL;
	}
	return 0;
}