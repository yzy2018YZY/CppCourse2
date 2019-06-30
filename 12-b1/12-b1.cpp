//1850059 º∆1∞‡ —Ó÷æ‘∂

#include <iostream>
#include <math.h>
using namespace std;

const int steps = 1000000;

class integral
{
protected:
	double upper;
	double lower;
public:
	virtual double value() = 0;
	friend istream &operator>>(istream &in, integral &s);
};

istream &operator>>(istream &in, integral &s)
{
	in >> s.lower >> s.upper;
	if (s.lower > s.upper)
	{
		double temp = s.lower;
		s.lower = s.upper;
		s.upper = temp;
	}
	return in;
}

class integral_sin : public integral
{
public:
	virtual double value()
	{
		double res = 0, step = (upper - lower) / (double)steps;
		for (double n = upper; n >= lower; n -= step)
		{
			res += (sin(n) * step);
		}
		return res;
	}
};

class integral_cos : public integral
{
public:
	virtual double value()
	{
		double res = 0, step = (upper - lower) / (double)steps;
		for (double n = upper; n >= lower; n -= step)
		{
			res += (cos(n) * step);
		}
		return res;
	}
};

class integral_exp : public integral
{
public:
	virtual double value()
	{
		double res = 0, step = (upper - lower) / (double)steps;
		for (double n = upper; n >= lower; n -= step)
		{
			res += (exp(n) * step);
		}
		return res;
	}
};


int main()
{
	integral_sin s1;
	integral_cos s2;
	integral_exp s3;
	integral *p;

	cin >> s1;
	p = &s1;
	cout << p->value() << endl;
	cin >> s2;
	p = &s2;
	cout << p->value() << endl;
	cin >> s3;
	p = &s3;
	cout << p->value() << endl;
}
