#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "��������������!" << endl;
		return -1;
	}
	//���ж������Ƿ�Ϸ�
	for (int i = 0; i < 3; i++)
	{
		cout << "argv[" << i << "]=" << argv[i] << endl;
	}
	int a = atoi(argv[1]), b = atoi(argv[2]);
	cout << "������: " << a << "  " << b << endl;
	int t = a;
	a = b;
	b = t;
	cout << "������: " << a << "  " << b << endl;
	return 0;
}