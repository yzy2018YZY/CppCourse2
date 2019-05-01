//1850059 ��1�� ��־Զ

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int usage(const char *procname)
{
	cout << "Usage: " << procname << " -check a.txt" << endl;
	cout << "       " << procname << " -convert wtol a.txt b.txt" << endl;
	cout << "       " << procname << " -convert ltow a.txt b.txt" << endl;
	return 0;
}

//true: Linux  false:Windows
bool form(ifstream &in)
{
	char ch;
	while ((ch = in.get()) != EOF)
	{
		if (ch == 0x0D)
		{
			in.seekg(0, ios::beg);
			return false;
		}
	}
	in.clear();
	in.seekg(0, ios::beg);
	return true;
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		if (strcmp(argv[1], "-check") != 0)//�б��ļ�����
		{
			cerr << "��������" << endl;
			return 2;
		}
		ifstream in(argv[2], ios::in | ios::binary);
		if (!in.is_open())
		{
			cerr << "�ļ�" << argv[2] << "��ʧ��" << endl;
			return 3;
		}
		cout << (form(in) ? "Linux��ʽ" : "Windows��ʽ") << endl;
		in.close();
	}
	else if (argc == 5)
	{
		if (strcmp(argv[1], "-convert") != 0)
		{
			cerr << "��������" << endl;
			return 2;
		}
		bool winToLinux = (strcmp(argv[2], "wtol") == 0);
		if (strcmp(argv[2], "wtol") == 0 || strcmp(argv[2], "ltow") == 0)//Windows��Linux����ת��
		{
			ifstream in(argv[3], ios::in | ios::binary);
			if (!in.is_open())
			{
				cerr << "�ļ�" << argv[3] << "��ʧ��" << endl;
				return 3;
			}
			if ((winToLinux && form(in)) || (!winToLinux && !form(in)))
			{
				cerr << "�ļ���ʽ����" << endl;
				in.close();
				return 4;
			}
			ofstream out(argv[4], ios::out | ios::binary);
			if (!out.is_open())
			{
				cerr << "�ļ�" << argv[4] << "��ʧ��" << endl;
				in.close();
				return 3;
			}
			int ch = ' ';
			while ((ch = in.get()) != EOF)//ת��
			{
				if (winToLinux)//WindowsתLinux
				{
					if (ch != 0x0D)
						out.put(char(ch));
				}
				else//LinuxתWindows
				{
					if (ch == 0x0A)
					{
						out.put(0x0D);
						out.put(0x0A);
					}
					else
						out.put(char(ch));
				}
			}
			cout << (winToLinux ? "Windows" : "Linux") << "�ļ� " << argv[3] << " ת��" << (winToLinux ? "Linux" : "Windows") << "�ļ� " << argv[4] << " ���" << endl;
			in.close();
			out.close();
		}
		else
		{
			cerr << "��������" << endl;
			return 2;
		}
	}
	else
	{
		usage(argv[0]);
		//cerr << "������������" << endl;
		return 1;
	}
	return 0;
}