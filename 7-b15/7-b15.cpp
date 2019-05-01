//1850059 计1班 杨志远

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
		if (strcmp(argv[1], "-check") != 0)//判别文件类型
		{
			cerr << "参数错误" << endl;
			return 2;
		}
		ifstream in(argv[2], ios::in | ios::binary);
		if (!in.is_open())
		{
			cerr << "文件" << argv[2] << "打开失败" << endl;
			return 3;
		}
		cout << (form(in) ? "Linux格式" : "Windows格式") << endl;
		in.close();
	}
	else if (argc == 5)
	{
		if (strcmp(argv[1], "-convert") != 0)
		{
			cerr << "参数错误" << endl;
			return 2;
		}
		bool winToLinux = (strcmp(argv[2], "wtol") == 0);
		if (strcmp(argv[2], "wtol") == 0 || strcmp(argv[2], "ltow") == 0)//Windows与Linux互相转换
		{
			ifstream in(argv[3], ios::in | ios::binary);
			if (!in.is_open())
			{
				cerr << "文件" << argv[3] << "打开失败" << endl;
				return 3;
			}
			if ((winToLinux && form(in)) || (!winToLinux && !form(in)))
			{
				cerr << "文件格式错误" << endl;
				in.close();
				return 4;
			}
			ofstream out(argv[4], ios::out | ios::binary);
			if (!out.is_open())
			{
				cerr << "文件" << argv[4] << "打开失败" << endl;
				in.close();
				return 3;
			}
			int ch = ' ';
			while ((ch = in.get()) != EOF)//转换
			{
				if (winToLinux)//Windows转Linux
				{
					if (ch != 0x0D)
						out.put(char(ch));
				}
				else//Linux转Windows
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
			cout << (winToLinux ? "Windows" : "Linux") << "文件 " << argv[3] << " 转换" << (winToLinux ? "Linux" : "Windows") << "文件 " << argv[4] << " 完成" << endl;
			in.close();
			out.close();
		}
		else
		{
			cerr << "参数错误" << endl;
			return 2;
		}
	}
	else
	{
		usage(argv[0]);
		//cerr << "参数数量错误" << endl;
		return 1;
	}
	return 0;
}