//1850059 ��1�� ��־Զ

#pragma once
#include <iostream>
#include <string.h>
using namespace std;

/* ��ȫDate��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
class Date {
private:
	int year;
	int month;
	int day;
	/* ������������ݳ�Ա */
public:
	/* ������Ҫ��������ĳ�Ա��������Ԫ������(������������ݳ�Ա) */
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

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

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

/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */

const int DaysOfMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };