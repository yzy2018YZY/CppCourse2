//1850059 º∆1∞‡ —Ó÷æ‘∂

#pragma once
#include <iostream>
#include <iomanip>
#include <string.h>
#include "11-b1-date.h"
#include "11-b1-time.h"
using namespace std;

class DateTime :public Date, public Time
{
protected:
	long long allSeconds;
public:
	DateTime(int _year, int _month, int _day, int _hour, int _minute, int _second);
	DateTime(int _year, int _month, int _day);
	DateTime(long long all_seconds);
	DateTime();
	void set(int _year, int _month, int _day, int _hour, int _minute, int _second);
	void set(int _year, int _month, int _day);
	void set(long long all_seconds);
	void set();
	operator long long() const;
	friend DateTime operator+(const DateTime &dt, const long long all_seconds);
	friend DateTime operator+(const long long all_seconds, const DateTime &dt);
	friend DateTime operator+(const DateTime &dt, const int all_seconds);
	friend DateTime operator+(const int all_seconds, const DateTime &dt);
	friend long long operator-(const DateTime &dt1, const DateTime &dt2);
	friend DateTime operator-(const DateTime &dt, const long long all_seconds);
	friend DateTime operator-(const DateTime &dt, const int all_seconds);
	DateTime& operator++();
	DateTime operator++(int);
	DateTime& operator--();
	DateTime operator--(int);
	friend ostream &operator<<(ostream &out, const DateTime &dt);
	friend istream &operator>>(istream &in, DateTime &dt);
	friend bool operator>(const DateTime &dt1, const DateTime &dt2);
	friend bool operator<(const DateTime &dt1, const DateTime &dt2);
	friend bool operator==(const DateTime &dt1, const DateTime &dt2);
	friend bool operator!=(const DateTime &dt1, const DateTime &dt2);
	friend bool operator>=(const DateTime &dt1, const DateTime &dt2);
	friend bool operator<=(const DateTime &dt1, const DateTime &dt2);
};

DateTime operator+(const DateTime &dt, const long long all_seconds);

DateTime operator+(const long long all_seconds, const DateTime &dt);

DateTime operator+(const DateTime &dt, const int all_seconds);

DateTime operator+(const int all_seconds, const DateTime &dt);

long long operator-(const DateTime &dt1, const DateTime &dt2);

DateTime operator-(const DateTime &dt, const long long all_seconds);

DateTime operator-(const DateTime &dt, const int all_seconds);

ostream &operator<<(ostream &out, const DateTime &dt);

istream &operator>>(istream &in, DateTime &dt);

bool operator>(const DateTime &dt1, const DateTime &dt2);

bool operator<(const DateTime &dt1, const DateTime &dt2);

bool operator==(const DateTime &dt1, const DateTime &dt2);

bool operator!=(const DateTime &dt1, const DateTime &dt2);

bool operator>=(const DateTime &dt1, const DateTime &dt2);

bool operator<=(const DateTime &dt1, const DateTime &dt2);
