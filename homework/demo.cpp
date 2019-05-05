#include <iostream>
#include <string.h>
#include <string>
#include <codecvt>
using namespace std;

void Intersection(int a[], int aLength, int b[], int bLength, int c[], int &cLength)
{
	for (int i = 0; i < aLength; i++)
	{
		for (int j = 0; j < bLength; j++)
		{
			if (a[i] == b[j])
			{
				c[cLength++] = a[i];
				break;
			}
		}
	}
}


int main()
{
	int a[] = { 1, 2, 3, 4, 5 };
	int b[] = { 3, 5, 1, 8, 9 };
	int c[100] = { 0 };
	int cLength = 0;
	Intersection(a, 5, b, 5, c, cLength);
	for (int i = 0; i < 5; i++)
		cout << c[i] << endl;

}
