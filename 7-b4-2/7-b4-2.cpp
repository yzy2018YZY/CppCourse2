//1850059 计1班 杨志远

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

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
	student *head = NULL, *temp = NULL;
	for (;;)//创建链表，输入数据
	{
		student *pre = temp;
		cin >> no >> name >> score;
		if (no >= 9999999)
			break;
		temp = new(nothrow) student;
		if (temp == NULL)
		{
			cout << "内存申请失败" << endl;
			return -1;
		}
		if (head == NULL)
			head = temp;
		else
			pre->next = temp;
		temp->no = new(nothrow) int(no);
		if (temp->no == NULL)
		{
			cout << "内存申请失败" << endl;
			return -1;
		}
		temp->score = new(nothrow) int(score);
		if (temp->score == NULL)
		{
			cout << "内存申请失败" << endl;
			return -1;
		}
		temp->name = new(nothrow) char[strlen(name) + 1];
		if (temp->name == NULL)
		{
			cout << "内存申请失败" << endl;
			return -1;
		}
		strcpy(temp->name, name);
		temp->next = NULL;
	}
	temp = head;//输出信息
	while (temp != NULL)
	{
		cout << *temp->no << " " << temp->name << " " << *temp->score << endl;
		temp = temp->next;
	}
	temp = head;//销毁链表
	while (temp != NULL)
	{
		student *pre = temp;
		temp = temp->next;
		delete pre->no;
		delete pre->name;
		delete pre->score;
		delete pre;
		pre = NULL;
	}
	return 0;
}