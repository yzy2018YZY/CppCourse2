//1850059 ��1�� ��־Զ

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
	for (;;)//����������������
	{
		student *pre = temp;
		cin >> no >> name >> score;
		if (no >= 9999999)
			break;
		temp = new(nothrow) student;
		if (temp == NULL)
		{
			cout << "�ڴ�����ʧ��" << endl;
			return -1;
		}
		if (head == NULL)
			head = temp;
		else
			pre->next = temp;
		temp->no = new(nothrow) int(no);
		if (temp->no == NULL)
		{
			cout << "�ڴ�����ʧ��" << endl;
			return -1;
		}
		temp->score = new(nothrow) int(score);
		if (temp->score == NULL)
		{
			cout << "�ڴ�����ʧ��" << endl;
			return -1;
		}
		temp->name = new(nothrow) char[strlen(name) + 1];
		if (temp->name == NULL)
		{
			cout << "�ڴ�����ʧ��" << endl;
			return -1;
		}
		strcpy(temp->name, name);
		temp->next = NULL;
	}
	temp = head;//�����Ϣ
	while (temp != NULL)
	{
		cout << *temp->no << " " << temp->name << " " << *temp->score << endl;
		temp = temp->next;
	}
	temp = head;//��������
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