//1850059 º∆1∞‡ —Ó÷æ‘∂

#include <iostream>
using namespace std;

class Time
{
private:
	int hour;
	int minute;
	int sec;
public:
	bool set_hour()
	{
		cin >> this->hour;
		return true;
	}
	bool set_minute()
	{
		cin >> this->minute;
		return true;
	}
	bool set_sec()
	{
		cin >> this->sec;
		return true;
	}
	void show_time()
	{
		cout << this->hour << ":" << this->minute << ":" << this->sec;
	}
};

int main()
{
	Time t1;
	t1.set_hour();
	t1.set_minute();
	t1.set_sec();
	t1.show_time();
	cout << endl;
	return 0;
}