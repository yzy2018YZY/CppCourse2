//1850059 º∆1∞‡ —Ó÷æ‘∂

#pragma once
#include <iostream>
#include <math.h>
using namespace std;

class double1
{
protected:
	double x;
public:
	double1();
	double1(double n);
	int operator==(double1 &d1);
	int operator!=(double1 &d1);
	friend ostream &operator<<(ostream &out, const double1 &d);
	friend istream &operator>>(istream &in, double1 &d);
};

ostream &operator<<(ostream &out, const double1 &d);
istream &operator>>(istream &in, double1 &d);