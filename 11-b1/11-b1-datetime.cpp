//1850059 计1班 杨志远

#include <iomanip>
#include "11-b1-datetime.h"
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

//将总秒速调整为一定范围内的正数
static long long convert_seconds(long long seconds)
{
	return (seconds + 6311433600ll) % 6311433600ll;
}

DateTime::DateTime(int _year, int _month, int _day, int _hour, int _minute, int _second) :Date(_year, _month, _day), Time(_hour, _minute, _second)
{
	if (_year >= 1900 && _year <= 2099 && _month >= 1 && _month <= 12 && _day >= 1 && _day <= DaysOfMonth[_month] + (_month == 2 ? leap(this->year) : 0) && _hour >= 0 && _hour < 24 && _minute >= 0 && _minute < 60 && _second >= 0 && _second < 60)
	{
		allSeconds = (long long)(Date::operator int()) * 24 * 60 * 60 + Time::operator int();
	}
	else
	{
		Date::set(DefaultYear, DefaultMonth, DefaultDay);
		Time::set(0, 0, 0);
		allSeconds = (long long)(Date::operator int()) * 24 * 60 * 60;
	}
}

DateTime::DateTime(int _year, int _month, int _day) :Date(_year, _month, _day), Time()
{
	if (_year >= 1900 && _year <= 2099 && _month >= 1 && _month <= 12 && _day >= 1 && _day <= DaysOfMonth[_month] + (_month == 2 ? leap(this->year) : 0))
	{
		allSeconds = (long long)(Date::operator int()) * 24 * 60 * 60 + Time::operator int();
	}
	else
	{
		Date::set(DefaultYear, DefaultMonth, DefaultDay);
		Time::set(0, 0, 0);
		allSeconds = (long long)(Date::operator int()) * 24 * 60 * 60;
	}
}

DateTime::DateTime(long long all_seconds) :Date(int((convert_seconds(all_seconds)) / (24 * 60 * 60) + 1)), Time((convert_seconds(all_seconds)) % (24 * 60 * 60))
{
	if (all_seconds >= 0 && all_seconds < 6311433600ll)
		allSeconds = all_seconds;
	else
	{
		Date::set(DefaultYear, DefaultMonth, DefaultDay);
		Time::set(0, 0, 0);
		allSeconds = (long long)(Date::operator int()) * 24 * 60 * 60;
	}
}

DateTime::DateTime() :Date(), Time()
{
	allSeconds = (long long)(Date::operator int()) * 24 * 60 * 60;
}

void DateTime::set(int _year, int _month, int _day, int _hour, int _minute, int _second)
{
	if (_year >= 1900 && _year <= 2099 && _month >= 1 && _month <= 12 && _day >= 1 && _day <= DaysOfMonth[_month] + (_month == 2 ? leap(this->year) : 0) && _hour >= 0 && _hour < 24 && _minute >= 0 && _minute < 60 && _second >= 0 && _second < 60)
	{
		Date::set(_year, _month, _day);
		Time::set(_hour, _minute, _second);
		allSeconds = (long long)(Date::operator int()) * 24 * 60 * 60 + Time::operator int();
	}
	else
	{
		Date::set(DefaultYear, DefaultMonth, DefaultDay);
		Time::set(0, 0, 0);
		allSeconds = (long long)(Date::operator int()) * 24 * 60 * 60;
	}
	
}

void DateTime::set(int _year, int _month, int _day)
{
	if (_year >= 1900 && _year <= 2099 && _month >= 1 && _month <= 12 && _day >= 1 && _day <= DaysOfMonth[_month] + (_month == 2 ? leap(this->year) : 0))
	{
		Date::set(_year, _month, _day);
		Time::set(0, 0, 0);
	}
	else
	{
		Date::set(DefaultYear, DefaultMonth, DefaultDay);
		Time::set(0, 0, 0);
	}
	allSeconds = (long long)(Date::operator int()) * 24 * 60 * 60;
}

void DateTime::set(long long all_seconds)
{
	if (all_seconds >= 0 && all_seconds < 6311433600ll)
	{
		Date::set(int((convert_seconds(all_seconds)) / (24 * 60 * 60) + 1));
		Time::set((convert_seconds(all_seconds)) % (24 * 60 * 60));
		allSeconds = all_seconds;
	}
	else
	{
		Date::set(DefaultYear, DefaultMonth, DefaultDay);
		Time::set(0, 0, 0);
		allSeconds = (long long)(Date::operator int()) * 24 * 60 * 60;
	}
}

void DateTime::set()
{
	Date::set();
	Time::set();
	allSeconds = (long long)(Date::operator int()) * 24 * 60 * 60;
}

DateTime::operator long long() const
{
	return allSeconds;
}

DateTime& DateTime::operator++()
{
	//如果手动写的话效率更高
	this->set(convert_seconds((long long)(*this) + 1));
	return (*this);
}

DateTime DateTime::operator++(int)
{
	DateTime dt = (*this);
	this->set(convert_seconds((long long)(*this) + 1));
	return dt;
}

DateTime& DateTime::operator--()
{
	this->set(convert_seconds((long long)(*this) - 1));
	return (*this);
}

DateTime DateTime::operator--(int)
{
	DateTime dt = (*this);
	this->set(convert_seconds((long long)(*this) - 1));
	return dt;
}

DateTime operator+(const DateTime &dt, const long long all_seconds)
{
	DateTime datetime(convert_seconds((long long)dt + all_seconds));
	return datetime;
}

DateTime operator+(const long long all_seconds, const DateTime &dt)
{
	DateTime datetime(convert_seconds((long long)dt + all_seconds));
	return datetime;
}

DateTime operator+(const DateTime &dt, const int all_seconds)
{
	DateTime datetime(convert_seconds((long long)dt + all_seconds));
	return datetime;
}

DateTime operator+(const int all_seconds, const DateTime &dt)
{
	DateTime datetime(convert_seconds((long long)dt + all_seconds));
	return datetime;
}

long long operator-(const DateTime &dt1, const DateTime &dt2)
{
	if (dt1 == dt2)
		return 0;
	else if (dt1 > dt2)
		return convert_seconds(((long long)dt1 - (long long)dt2));
	else
		return -convert_seconds(((long long)dt2 - (long long)dt1));
}

DateTime operator-(const DateTime &dt, const long long all_seconds)
{
	DateTime datetime(convert_seconds((long long)dt - all_seconds));
	return datetime;
}

DateTime operator-(const DateTime &dt, const int all_seconds)
{
	DateTime datetime(convert_seconds((long long)dt - all_seconds));
	return datetime;
}

ostream &operator<<(ostream &out, const DateTime &dt)
{
	out << dt.year << "-" << setfill('0') << setw(2) << dt.month << "-" << setfill('0') << setw(2) << dt.day << " ";
	out << setfill('0') << setw(2) << dt.hour << ":" << setfill('0') << setw(2) << dt.minute << ":" << setfill('0') << setw(2) << dt.second;
	return out;
}

istream &operator>>(istream &in, DateTime &dt)
{
	int year, month, day, hour, minute, second;
	in >> year >> month >> day >> hour >> minute >> second;
	DateTime datetime(year, month, day, hour, minute, second);
	memcpy(&dt, &datetime, sizeof(Date));
	return in;
}

bool operator>(const DateTime &dt1, const DateTime &dt2)
{
	return (dt1.allSeconds > dt2.allSeconds);
}

bool operator<(const DateTime &dt1, const DateTime &dt2)
{
	return (dt1.allSeconds < dt2.allSeconds);
}

bool operator==(const DateTime &dt1, const DateTime &dt2)
{
	return (dt1.allSeconds == dt2.allSeconds);
}

bool operator!=(const DateTime &dt1, const DateTime &dt2)
{
	return (dt1.allSeconds != dt2.allSeconds);
}

bool operator>=(const DateTime &dt1, const DateTime &dt2)
{
	return (dt1.allSeconds >= dt2.allSeconds);
}

bool operator<=(const DateTime &dt1, const DateTime &dt2)
{
	return (dt1.allSeconds <= dt2.allSeconds);
}
