//1850059 ��1�� ��־Զ

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
		cout << "�ڴ�����ʧ��" << endl;
		return -1;
	}
	if (students == NULL)
	{
		cout << "�ڴ�����ʧ��" << endl;
		return 0;
	}
	for (int i = 0; i < n; i++)//��������
	{
		cin >> id >> tempStr >> score;
		students[i].id = id;
		students[i].score = score;
		students[i].name = new(nothrow) char[strlen(tempStr) + 1];
		if (students[i].name == NULL)
		{
			cout << "�ڴ�����ʧ��" << endl;
			return -1;
		}
		strcpy(students[i].name, tempStr);
		students[i].rank = 0;
	}
	for (int i = 0; i < n; i++)//��������
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
	for (int i = 0; i < n; i++)//�����Ϣ
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
	for (int i = 0; i < n; i++)//�ͷ��ڴ�
	{
		delete students[i].name;
		students[i].name = NULL;
	}
	delete []students;
	return 0;
}