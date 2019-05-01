//1850059 ��1�� ��־Զ

#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

const int DefaultMatchDegree = 80;
const int MinMatchDegree = 60;
const int MaxMatchDegree = 100;
const char *ErrorMessage[] =
{
	"���ѧ����all��ƥ��ѧ�ű�����all",
	"Ҫ����ѧ�Ų���7λ",
	"Ҫ����ѧ�Ų���7λ����",
	"Ҫƥ���ѧ�Ų���7λ",
	"Ҫƥ���ѧ�Ų���7λ����",
	"Դ�����ļ���������32�ֽ�",
	"�������ļ���������32�ֽ�",
};

int usage(const char *procname)
{
	cout << "Usage: " << procname << " Ҫ����ѧ��/all ƥ��ѧ��/all Դ������/all ���ƶȷ�ֵ(60-100) ���(filename/screen)" << endl;
	cout << "               1859999          1859998      all          80                screen" << endl;
	cout << "               1859999          all          7-b2.cpp     75                result.txt" << endl;
	cout << "               all              all          7-b2.cpp     80                check.dat" << endl;
	cout << "               all              all          all          85                screen" << endl;

	return 0;
}

//1:���ȴ��� 2:������ 0:��ȷ
int is_no(char str[], int len = 7)
{
	if (strlen(str) != len)
		return 1;
	for (int i = 0; i < len; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return 2;
	}
	return 0;
}

bool is_number(char str[])
{
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

int main(int argc, char *argv[])
{
	int matchDegree = DefaultMatchDegree;
	//����������
	if (argc != 6)
	{
		usage(argv[0]);
		return -1;
	}
	//���argv[1]
	if (strcmp(argv[1], "all") == 0)
	{
		if (strcmp(argv[2], "all") != 0)
		{
			cout << ErrorMessage[0] << endl;
			return 1;
		}
	}
	else
	{
		if (is_no(argv[1]) == 1)
		{
			cout << ErrorMessage[1] << endl;
			return 2;
		}
		if (is_no(argv[1]) == 2)
		{
			cout << ErrorMessage[2] << endl;
			return 3;
		}
	}
	//���argv[2]
	if (strcmp(argv[2], "all") != 0)
	{
		if (is_no(argv[2]) == 1)
		{
			cout << ErrorMessage[3] << endl;
			return 2;
		}
		if (is_no(argv[2]) == 2)
		{
			cout << ErrorMessage[4] << endl;
			return 3;
		}
	}
	//���argv[3]
	if (strlen(argv[3]) > 32)
	{
		cout << ErrorMessage[5] << endl;
		return 4;
	}
	//���argv[4]
	if (is_number(argv[4]))
	{
		matchDegree = atoi(argv[4]);
		if (matchDegree < MinMatchDegree || matchDegree > MaxMatchDegree)
			matchDegree = DefaultMatchDegree;
	}
	//���argv[5]
	if (strlen(argv[5]) > 32)
	{
		cout << ErrorMessage[6] << endl;
		return 5;
	}
	cout << "�������ͨ��" << endl;
	cout << "���ѧ�ţ�" << argv[1] << endl;
	cout << "ƥ��ѧ�ţ�" << argv[2] << endl;
	cout << "Դ�ļ�����" << argv[3] << endl;
	cout << "ƥ����ֵ��" << matchDegree << endl;
	cout << "���Ŀ�꣺" << argv[5] << endl;
	return 0;
}