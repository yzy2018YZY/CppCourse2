//1850059 º∆1∞‡ —Ó÷æ‘∂

#pragma once
#include <iostream>
#include <iomanip>
#include <string.h>
using namespace std;

class Time
{
protected:
	int hour;
	int minute;
	int second;
public:
	Time(int _hour, int _minute, int _second);
	Time(int seconds);
	Time(const Time &time);
	Time();
	void set(int _hour, int _minute, int _second);
	void set(const int _hour);
	void set();
	void get(int &_hour, int &_minute, int &_second);
	operator int() const;
	friend Time operator+(const Time &t, const int seconds);
	friend Time operator+(const int seconds, const Time &t);
	friend int operator-(const Time &t1, const Time &t2);
	friend Time operator-(const Time &t, const int seconds);
	Time& operator++();
	Time operator++(int);
	Time& operator--();
	Time operator--(int);
	friend ostream &operator<<(ostream &out, const Time &t);
	friend istream &operator>>(istream &in, Time &t);
	friend bool operator>(const Time &t1, const Time &t2);
	friend bool operator<(const Time &t1, const Time &t2);
	friend bool operator==(const Time &t1, const Time &t2);
	friend bool operator!=(const Time &t1, const Time &t2);
	friend bool operator>=(const Time &t1, const Time &t2);
	friend bool operator<=(const Time &t1, const Time &t2);
};

Time operator+(const Time &t, const int seconds);

Time operator+(const int seconds, const Time &t);

int operator-(const Time &t1, const Time &t2);

Time operator-(const Time &t, const int seconds);

ostream &operator<<(ostream &out, const Time &t);

istream &operator>>(istream &in, Time &t);

bool operator>(const Time &t1, const Time &t2);

bool operator<(const Time &t1, const Time &t2);

bool operator==(const Time &t1, const Time &t2);

bool operator!=(const Time &t1, const Time &t2);

bool operator>=(const Time &t1, const Time &t2);

bool operator<=(const Time &t1, const Time &t2);
