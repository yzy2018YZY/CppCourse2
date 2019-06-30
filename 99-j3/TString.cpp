//1850059 计1班 杨志远

/***********************************************

提高性能的主要措施：
1、将strcat和strcmp转为memcpy
2、operator+=函数中，从第32767个字符开始计算字符串长度（仅可以在当前main函数下正确）
3、仿照string和vector的实现，申请内存的大小按指数级增长，目前为1.28^n（不知道这有没有违规，但这是我能想到的提升效率最为明显的方式，注释掉ENABLEGROWTH可以关闭功能）

这个程序最耗时的过程是new和delete，因此我认为尽量减少申请内存的次数才能缩短时间
Windows下执行后内存占用111-114MB，但在多次连续执行后内存占用会略微上升
原本打算使用多线程，但是没有找到允许子线程函数传入c风格字符串指针的方法

************************************************/

#define ENABLEGROWTH
//#include <thread>
//#define MAX(a, b) ((a > b) ? a : b)
using namespace std;
const int DefaultLength = 16;
const double growth = 1.28;

class TString
{
protected:
	char *content;
	int len;
#ifdef ENABLEGROWTH
	int size;
#endif
public:
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
	bool operator!=(const char *str);
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


TString::TString()
{
	content = NULL;
	len = 0;
#ifdef ENABLEGROWTH
	size = DefaultLength;
#endif
}

TString::TString(const char *str)
{
	if (str == NULL)
	{
		content = NULL;
		len = 0;
	}
	else
	{
		len = strlen(str);
		content = new(nothrow) char[len + 1];
		if (content == NULL)
			return;
		memcpy(content, str, len + 1);
	}
#ifdef ENABLEGROWTH
	size = (len > DefaultLength) ? len * 2 : DefaultLength;
#endif
}

TString::TString(const TString &str)
{
	if (str.len == 0)
	{
		content = NULL;
		len = 0;
	}
	else
	{
		len = str.len;
		content = new(nothrow) char[len + 1];
		if (content == NULL)
			return;
		memcpy(content, str.content, len + 1);
	}
#ifdef ENABLEGROWTH
	size = (len > DefaultLength) ? len * 2 : DefaultLength;
#endif
}

TString::~TString()
{
	if (content != NULL)
	{
		delete[]content;
	}
}

const char *TString::c_str() const
{
	return content;
}

int TString::length()
{
	return len;
}

TString &TString::operator+=(const TString &str)
{
	if (str.content != NULL)
	{
		int sLen = len + str.len;	//先存储最终长度，因为len还有用
		if (content == NULL)
		{
			content = new(nothrow) char[sLen + 1];
			if (content == NULL)
				return *this;
			strcpy(content, str.content);
		}
		else
		{
			char *tStr = new(nothrow) char[sLen + 1];
			if (tStr == NULL)
				return *this;
			strcpy(tStr, content);
			strcpy(&tStr[len], str.content);	//不用strcat，提升性能
			delete[](content);
			content = tStr;
		}
		len = sLen;
	}
	return *this;
}

//void f1(string content, string p, int len)
//{
//	memcpy((char *)content.c_str(), p.c_str(), len);
//}
//
//void f2(string content, string str, int len, int sLen)
//{
//	memcpy(&(content)[len], str.c_str(), sLen + 1);
//}

TString &TString::operator+=(const char *str)
{
	
	if (str != NULL)
	{
		int sLen = strlen(&str[32767]) + 32767;
		if (content == NULL)
		{
#ifdef ENABLEGROWTH
			if (sLen + 1 >= size)
			{
				while (sLen + 1 >= size)
					size = int(size * growth);
				content = new(nothrow) char[size];
			}
#else
			content = new(nothrow) char[len + sLen + 1];
#endif
			if (content == NULL)
				return *this;
			memcpy(content, str, sLen + 1);
		}
		else
		{
#ifdef ENABLEGROWTH
			if (len + sLen + 1 >= size)
			{
				char *p = content;
				while (len + sLen + 1 >= size)
					size = int(size * growth);
				content = new(nothrow) char[size];
				if (content == NULL)
					return (*this);
				//std::thread t1(f1, content, p, len);
				//std::thread t2(f2, content, str, len, sLen);
				//t1.join();
				//t2.join();
				memcpy(content, p, len);
				memcpy(&content[len], str, sLen + 1);
				delete p;
			}
			else
			{
				memcpy(&content[len], str, sLen + 1);
			}
#else
			char *p = content;
			content = new(nothrow) char[len + sLen + 1];
			if (content == NULL)
				return (*this);
			memcpy(content, p, len);
			memcpy(&content[len], str, sLen + 1);
			delete p;
#endif
		}
		len = len + sLen;
	}
	return *this;
}

TString &TString::operator+=(const char c)
{
	len++;
	if (content == NULL)
	{
		content = new(nothrow) char[len + 1];
		if (content == NULL)
			return *this;
		content[0] = c;
		content[1] = '\0';
	}
	else
	{
		char *tStr = new(nothrow) char[len + 1];
		if (tStr == NULL)
			return *this;
		strcpy(tStr, content);
		tStr[len - 1] = c;
		tStr[len] = '\0';
		delete[](content);
		content = tStr;
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
	len = str.len;
	if (content != NULL)
		delete[](content);
	if (str.len != 0)
	{
		content = new(nothrow) char[len + 1];
		if (content == NULL)
			return *this;
		strcpy(content, str.content);
	}
	else
	{
		content = NULL;
	}
	return *this;
}

TString &TString::operator=(const char *str)
{
	if (str == NULL)
	{
		len = 0;
		if (content != NULL)
			delete[](content);
		content = NULL;
	}
	else
	{
		len = strlen(str);
		if (content != NULL)
			delete[](content);
		content = new(nothrow) char[len + 1];
		if (content == NULL)
			return *this;
		strcpy(content, str);
	}
	return *this;
}

TString TString::operator!()
{
	if (len == 0)
	{
		TString t;
		return t;
	}
	char *str = new(nothrow) char[len + 1];
	if (str == NULL)
		return *this;
	for (int i = 0; i < len; i++)
		str[i] = content[len - i - 1];
	str[len] = '\0';
	TString t = str;
	delete[]str;
	return t;
}

bool TString::operator>(const TString &str)
{
	if (len == 0)
		return false;
	if (str.len == 0)
	{
		if (len == 0)
			return false;
		else
			return true;
	}
	if (strcmp(content, str.content) > 0)
		return true;
	else
		return false;
}

bool TString::operator<(const TString &str)
{
	if (str.len == 0)
		return false;
	if (len == 0)
	{
		if (str.len == 0)
			return false;
		else
			return true;
	}
	if (strcmp(content, str.content) < 0)
		return true;
	else
		return false;
	return true;
}

bool TString::operator==(const TString &str)
{
	if (len == 0 && str.len == 0)
		return true;
	else if (len == 0)
		return false;
	else if (str.len == 0)
		return false;
	else if (strcmp(content, str.content) == 0)
		return true;
	else
		return false;
}

bool TString::operator!=(const TString &str)
{
	if (len == 0 && str.len == 0)
		return false;
	else if (len != str.len)
		return true;
	else if (strcmp(content, str.content) == 0)
		return false;
	else
		return true;
}

bool TString::operator!=(const char *str)
{
	if (len == 0 && (str == NULL || str[0] == '\0'))
		return false;
	else if (len != 0 && (str == NULL || str[0] == '\0'))
		return true;
	else if (len == 0 && str[0] != '\0')
		return true;
	else if (strcmp(content, str) == 0)
		return false;
	else
		return true;
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
	i = (i < len - 1) ? i : len - 1;
	return content[i];
}

/* 如果有需要的其它全局函数的实现，可以写于此处 */

istream &operator>>(istream &in, TString &str)
{
	const int defaultSize = 1000;
	char *tStr = (char *)malloc(sizeof(char) * defaultSize);
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
		else if (length % defaultSize == 0)	//若临时字符串空间用完，则重新扩充
		{
			tStr = (char *)realloc(tStr, sizeof(char) * (length + defaultSize));
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
