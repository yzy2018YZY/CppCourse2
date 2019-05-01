#include <iostream>
#include <sstream>
using namespace std;

int main()         //P.437 例13.15
{
	string str("12 34 65 -23 -32 33 61 99 321 32");
	int a[10], i, j, t;
	cout << "array c:" << str << endl;

	istringstream strin(str);
	for (i = 0; i < 10; i++)
		strin >> a[i];  //str中的内容逐个读入int a[10]中

	cout << "array a:";
	for (i = 0; i < 10; i++)  //输出int a[10]的内容
		cout << a[i] << " ";
	cout << endl;
	//进行排序
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9 - i; j++)
			if (a[j] > a[j + 1]) {
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
	//输出到str中（str刚才用做了输入流）
	ostringstream strout;
	for (i = 0; i < 10; i++)
		strout << a[i] << " ";
	cout << "array c:" << str << endl;
}