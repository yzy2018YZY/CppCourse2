#include <iostream>
#include <string.h>
#include <string>
#include <codecvt>
using namespace std;

int main()
{
	char u8[] = "�t����";
	char16_t u16[] = u"�t����";
	char32_t u32[] = U"�t����";
	cout << u8 << endl;
	cout << u16 << endl;
	cout << u32 << endl;
	cout << strlen(u8) << endl;
	return 0;
}
