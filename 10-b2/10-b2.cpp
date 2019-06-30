//1850059 计1班 杨志远

#include <iostream>
#include "10-b2.h"
using namespace std;

//判断是否是闰年，是的话返回1，否则返回0
static int leap(int year)
{
	if (year % 400 == 0)
		return 1;
	else if (year % 100 != 0 && year % 4 == 0)
		return 1;
	else
		return 0;
}

/* 给出 Date 类的所有成员函数的体外实现 */

Date::Date()
{
	this->year = 2000;
	this->month = 1;
	this->day = 1;
}

Date::Date(const int _year, const int _month, const int _day)
{
	if (_year >= 1900 && _year <= 2099)
		this->year = _year;
	else
		this->year = 2000;
	int tMonth = (_month >= 1 && _month <= 12) ? _month : 1;
	this->month = tMonth;
	if (_day >= 1 && _day <= DaysOfMonth[tMonth] + (tMonth == 2 ? leap(this->year) : 0))
		this->day = _day;
	else
		this->day = 1;
}

Date::Date(const int _days)
{
	if (_days <= 0)
	{
		this->year = 1900;
		this->month = 1;
		this->day = 1;
		return;
	}
	if (_days >= 73049)
	{
		this->year = 2099;
		this->month = 12;
		this->day = 31;
		return;
	}
	int days = (_days > 0 ? _days : 0), i;
	for (i = 1900; days > 365 + leap(i); i++)
	{
		days -= (365 + leap(i));
	}
	this->year = i;
	for (i = 1; days > DaysOfMonth[i] + leap(this->year); i++)
	{
		days -= (DaysOfMonth[i] + (i == 2 ? leap(this->year) : 0));
	}
	this->month = i;
	this->day = days;
}

void Date::set(const int _year, const int _month, const int _day)
{
	if (_year >= 1900 && _year)
		this->year = _year;
	else if(_year != 0)
		this->year = 2000;
	int tMonth = (_month >= 1 && _month <= 12) ? _month : 1;
	if (_month != 0)
		this->month = tMonth;
	if (_day >= 1 && _day <= DaysOfMonth[tMonth] + (tMonth == 2 ? leap(this->year) : 0))
		this->day = _day;
	else if(_day != 0)
		this->day = 1;
}

void Date::set(const int _year, const int _month)
{
	if (_year >= 1900 && _year)
		this->year = _year;
	else if (_year != 0)
		this->year = 2000;
	int tMonth = (_month >= 1 && _month <= 12) ? _month : 1;
	if (_month != 0)
		this->month = tMonth;
	this->day = 1;
}

void Date::set(const int _year)
{
	if (_year >= 1900 && _year)
		this->year = _year;
	else if (_year != 0)
		this->year = 2000;
	this->month = 1;
	this->day = 1;
}

void Date::get(int &_year, int &_month, int &_day) const
{
	_year = this->year;
	_month = this->month;
	_day = this->day;
}

void Date::show() const
{
	cout << this->year << "年" << this->month << "月" << this->day << "日" << endl;
}

Date::operator int() const
{
	int days = 0;
	for (int i = 1900; i < this->year; i++)
	{
		days += (365 + leap(i));
	}
	for (int i = 1; i < this->month; i++)
	{
		days += (DaysOfMonth[i] + (i == 2 ? leap(this->year) : 0));
	}
	days += this->day;
	return days;
}

Date& Date::operator++()
{
	*this = *this + 1;
	return *this;
}

Date Date::operator++(int)
{
	Date date = *this;
	*this = *this + 1;
	return date;
}

Date& Date::operator--()
{
	*this = *this - 1;
	return *this;
}

Date Date::operator--(int)
{
	Date date = *this;
	*this = *this - 1;
	return date;
}


/* 如果有需要的其它全局函数的实现，可以写于此处 */

Date operator+(const Date &d, const int days)
{
	//手动计算的效率或许会更高，但比较麻烦，容易出错，就不写了，下同
	Date date((int)d + days);
	return date;
}

Date operator+(const int days, const Date &d) 
{
	Date date((int)d + days);
	return date;
}

int operator-(const Date &d1, const Date &d2)
{
	return ((int)d1 - (int)d2);
}

Date operator-(const Date &d, const int days)
{
	Date date((int)d - days);
	return date;
}

ostream &operator<<(ostream &out, const Date &d)
{
	out << d.year << "年" << d.month << "月" << d.day << "日";
	return out;
}

istream &operator>>(istream &in, Date &d)
{
	int year, month, day;
	in >> year >> month >> day;
	Date date(year, month, day);
	memcpy(&d, &date, sizeof(Date));
	return in;
}

bool operator>(const Date &d1, const Date &d2)
{
	if (d1.year > d2.year)
		return true;
	if (d1.year < d2.year)
		return false;
	if (d1.month > d2.month)
		return true;
	if (d1.month < d2.month)
		return false;
	if (d1.day > d2.day)
		return true;
	if (d1.day < d2.day)
		return false;
	return false;
}

bool operator<(const Date &d1, const Date &d2)
{
	if (d1.year < d2.year)
		return true;
	if (d1.year > d2.year)
		return false;
	if (d1.month < d2.month)
		return true;
	if (d1.month > d2.month)
		return false;
	if (d1.day < d2.day)
		return true;
	if (d1.day > d2.day)
		return false;
	return false;
}

bool operator==(const Date &d1, const Date &d2)
{
	if (d1.year != d2.year)
		return false;
	if (d1.month != d2.month)
		return false;
	if (d1.day != d2.day)
		return false;
	return true;
}

bool operator!=(const Date &d1, const Date &d2)
{
	return !(d1 == d2);
}

bool operator>=(const Date &d1, const Date &d2)
{
	if (d1 > d2 || d1 == d2)
		return true;
	else
		return false;
}

bool operator<=(const Date &d1, const Date &d2)
{
	if (d1 < d2 || d1 == d2)
		return true;
	else
		return false;
}