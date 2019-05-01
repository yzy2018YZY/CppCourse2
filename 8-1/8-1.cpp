//1850059 计1班 杨志远

#include <iostream>
using namespace std;

class Time
{
public:	//原：无
	void set_time(void);
	void show_time(void);
	int hour;
	int minute;
	int sec;
};

Time t;

int main(void)
{
	t.set_time();	//原：set_time();
	t.show_time();	//原：show_time();
	return 0;
}

void Time::set_time(void)	//原：int set_time(void)
{
	cin >> t.hour;
	cin >> t.minute;
	cin >> t.sec;
}

void Time::show_time(void)	//原：int show_time(void)
{
	cout << t.hour << ":" << t.minute << ":" << t.sec << endl;
}