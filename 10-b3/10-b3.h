//1850059 ��1�� ��־Զ

#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/* ��ȫTString��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
class TString {
private:
	char *content;
	int   len;
	/* ������Ҫ������������ݳ�Ա����Ա��������Ԫ������ */
public:
	/* ������Ҫ������������ݳ�Ա����Ա��������Ԫ������ */
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

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

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

/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */
