#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "请输入两个数字!" << endl;
		return -1;
	}
	//不判断输入是否合法
	for (int i = 0; i < 3; i++)
	{
		cout << "argv[" << i << "]=" << argv[i] << endl;
	}
	int a = atoi(argv[1]), b = atoi(argv[2]);
	cout << "输入了: " << a << "  " << b << endl;
	int t = a;
	a = b;
	b = t;
	cout << "交换后: " << a << "  " << b << endl;
	return 0;
}