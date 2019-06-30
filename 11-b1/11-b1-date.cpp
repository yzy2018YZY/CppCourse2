//1850059 计1班 杨志远

#include "11-b1-date.h"
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

Date::Date()
{
	this->year = DefaultYear;
	this->month = DefaultMonth;
	this->day = DefaultDay;
}

Date::Date(const int _year, const int _month, const int _day)
{
	if (_month >= 1 && _month <= 12 && _year >= 1900 && _year <= 2099 && _day >= 1 && _day <= DaysOfMonth[_month] + (_month == 2 ? leap(this->year) : 0))
	{
		this->year = _year;
		this->month = _month;
		this->day = _day;
	}
	else
	{
		this->year = DefaultYear;
		this->month = DefaultMonth;
		this->day = DefaultDay;
	}
}

Date::Date(const int _days)
{
	if (_days <= 0 || _days > 73049)
	{
		this->year = 1900;
		this->month = 1;
		this->day = 1;
		return;
	}
	int days = _days, i;
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
	if (_month >= 1 && _month <= 12 && _year >= 1900 && _year <= 2099 && _day >= 1 && _day <= DaysOfMonth[_month] + (_month == 2 ? leap(this->year) : 0))
	{
		this->year = _year;
		this->month = _month;
		this->day = _day;
	}
	else
	{
		this->year = DefaultYear;
		this->month = DefaultMonth;
		this->day = DefaultDay;
	}
}

void Date::set(const int _days)
{
	if (_days <= 0 || _days > 73049)
	{
		this->year = 1900;
		this->month = 1;
		this->day = 1;
		return;
	}
	int days = _days, i;
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

void Date::set()
{
	this->year = DefaultYear;
	this->month = DefaultMonth;
	this->day = DefaultDay;
}

void Date::get(int &_year, int &_month, int &_day)
{
	_year = year;
	_month = month;
	_day = day;
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
	return days - 1;
}

Date& Date::operator++()
{
	//*this = *this + 1;
	if (++day > DaysOfMonth[month])
	{
		day = 1;
		++month;
	}
	if (month > 12)
	{
		month = 1;
		day = DaysOfMonth[month];
		++year;
	}
	if (year > 2099)
	{
		year = 1900;
		month = 1;
		day = 1;
	}
	return *this;
}

Date Date::operator++(int)
{
	Date date = *this;
	if (++day > DaysOfMonth[month])
	{
		day = 1;
		++month;
	}
	if (month > 12)
	{
		month = 1;
		day = DaysOfMonth[month];
		++year;
	}
	if (year > 2099)
	{
		year = 1900;
		month = 1;
		day = 1;
	}
	return date;
}

Date& Date::operator--()
{
	//*this = *this - 1;
	if (--day <= 0)
	{
		--month;
		day = DaysOfMonth[month];
	}
	if (month <= 0)
	{
		month = 12;
		day = DaysOfMonth[month];
		--year;
	}
	if (year < 1900)
	{
		year = 2099;
		month = 12;
		day = 31;
	}
	return *this;
}

Date Date::operator--(int)
{
	Date date = *this;
	//*this = *this - 1;
	if (--day <= 0)
	{
		--month;
		day = DaysOfMonth[month];
	}
	if (month <= 0)
	{
		month = 12;
		day = DaysOfMonth[month];
		--year;
	}
	if (year < 1900)
	{
		year = 2099;
		month = 12;
		day = 31;
	}
	return date;
}

Date operator+(const Date &d, const int days)
{
	int n = ((int)d + days + 1);
	if (n >= 73050)
	{
		Date date(((int)d + days + 1) % 73050 + 1);
		return date;
	}
	else
	{
		Date date((int)d + days + 1);
		return date;
	}
}

Date operator+(const int days, const Date &d)
{
	int n = ((int)d + days + 1);
	if (n >= 73050)
	{
		Date date(((int)d + days + 1) % 73050 + 1);
		return date;
	}
	else
	{
		Date date((int)d + days + 1);
		return date;
	}
}

int operator-(const Date &d1, const Date &d2)
{
	if (d1 == d2)
		return 0;
	else if (d1 > d2)
		return (((int)d1 - (int)d2 + 73050) % 73050);
	else
		return -(((int)d2 - (int)d1 + 73050) % 73050);
}

Date operator-(const Date &d, const int days)
{
	int n = (int)d - days;
	if (n >= 0)
	{
		Date date((n + 73050 + 1) % 73050);
		return date;
	}
	else
	{
		Date date((n + 73050) % 73050);
		return date;
	}
}

ostream &operator<<(ostream &out, const Date &d)
{
	out << d.year << "-" << setfill('0') << setw(2) << d.month << "-" << setfill('0') << setw(2) << d.day;
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
