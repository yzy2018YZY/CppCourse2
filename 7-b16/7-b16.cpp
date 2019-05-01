//1850059 ��1�� ��־Զ

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

const int BytesEachLine = 16;
const char Separator[] = "-";

int main(int argc, char *argv[])
{
	char fileName[100] = "";
	if (argc == 1)
	{
		cout << "�ļ���������ʽ�����ԣ�" << endl;
		cout << "    a.txt������·����ʽ" << endl;
		cout << "    ../data/b.dat�����·����ʽ" << endl;
		cout << "    C : /Windows/System32/c.dat���������·����ʽ" << endl;
		cout << "�������ļ��� : ";
		cin >> fileName;
	}
	else if (strlen(argv[1]) >= 100)
	{
		cout << "�ļ�������" << endl;
		return 4;
	}
	else
	{
		strcpy(fileName, argv[1]);
	}
	ifstream in(fileName, ios::in | ios::binary);
	if (!in.is_open())
	{
		cerr << "�ļ�" << fileName << "��ʧ��" << endl;
		return 3;
	}
	while (!in.eof())
	{
		int ch[BytesEachLine + 4];
		for (int i = 0; i < BytesEachLine; i++)
		{
			ch[i] = in.get();
			if (ch[i] == EOF)
			{
				for (int k = i + 1; k < BytesEachLine; k++)
					ch[k] = EOF;
				break;
			}
		}
		if (ch[i] == EOF)
			break;
		cout << setw(8) << setfill('0') << hex << in.tellg();
		cout << "  ";
		for (int i = 0; i < BytesEachLine; i++)
		{
			if (i % 8 == 0 && i != 0)
				cout << (ch[i] == EOF ? " " : Separator) << " ";
			if (ch[i] == EOF)
				cout << "   ";
			else
				cout << setw(2) << setfill('0') << hex << int(ch[i]) << " ";
		}
		cout << "    ";
		for (int i = 0; i < BytesEachLine; i++)
		{
			if (ch[i] == EOF)
				cout << "";
			else if (ch[i] >= 33 && ch[i] <= 126)
				cout << char(ch[i]);
			else
				cout << ".";
		}
		cout << endl;
	}
	in.close();
	return 0;
}
