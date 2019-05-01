//1850059 计1班 杨志远

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct student
{
	int no;
	char *name;
	char *school;
	struct student *next;
};

int main()
{
	//system("7-b5-maketxt.exe");
	//system("type student.txt");
	//cout << endl;
	//freopen("stulist.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int no, m, n;
	bool *list = NULL;
	char name[20], school[40];
	student *head = NULL, *temp = NULL;
	ofstream fout;
	fout.open("result.txt", ios::out);
	if (fout.is_open() == 0) 
	{
		cout << "打开文件失败" << endl;
		return -1;
	}
	srand((unsigned int)(time(0)));
	cout << "请依次输入招生名额和报名学生人数:" << endl;
	cin >> n >> m;
	list = new(nothrow) bool[m];
	if (list == NULL)
	{
		cout << "内存申请失败" << endl;
		return -1;
	}
	cout << "请输入学生信息:" << endl;
	for (int i = 0; i < m; i++)//创建链表，输入数据
	{
		student *pre = temp;
		cin >> no >> name >> school;
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
		temp->no = no;
		temp->name = new(nothrow) char[strlen(name) + 1];
		if (temp->name == NULL)
		{
			cout << "内存申请失败" << endl;
			return -1;
		}
		strcpy(temp->name, name);
		temp->school = new(nothrow) char[strlen(school) + 1];
		if (temp->school == NULL)
		{
			cout << "内存申请失败" << endl;
			return -1;
		}
		strcpy(temp->school, school);
		temp->next = NULL;
	}
	for (int i = 0; i < m; i++)//初始化list
		list[i] = false;
	for (int i = 0; i < n; i++)//随机选择学生
	{
		int t;
		do
		{
			t = rand() % m;
		} while (list[t] == true);
		list[t] = true;
	}
	cout << "被选中的学生列表在result.txt文件中" << endl;
	temp = head;//向文件中输出列表
	for (int i = 0; temp != NULL; i++, temp = temp->next)
	{
		if (list[i])
		{
			fout << temp->no << " " << temp->name << " " << temp->school << endl;
		}
	}
	temp = head;//销毁链表
	while (temp != NULL)
	{
		student *pre = temp;
		temp = temp->next;
		delete pre->name;
		delete pre->school;
		delete pre;
		pre = NULL;
	}
	fout.close();
	return 0;
}
