//1850059 计1班 杨志远

#pragma once
#include <iostream>
#include <string.h>
using namespace std;

/* 补全Date类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class Date {
private:
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
	void set(const int _year, const int _month);
	void set(const int _year);
	void get(int &_year, int &_month, int &_day) const;
	void show() const;
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

/* 如果有其它全局函数需要声明，写于此处 */

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

/* 如果有需要的宏定义、只读全局变量等，写于此处 */

const int DaysOfMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };