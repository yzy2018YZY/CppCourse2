//1850059 º∆1∞‡ —Ó÷æ‘∂

#include "12-b2-double1.h"

int double1::operator==(double1 &d1)
{
	if (fabs(x - d1.x) < 1e-6)
		return 1;
	else
		return 0;
}

int double1::operator!=(double1 &d1)
{
	if (fabs(x - d1.x) < 1e-6)
		return 0;
	else
		return 1;
}

double1::double1()
{
	x = 0;
}

double1::double1(double n)
{
	x = n;
}

ostream &operator<<(ostream &out, const double1 &d)
{
	out << d.x;
	return out;
}

istream &operator>>(istream &in, double1 &d)
{
	in >> d.x;
	return in;
}