#include <iostream>
using namespace std;

int main()
{
	int a = 1, b = 4294967300;
	cout << (a << b) << endl;
	cout << (a << 31) << endl;
	cout << (a << 32) << endl;			//warning
	cout << (a << 63) << endl;			//warning
	cout << (a << 64) << endl;			//warning
	cout << (a << 70) << endl << endl;	//warning
	cout << (1 << (b - 6)) << endl;
	cout << (1 << b) << endl;
	cout << (1 << (b + 6)) << endl;
	cout << (1 << 31) << endl;
	cout << (1 << 32) << endl;			//warning
	cout << (1 << 63) << endl;			//warning
	cout << (1 << 64) << endl;			//warning
	cout << (1 << 70) << endl << endl;	//warning

	long long c = 1, d = 32, e = 64;
	cout << (c << d) << endl;
	cout << (c << 31ll) << endl;
	cout << (c << 32ll) << endl;
	cout << (c << 63ll) << endl;
	cout << (c << 64ll) << endl;			//warning
	cout << (c << 70ll) << endl << endl;	//warning
	cout << (1ll << d) << endl;
	cout << (1ll << (e - 1)) << endl;
	cout << (1ll << e) << endl;
	cout << (1ll << (e + 6)) << endl;
	cout << (1ll << 31ll) << endl;
	cout << (1ll << 32ll) << endl;
	cout << (1ll << 63ll) << endl;
	cout << (1ll << 64ll) << endl;			//warning
	cout << (1ll << 70ll) << endl << endl;	//warning
	
	return 0;
}