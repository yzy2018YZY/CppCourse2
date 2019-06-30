//1850059 计1班 杨志远

/* 允许添加需要的头文件、宏定义等 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "10-b3.h"
using namespace std;

/* 给出 TString 类的所有成员函数的体外实现 */

TString::TString()
{
	this->content = NULL;
	this->len = 0;
}

TString::TString(const char *str)
{
	if (str == NULL)
	{
		this->content = NULL;
		this->len = 0;
	}
	else
	{
		this->len = strlen(str);
		this->content = new(nothrow) char[this->len + 1];
		if (this->content == NULL)
			return;
		strcpy(this->content, str);
	}
}

TString::TString(const TString &str)
{
	if (str.len == 0)
	{
		this->content = NULL;
		this->len = 0;
	}
	else
	{
		this->len = str.len;
		this->content = new(nothrow) char[this->len + 1];
		if (this->content == NULL)
			return;
		strcpy(this->content, str.content);
	}
}

TString::~TString()
{
	if (this->content != NULL)
	{
		delete[](this->content);
	}
}

const char *TString::c_str() const
{
	return this->content;
}

int TString::length()
{
	return this->len;
}

TString &TString::operator+=(const TString &str)
{
	if (str.content != NULL)
	{
		int sLen = this->len + str.len;	//先存储最终长度，因为this->len还有用
		if (this->content == NULL)
		{
			this->content = new(nothrow) char[sLen + 1];
			if (this->content == NULL)
				return *this;
			strcpy(this->content, str.content);
		}
		else
		{
			char *tStr = new(nothrow) char[sLen + 1];
			if (tStr == NULL)
				return *this;
			strcpy(tStr, this->content);
			strcpy(&tStr[this->len], str.content);	//不用strcat，提升性能
			delete[](this->content);
			this->content = tStr;
		}
		this->len = sLen;
	}
	return *this;
}

TString &TString::operator+=(const char *str)
{
	if (str != NULL)
	{
		int sLen = strlen(str);	//先存储最终长度，因为this->len还有用
		if (this->content == NULL)
		{
			this->content = new(nothrow) char[this->len + sLen + 1];
			if (this->content == NULL)
				return *this;
			strcpy(this->content, str);
		}
		else
		{
			char *tStr = new(nothrow) char[this->len + sLen + 1];
			if (tStr == NULL)
				return *this;
			//strcpy(tStr, this->content);
			//strcpy(&tStr[this->len], str);	//不用strcat，提升性能
			memcpy(tStr, this->content, this->len);
			memcpy(&tStr[this->len], str, sLen);
			tStr[this->len + sLen] = '\0';
			delete[](this->content);
			this->content = tStr;
		}
		this->len = this->len + sLen;
	}
	return *this;
}

TString &TString::operator+=(const char c)
{
	this->len++;
	if (this->content == NULL)
	{
		this->content = new(nothrow) char[this->len + 1];
		if (this->content == NULL)
			return *this;
		this->content[0] = c;
		this->content[1] = '\0';
	}
	else
	{
		char *tStr = new(nothrow) char[this->len + 1];
		if (tStr == NULL)
			return *this;
		strcpy(tStr, this->content);
		tStr[this->len - 1] = c;
		tStr[this->len] = '\0';
		delete[](this->content);
		this->content = tStr;
	}
	return *this;
}

TString &TString::operator-=(const TString &str)
{
	*this = *this - str;
	return *this;
}

TString &TString::operator-=(const char *str)
{
	*this = *this - str;
	return *this;
}

TString &TString::operator-=(const char c)
{
	*this = *this - c;
	return *this;
}

TString &TString::operator*=(const int times)
{
	*this = (*this) * times;
	return *this;
}

TString &TString::operator=(const TString &str)
{
	if (this == &str)	//同一个对象（例如s1=s1）
		return *this;
	this->len = str.len;
	if (this->content != NULL)
		delete[](this->content);
	if (str.len != 0)
	{
		this->content = new(nothrow) char[this->len + 1];
		if (this->content == NULL)
			return *this;
		strcpy(this->content, str.content);
	}
	else
	{
		this->content = NULL;
	}
	return *this;
}

TString &TString::operator=(const char *str)
{
	if (str == NULL)
	{
		this->len = 0;
		if (this->content != NULL)
			delete[](this->content);
		this->content = NULL;
	}
	else
	{
		this->len = strlen(str);
		if (this->content != NULL)
			delete[](this->content);
		this->content = new(nothrow) char[this->len + 1];
		if (this->content == NULL)
			return *this;
		strcpy(this->content, str);
	}
	return *this;
}

TString TString::operator!()
{
	if (this->len == 0)
	{
		TString t;
		return t;
	}
	char *str = new(nothrow) char[this->len + 1];
	if (str == NULL)
		return *this;
	for (int i = 0; i < this->len; i++)
		str[i] = this->content[this->len - i - 1];
	str[this->len] = '\0';
	TString t = str;
	delete[]str;
	return t;
}

bool TString::operator>(const TString &str)
{
	if (this->len == 0)
		return false;
	if (str.len == 0)
	{
		if (this->len == 0)
			return false;
		else
			return true;
	}
	if (strcmp(this->content, str.content) > 0)
		return true;
	else
		return false;
}

bool TString::operator<(const TString &str)
{
	if (str.len == 0)
		return false;
	if (this->len == 0)
	{
		if (str.len == 0)
			return false;
		else
			return true;
	}
	if (strcmp(this->content, str.content) < 0)
		return true;
	else
		return false;
	return true;
}

bool TString::operator==(const TString &str)
{
	if (this->len == 0 && str.len == 0)
		return true;
	else if (this->len == 0)
		return false;
	else if (str.len == 0)
		return false;
	else if (strcmp(this->content, str.content) == 0)
		return true;
	else
		return false;
}

bool TString::operator!=(const TString &str)
{
	return !(*this == str);
}

bool TString::operator>=(const TString &str)
{
	return (*this == str || *this > str);
}

bool TString::operator<=(const TString &str)
{
	return (*this == str || *this < str);
}

char &TString::operator[](const int index)
{
	int i = (index >= 0) ? index : 0;
	i = (i < this->len - 1) ? i : this->len - 1;
	return this->content[i];
}


/* 如果有需要的其它全局函数的实现，可以写于此处 */

istream &operator>>(istream &in, TString &str)
{
	const int size = 1000;
	char *tStr = (char *)malloc(sizeof(char) * size);
	char *buf = tStr;
	int length = 1;
	while (((*buf) = getchar()) == ' ' || (*buf) == '\n')	//过滤空格、回车等字符
		;
	for (;; length++)	//逐字符读入处理
	{
		if ((*buf) == '\n' || (*buf) == ' ')	//读到空格、回车则结束读入
		{
			*buf = '\0';
			break;
		}
		else if (length % size == 0)	//若临时字符串空间用完，则重新扩充
		{
			tStr = (char *)realloc(tStr, sizeof(char) * (length + size));
		}
		buf = tStr + length;	//读入一个字符
		*buf = getchar();
	}
	str.len = strlen(tStr);
	str.content = new(nothrow) char[str.len + 1];	//写入TString
	if (str.content == NULL)
		return in;
	strcpy(str.content, tStr);
	free(tStr);
	return in;
}

ostream &operator<<(ostream &out, const TString &str)
{
	if (str.len != 0)
		out << str.content;
	else
		cout << "<NULL>";
	return out;
}

const TString operator+(const TString &s1, const TString &s2)
{
	TString t;
	t.content = new(nothrow) char[s1.len + s2.len + 1];
	if (t.content == NULL)
		return t;
	t.content[0] = '\0';	//防止strcat出错
	t.len = s1.len + s2.len;
	if (s1.content != NULL)
		strcat(t.content, s1.content);
	if (s2.content != NULL)
		strcat(t.content, s2.content);
	return t;
}

const TString operator+(const TString &s1, const char *s2)
{
	TString t;
	if (s2 != NULL)
		t.len = s1.len + strlen(s2);
	else
		t.len = s1.len;
	t.content = new(nothrow) char[t.len + 1];
	if (t.content == NULL)
	{
		t.len = 0;
		return t;
	}
	t.content[0] = '\0';	//防止strcat出错
	if (s1.content != NULL)
		strcat(t.content, s1.content);
	if (s2 != NULL)
		strcat(t.content, s2);
	return t;
}

const TString operator+(const char *s1, const TString &s2)
{
	TString t;
	if (s1 != NULL)
		t.len = strlen(s1) + s2.len;
	else
		t.len = s2.len;
	t.content = new(nothrow) char[t.len + 1];
	if (t.content == NULL)
	{
		t.len = 0;
		return t;
	}
	t.content[0] = '\0';	//防止strcat出错
	if (s1 != NULL)
		strcat(t.content, s1);
	if (s2.content != NULL)
		strcat(t.content, s2.content);
	return t;
}

const TString operator+(const TString &str, const char c)
{
	TString t;
	if (str.content != NULL)
		t.len = str.len + 1;
	else
		t.len = 1;
	t.content = new(nothrow) char[t.len + 1];
	if (t.content == NULL)
	{
		t.len = 0;
		return t;
	}
	if (str.content != NULL)
		strcpy(t.content, str.content);
	t.content[t.len - 1] = c;
	t.content[t.len] = '\0';
	return t;
}

const TString operator+(const char c, const TString &str)
{
	TString t;
	if (str.content != NULL)
		t.len = str.len + 1;
	else
		t.len = 1;
	t.content = new(nothrow) char[t.len + 1];
	if (t.content == NULL)
	{
		t.len = 0;
		return t;
	}
	t.content[0] = c;
	if (str.content != NULL)
		strcpy(&t.content[1], str.content);
	return t;
}

const TString operator-(const TString &s1, const TString &s2)
{
	if (s1.len == 0 || s2.len == 0)
	{
		TString t = s1;
		return t;
	}
	char *p = strstr(s1.content, s2.content), *q;
	if (p == NULL)
	{
		TString t = s1;
		return t;
	}
	char *str = new(nothrow) char[s1.len - s2.len + 1];
	if (str == NULL)
	{
		TString t = s1;
		return t;
	}
	int len = 0;
	for (q = s1.content; q != p; q++)
		str[len++] = *q;
	for (q = p + s2.len; *q != '\0'; q++)
		str[len++] = *q;
	str[len] = '\0';
	TString t = str;
	delete[]str;
	return t;
}

const TString operator-(const TString &s1, const char *s2)
{
	int len2 = strlen(s2);
	if (s1.len == 0 || len2 == 0)
	{
		TString t = s1;
		return t;
	}
	char *p = strstr(s1.content, s2), *q;
	if (p == NULL)
	{
		TString t = s1;
		return t;
	}
	char *str = new(nothrow) char[s1.len - len2 + 1];
	if (str == NULL)
	{
		TString t = s1;
		return t;
	}
	int len = 0;
	for (q = s1.content; q != p; q++)
		str[len++] = *q;
	for (q = p + len2; *q != '\0'; q++)
		str[len++] = *q;
	str[len] = '\0';
	TString t = str;
	delete[]str;
	return t;
}

const TString operator-(const TString &str, const char c)
{
	if (str.len == 0)
	{
		TString t = str;
		return t;
	}
	char *p = strchr(str.content, c), *q;
	if (p == NULL)
	{
		TString t = str;
		return t;
	}
	char *tStr = new(nothrow) char[str.len - 1 + 1];
	if (tStr == NULL)
	{
		TString t = str;
		return t;
	}
	int len = 0;
	for (q = str.content; q != p; q++)
		tStr[len++] = *q;
	for (q = p + 1; *q != '\0'; q++)
		tStr[len++] = *q;
	tStr[len] = '\0';
	TString t = tStr;
	delete[]tStr;
	return t;
}

TString operator*(const TString &s1, const int times)
{
	if (s1.len == 0)
	{
		TString t;
		return t;
	} 
	char *str = new(nothrow) char[s1.len * times + 1];
	if (str == NULL)
	{
		TString t = s1;
		return t;
	}
	str[0] = '\0';
	for (int i = 0; i < times; i++)
		strcat(str, s1.content);
	TString t = str;
	delete[]str;
	return t;
}

int TStringLen(const TString &str)
{
	return str.len;
}
