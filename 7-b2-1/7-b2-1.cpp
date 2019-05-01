//1850059 计1班 杨志远

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

struct Student
{
	int id;
	int score;
	int rank;
	char *name;
};

int main()
{
	//system("7-b2-maketxt.exe");
	//system("type student.txt");
	//cout << endl;
	//freopen("student.txt", "r", stdin);
	int id, score, n;
	char tempStr[30];
	cin >> n;
	Student *students = new(nothrow) Student[n];
	if (students == NULL)
	{
		cout << "内存申请失败" << endl;
		return -1;
	}
	if (students == NULL)
	{
		cout << "内存申请失败" << endl;
		return 0;
	}
	for (int i = 0; i < n; i++)//输入数据
	{
		cin >> id >> tempStr >> score;
		students[i].id = id;
		students[i].score = score;
		students[i].name = new(nothrow) char[strlen(tempStr) + 1];
		if (students[i].name == NULL)
		{
			cout << "内存申请失败" << endl;
			return -1;
		}
		strcpy(students[i].name, tempStr);
		students[i].rank = 0;
	}
	for (int i = 0; i < n; i++)//计算名次
	{
		int max = 0;
		for (int j = 0; j < n; j++)
		{
			if (students[j].rank == 0 && students[j].score > max)
				max = students[j].score;
		}
		for (int j = 0; j < n; j++)
		{
			if (students[j].score == max)
			{
				students[j].rank = i + 1;
			}
		}
	}
	for (int i = 0; i < n; i++)//输出信息
	{
		int mi = 999999999, index = 0;
		for (int j = 0; j < n; j++)
		{
			if (students[j].rank > 0 && students[j].id < mi)
			{
				mi = students[j].id;
				index = j;
			}
		}
		students[index].rank *= -1;
		cout << students[index].id << " " << students[index].name << " " << students[index].score << " " << -students[index].rank << endl;
	}
	for (int i = 0; i < n; i++)//释放内存
	{
		delete students[i].name;
		students[i].name = NULL;
	}
	delete []students;
	return 0;
}