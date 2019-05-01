//1850059 º∆1∞‡ —Ó÷æ‘∂

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

struct Student
{
	int id;
	int score;
	int rank;
	char *name = NULL;
};

int compare_students(const Student &s1, const Student &s2)
{
	if (s1.score > s2.score)
		return 1;
	else if (s1.score < s2.score)
		return -1;
	else
	{
		if (s1.id < s2.id)
			return 1;
		else
			return -1;
	}
}

int main()
{
	//system("7-b2-maketxt.exe");
	//system("type student.txt");
	//cout << endl;
	//freopen("student.txt", "r", stdin);
	int id, score, n, *sortList = NULL;
	char tempStr[30];
	cin >> n;
	Student *students = new(nothrow) Student[n];
	if (students == NULL)
	{
		cout << "ƒ⁄¥Ê…Í«Î ß∞‹" << endl;
		return -1;
	}
	sortList = new(nothrow) int[n];
	if (sortList == NULL)
	{
		cout << "ƒ⁄¥Ê…Í«Î ß∞‹" << endl;
		return -1;
	}
	if (students == NULL)
	{
		cout << "ƒ⁄¥Ê…Í«Î ß∞‹" << endl;
		return 0;
	}
	for (int i = 0; i < n; i++)// ‰»Î ˝æ›
	{
		cin >> id >> tempStr >> score;
		students[i].id = id;
		students[i].score = score;
		students[i].name = new(nothrow) char[strlen(tempStr) + 1];
		if (students[i].name == NULL)
		{
			cout << "ƒ⁄¥Ê…Í«Î ß∞‹" << endl;
			return -1;
		}
		strcpy(students[i].name, tempStr);
		students[i].rank = 0;
	}
	for (int i = 0; i < n; i++)//º∆À„√˚¥Œ
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
	for (int i = 0; i < n; i++)//≥ı ºªØsortList
		sortList[i] = i;
	for (int i = n - 1; i >= 0; i--)//≈≈–Ú
	{
		for (int j = 0; j < i; j++)
		{
			if (compare_students(students[sortList[j]], students[sortList[j + 1]]) == -1)
			{
				int t = sortList[j];
				sortList[j] = sortList[j + 1];
				sortList[j + 1] = t;
			}
		}
	}
	for (int i = 0; i < n; i++)// ‰≥ˆ–≈œ¢
	{
		cout << students[sortList[i]].id << " " << students[sortList[i]].name << " " << students[sortList[i]].score << " " << students[sortList[i]].rank << endl;
	}
	for (int i = 0; i < n; i++)// Õ∑≈ƒ⁄¥Ê
	{
		delete students[i].name;
		students[i].name = NULL;
	}
	delete[]students;
	return 0;
}