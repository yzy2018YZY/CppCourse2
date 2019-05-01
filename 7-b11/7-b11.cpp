//1850059 计1班 杨志远

#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

const int DefaultMatchDegree = 80;
const int MinMatchDegree = 60;
const int MaxMatchDegree = 100;
const char *ErrorMessage[] =
{
	"检查学号是all，匹配学号必须是all",
	"要检查的学号不是7位",
	"要检查的学号不是7位数字",
	"要匹配的学号不是7位",
	"要匹配的学号不是7位数字",
	"源程序文件名超过了32字节",
	"输出结果文件名超过了32字节",
};

int usage(const char *procname)
{
	cout << "Usage: " << procname << " 要检查的学号/all 匹配学号/all 源程序名/all 相似度阀值(60-100) 输出(filename/screen)" << endl;
	cout << "               1859999          1859998      all          80                screen" << endl;
	cout << "               1859999          all          7-b2.cpp     75                result.txt" << endl;
	cout << "               all              all          7-b2.cpp     80                check.dat" << endl;
	cout << "               all              all          all          85                screen" << endl;

	return 0;
}

//1:长度错误 2:非数字 0:正确
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
	//检查参数数量
	if (argc != 6)
	{
		usage(argv[0]);
		return -1;
	}
	//检查argv[1]
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
	//检查argv[2]
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
	//检查argv[3]
	if (strlen(argv[3]) > 32)
	{
		cout << ErrorMessage[5] << endl;
		return 4;
	}
	//检查argv[4]
	if (is_number(argv[4]))
	{
		matchDegree = atoi(argv[4]);
		if (matchDegree < MinMatchDegree || matchDegree > MaxMatchDegree)
			matchDegree = DefaultMatchDegree;
	}
	//检查argv[5]
	if (strlen(argv[5]) > 32)
	{
		cout << ErrorMessage[6] << endl;
		return 5;
	}
	cout << "参数检查通过" << endl;
	cout << "检查学号：" << argv[1] << endl;
	cout << "匹配学号：" << argv[2] << endl;
	cout << "源文件名：" << argv[3] << endl;
	cout << "匹配阈值：" << matchDegree << endl;
	cout << "输出目标：" << argv[5] << endl;
	return 0;
}