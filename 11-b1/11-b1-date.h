//1850059 计1班 杨志远

#pragma once
#include <iostream>
#include <iomanip>
#include <string.h>
using namespace std;

class Date {
protected:
	int year;
	int month;
	int day;
	/* 不允许添加数据成员 */
public:
	/* 根据需要定义所需的成员函数、友元函数等(不允许添加数据成员) */
	Date();
	Date(const int _year, const int _month, const int _day);
	Date(const int _days);
	void set(const int _year, const int _month, const int _day);
	void set(const int _days);
	void set();
	void get(int &_year, int &_month, int &_day);
	operator int() const;
	friend Date operator+(const Date &d, const int days);
	friend Date operator+(const int days, const Date &d);
	friend int operator-(const Date &d1, const Date &d2);
	friend Date operator-(const Date &d, const int days);
	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);
	friend ostream &operator<<(ostream &out, const Date &d);
	friend istream &operator>>(istream &in, Date &d);
	friend bool operator>(const Date &d1, const Date &d2);
	friend bool operator<(const Date &d1, const Date &d2);
	friend bool operator==(const Date &d1, const Date &d2);
	friend bool operator!=(const Date &d1, const Date &d2);
	friend bool operator>=(const Date &d1, const Date &d2);
	friend bool operator<=(const Date &d1, const Date &d2);
};

Date operator+(const Date &d, const int days);

Date operator+(const int days, const Date &d);

int operator-(const Date &d1, const Date &d2);

Date operator-(const Date &d, const int days);

ostream &operator<<(ostream &out, const Date &d);

istream &operator>>(istream &in, Date &d);

bool operator>(const Date &d1, const Date &d2);

bool operator<(const Date &d1, const Date &d2);

bool operator==(const Date &d1, const Date &d2);

bool operator!=(const Date &d1, const Date &d2);

bool operator>=(const Date &d1, const Date &d2);

bool operator<=(const Date &d1, const Date &d2);

const int DaysOfMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static const int DefaultYear = 1900;
static const int DefaultMonth = 1;
static const int DefaultDay = 1;
