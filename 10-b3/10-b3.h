//1850059 计1班 杨志远

#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/* 补全TString类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class TString {
private:
	char *content;
	int   len;
	/* 根据需要定义所需的数据成员、成员函数、友元函数等 */
public:
	/* 根据需要定义所需的数据成员、成员函数、友元函数等 */
	TString();
	TString(const char *str);
	TString(const TString &str);
	~TString();
	const char *c_str() const;
	int length();
	TString &operator+=(const TString &str);
	TString &operator+=(const char *str);
	TString &operator+=(const char c);
	TString &operator-=(const TString &str);
	TString &operator-=(const char *str);
	TString &operator-=(const char c);
	TString &operator*=(const int times);
	TString &operator=(const TString &str);
	TString &operator=(const char *str);
	TString operator!();
	bool operator>(const TString &str);
	bool operator<(const TString &str);
	bool operator==(const TString &str);
	bool operator!=(const TString &str);
	bool operator>=(const TString &str);
	bool operator<=(const TString &str);
	char &operator[](const int index);
	friend istream &operator>>(istream &in, TString &str);
	friend ostream &operator<<(ostream &out, const TString &str);
	friend const TString operator+(const TString &s1, const TString &s2);
	friend const TString operator+(const TString &s1, const char *s2);
	friend const TString operator+(const char *s1, const TString &s2);
	friend const TString operator+(const TString &str, const char c);
	friend const TString operator+(const char c, const TString &str);
	friend const TString operator-(const TString &s1, const TString &s2);
	friend const TString operator-(const TString &s1, const char *s2);
	friend const TString operator-(const TString &str, const char c);
	friend TString operator*(const TString &s1, const int times);
	friend int TStringLen(const TString &str);
};

/* 如果有其它全局函数需要声明，写于此处 */

int TStringLen(const TString &str);

istream &operator>>(istream &in, TString &str);

ostream &operator<<(ostream &in, const TString &str);

const TString operator+(const TString &s1, const TString &s2);

const TString operator+(const TString &s1, const char *s2);

const TString operator+(const char *s1, const TString &s2);

const TString operator+(const TString &str, const char c);

const TString operator+(const char c, const TString &str);

const TString operator-(const TString &s1, const TString &s2);

const TString operator-(const TString &s1, const char *s2);

const TString operator-(const TString &str, const char c);

TString operator*(const TString &s1, const int times);

int TStringLen(const TString &str);

/* 如果有需要的宏定义、只读全局变量等，写于此处 */
