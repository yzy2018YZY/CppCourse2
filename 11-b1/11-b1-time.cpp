//1850059 ¼Æ1°à ÑîÖ¾Ô¶

#include "11-b1-time.h"
using namespace std;

Time::Time(int _hour, int _minute, int _second)
{
	if (_hour >= 0 && _hour < 24 && _minute >= 0 && _minute < 60 && _second >= 0 && _second < 60)
	{
		hour = _hour;
		minute = _minute;
		second = _second;
	}
	else
	{
		hour = 0;
		minute = 0;
		second = 0;
	}
}

Time::Time(int seconds)
{
	if (seconds >= 0 && seconds < 24 * 60 * 60)
	{
		hour = seconds / 3600;
		minute = (seconds % 3600) / 60;
		second = seconds % 60;
	}
	else
	{
		hour = 0;
		minute = 0;
		second = 0;
	}
}

Time::Time(const Time &time)
{
	memcpy(this, &time, sizeof(Time));
}

Time::Time()
{
	hour = 0;
	minute = 0;
	second = 0;
}

void Time::set(int _hour, int _minute, int _second)
{
	if (_hour >= 0 && _hour < 24 && _minute >= 0 && _minute < 60 && _second >= 0 && _second < 60)
	{
		hour = _hour;
		minute = _minute;
		second = _second;
	}
	else
	{
		hour = 0;
		minute = 0;
		second = 0;
	}
}

void Time::set(const int seconds)
{
	if (seconds >= 0 && seconds < 24 * 60 * 60)
	{
		hour = seconds / 3600;
		minute = (seconds % 3600) / 60;
		second = seconds % 60;
	}
	else
	{
		hour = 0;
		minute = 0;
		second = 0;
	}
}

void Time::set()
{
	hour = 0;
	minute = 0;
	second = 0;
}

void Time::get(int &_hour, int &_minute, int &_second)
{
	_hour = hour;
	_minute = minute;
	_second = second;
}

Time::operator int() const
{
	return hour * 60 * 60 + minute * 60 + second;
}

Time& Time::operator++()
{
	//(*this) = (*this) + 1;
	if (++second >= 60)
	{
		second = 0;
		++minute;
	}
	if (minute >= 60)
	{
		minute = 0;
		++hour;
	}
	if (hour >= 24)
	{
		hour = 0;
	}
	return (*this);
}

Time Time::operator++(int)
{
	Time t = (*this);
	if (++second >= 60)
	{
		second = 0;
		++minute;
	}
	if (minute >= 60)
	{
		minute = 0;
		++hour;
	}
	if (hour >= 24)
	{
		hour = 0;
	}
	return t;
}

Time& Time::operator--()
{
	//(*this) = (*this) - 1;
	if (--second < 0)
	{
		second = 59;
		--minute;
	}
	if (minute < 0)
	{
		minute = 59;
		--hour;
	}
	if (hour < 0)
	{
		hour = 23;
	}
	return (*this);
}

Time Time::operator--(int)
{
	Time t = (*this);
	if (--second < 0)
	{
		second = 59;
		--minute;
	}
	if (minute < 0)
	{
		minute = 59;
		--hour;
	}
	if (hour < 0)
	{
		hour = 23;
	}
	return t;
}

Time operator+(const Time &t, const int seconds)
{
	Time time = (int(t) + seconds) % (24 * 60 * 60);
	return time;
}

Time operator+(const int seconds, const Time &t)
{
	Time time = (int(t) + seconds) % (24 * 60 * 60);
	return time;
}

int operator-(const Time &t1, const Time &t2)
{
	if (t1 == t2)
		return 0;
	else if (t1 > t2)
		return (int(t1) - int(t2) + 24 * 60 * 60) % (24 * 60 * 60);
	else
		return -((int(t2) - int(t1)) + 24 * 60 * 60) % (24 * 60 * 60);
}

Time operator-(const Time &t, const int seconds)
{
	Time time = (int(t) - seconds + 24 * 60 * 60) % (24 * 60 * 60);
	return time;
}

ostream &operator<<(ostream &out, const Time &t)
{
	out << setfill('0') << setw(2) << t.hour << ":" << setfill('0') << setw(2) << t.minute << ":" << setfill('0') << setw(2) << t.second;
	return out;
}

istream &operator>>(istream &in, Time &t)
{
	int hour, minute, second;
	in >> hour >> minute >> second;
	Time time(hour, minute, second);
	memcpy(&t, &time, sizeof(Time));
	return in;
}

bool operator>(const Time &t1, const Time &t2)
{
	if (t1.hour > t2.hour)
		return true;
	if (t1.hour < t2.hour)
		return false;
	if (t1.minute > t2.minute)
		return true;
	if (t1.minute < t2.minute)
		return false;
	if (t1.second > t2.second)
		return true;
	else
		return false;
}

bool operator<(const Time &t1, const Time &t2)
{
	if (t1.hour < t2.hour)
		return true;
	if (t1.hour > t2.hour)
		return false;
	if (t1.minute < t2.minute)
		return true;
	if (t1.minute > t2.minute)
		return false;
	if (t1.second < t2.second)
		return true;
	else
		return false;
}

bool operator==(const Time &t1, const Time &t2)
{
	if (t1.hour == t2.hour && t1.minute == t2.minute && t1.second == t2.second)
		return true;
	else
		return false;
}

bool operator!=(const Time &t1, const Time &t2)
{
	return !(t1 == t2);
}

bool operator>=(const Time &t1, const Time &t2)
{
	return !(t1 < t2);
}

bool operator<=(const Time &t1, const Time &t2)
{
	return !(t1 > t2);
}
