//1850059 计1班 杨志远

#include <iostream>
using namespace std;

class Days {
private:
	int year;
	int month;
	int day;
	//除上面的三个private数据成员外，不再允许添加任何类型的数据成员

	int is_leap_year();  //判断是否闰年，是：返回1  /   否：返回0
public:
	int calc_days();     //计算是当年的第几天
	/* 下面可以补充其它需要的类成员函数的定义(体外实现)，数量不限 */
	Days(int _year, int _month, int _day);
};

/* 此处给出类成员函数的体外实现 */

int Days::is_leap_year()
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return 1;
	else
		return 0;
}

int Days::calc_days()
{
	const int daysOfMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int days = 0;
	if ((month == 2 && ((is_leap_year() && day > daysOfMonth[2] + 1) || (!is_leap_year() && day > daysOfMonth[2]))) || month < 1 || month > 12 || day > daysOfMonth[month])
		return -1;
	for (int i = 1; i < month; i++)
	{
		days += daysOfMonth[i];
	}
	if(month >= 3 && is_leap_year())
		days++;
	return days + day;
}

Days::Days(int _year, int _month, int _day)
{
	this->year = _year;
	this->month = _month;
	this->day = _day;
}

/* main函数不准动 */
int main()
{
	if (1) {
		Days d1(2012, 3, 18);
		cout << "应该输出78， 实际是：" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 12, 31);
		cout << "应该输出365，实际是：" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2012, 12, 31);
		cout << "应该输出366，实际是：" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 2, 29);
		cout << "应该输出-1， 实际是：" << d1.calc_days() << endl;
	}

	return 0;
}