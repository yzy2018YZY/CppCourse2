#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
using namespace std;

long long decToBin(int dec) 
{
	int result = 0, temp = dec, j = 1;
	while (temp) 
	{
		result = result + j * (temp % 2);
		temp = temp / 2;
		//k = k * 10;
	}
	return result;
}

void printbinary(const unsigned int val)
{
	for (int i = 7; i >= 0; i--)
	{
		if (val & (1 << i))
			cout << "1";
		else
			cout << "0";
	}
}

int main()
{
	double f = -6.54e-4;
	char *p = (char *)&f;
	printbinary(int(*(p + 7)));
	cout << "-";
	printbinary(int(*(p + 6)));
	cout << "-";
	printbinary(int(*(p + 5)));
	cout << "-";
	printbinary(int(*(p + 4)));
	cout << "-";
	printbinary(int(*(p + 3)));
	cout << "-";
	printbinary(int(*(p + 2)));
	cout << "-";
	printbinary(int(*(p + 1)));
	cout << "-";
	printbinary(int(*(p + 0)));
	cout << endl;
	return 0;
}