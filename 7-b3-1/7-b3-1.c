//1850059 计1班 杨志远

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
	int no;
	char name[9];
	int score;
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
	for (;;)//创建链表，输入数据
	{
		struct student *pre = temp;
		scanf("%d%s%d", &no, name, &score);
		if (no >= 9999999)
			break;
		temp = malloc(sizeof(struct student));
		if (temp == NULL)
		{
			printf("内存申请失败\n");
			return -1;
		}
		if (head == NULL)
			head = temp;
		else
			pre->next = temp;
		temp->no = no;
		temp->score = score;
		strcpy(temp->name, name);
		temp->next = NULL;
	}
	temp = head;//输出信息
	while (temp != NULL)
	{
		printf("%d %s %d\n", temp->no, temp->name, temp->score);
		temp = temp->next;
	}
	temp = head;//销毁链表
	while (temp != NULL)
	{
		struct student *pre = temp;
		temp = temp->next;
		free(pre);
		pre = NULL;
	}
	return 0;
}