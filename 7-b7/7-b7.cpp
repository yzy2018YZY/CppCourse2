//1850059 计1班 杨志远

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <string.h>
using namespace std;

const int MaxSwitchs = 10;
const int MaxStringLength = 100;
const int InitNum = 0x0000;

char *my_strupr(char string[])
{
	int len = strlen(string);
	for (int i = 0; i < len; i++)
		string[i] = toupper(string[i]);
	return string;
}

void print_status(short status)
{
	for (int i = 0; i < MaxSwitchs; i++)
		cout << char('A' + i) << "   ";
	cout << endl;
	for (int i = 0; i < MaxSwitchs; i++)
		cout << ((((status >> i) & 1) == 0) ? "OFF " : "ON  ");
	cout << endl;
}

void set_status(short &status, char target, bool on)
{
	short temp = 0x0001 << (target - 'A');
	if (on)
		status = status | temp;
	else
		status = status & (~temp);
}

void print_info(const char info[], short status)
{
	cout << info << "0x" << hex << setw(4) << setfill('0') << status << endl;
	print_status(status);
	cout << endl;
}

int main()
{
	short status = InitNum;
	char target[MaxStringLength], instruction[MaxStringLength];
	print_info("初始状态: ", status);
	for (;;)
	{
		cout << "请以(\"A On / J Off\"形式输入，输入\"Q on / off\"退出)" << endl;
		cin >> target >> instruction;
		if (strlen(target) != 1)
			continue;
		char tar = toupper(target[0]);
		if (tar == 'Q')
			break;
		else if (tar < 'A' || tar > 'A' + MaxSwitchs - 1)
			continue;
		my_strupr(instruction);
		if (strcmp(instruction, "ON") == 0)
			set_status(status, tar, true);
		else if (strcmp(instruction, "OFF") == 0)
			set_status(status, tar, false);
		else
			continue;
		print_info("当前状态: ", status);
	}
	return 0;
}
