//1850059 计1班 杨志远
//检查 1851573 李博宇 1851726 汪一泓 1852101 曹乾 1852822 李宇龙 1852878 邓杰 完成

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
using namespace std;

const int BytesEachLine = 16;

int usage(const char *procname)
{
	cout << "Usage : " << procname << " 16进制debug格式文件名 原始文件名" << endl;
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		usage(argv[0]);
		return 1;
	}
	ifstream in(argv[1], ios::in);
	if (!in.is_open())
	{
		cerr << "文件" << argv[1] << "打开失败" << endl;
		return 3;
	}
	ofstream out(argv[2], ios::out | ios::binary);
	if (!out.is_open())
	{
		cerr << "文件" << argv[2] << "打开失败" << endl;
		in.close();
		return 3;
	}
	int front = -BytesEachLine;
	int num[BytesEachLine + 4];
	for (;;)
	{
		char tempStr[BytesEachLine + 4];
		int numCount = 0, separatorCount = 0;
		memset(num, 0x7f, sizeof(num));
		in >> hex >> num[0];
		if(in.eof())//行首数字格式错误
		{
			return 0;
		}
		else if (!in.good() || num[0] - front != BytesEachLine)//检查行首数字
		{
			in.clear();
			cerr << "行首序数" << setw(8) << setfill('0') << hex << num[0] << "错误" << endl;
			return 5;
		}
		else//更新行首数字
			front = num[0];
		for (int i = 0; i <= BytesEachLine; i++)
		{
			if (i % 8 == 0 && i != 0 && i != BytesEachLine)//分隔符
			{
				in.get();
				in.ignore(1000, ' ');
				num[i] = INT_MIN;
				separatorCount++;
				continue;
			}
			in >> hex >> num[i];
			if (!in.good() || in.eof())//末尾字符串
			{
				in.clear();
				num[i] = INT_MIN;
				break;
			}
			else//正常数字
			{
				numCount++;
			}
		}
		if (numCount != BytesEachLine && num[numCount - 1 + separatorCount] > 0)//这一行的字符可能是类似于4A、00这样的会与十六位数字混淆的字符串
			num[numCount - 1 + separatorCount] = INT_MIN;
		in >> tempStr; //过滤每一行最后一个字符串
		for (int i = 0; i <= numCount; i++) //写入文件
		{
			if (num[i] >= 0 && num[i] <= 0xff)
				out.put(char(num[i]));
		}
		if (numCount != BytesEachLine) //退出循环
			break;
	}
	in.close();
	out.close();
	return 0;
}
