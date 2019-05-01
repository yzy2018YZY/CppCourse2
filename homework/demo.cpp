#include <iostream>
#include <string.h>
#include <string>
#include <codecvt>
using namespace std;

int main()
{
	char u8[] = "²tÍûËş";
	char16_t u16[] = u"²tÍûËş";
	char32_t u32[] = U"²tÍûËş";
	cout << u8 << endl;
	cout << u16 << endl;
	cout << u32 << endl;
	cout << strlen(u8) << endl;
	return 0;
}
