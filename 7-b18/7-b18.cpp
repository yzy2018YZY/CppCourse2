#include <iostream>
#include <sstream>
using namespace std;

int main()         //P.437 ��13.15
{
	string str("12 34 65 -23 -32 33 61 99 321 32");
	int a[10], i, j, t;
	cout << "array c:" << str << endl;

	istringstream strin(str);
	for (i = 0; i < 10; i++)
		strin >> a[i];  //str�е������������int a[10]��

	cout << "array a:";
	for (i = 0; i < 10; i++)  //���int a[10]������
		cout << a[i] << " ";
	cout << endl;
	//��������
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9 - i; j++)
			if (a[j] > a[j + 1]) {
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
	//�����str�У�str�ղ���������������
	ostringstream strout;
	for (i = 0; i < 10; i++)
		strout << a[i] << " ";
	cout << "array c:" << str << endl;
}