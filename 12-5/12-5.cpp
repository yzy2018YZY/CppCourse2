//1850059 º∆1∞‡ —Ó÷æ‘∂

#include <iostream>
#include <math.h>
using namespace std;

const double pi = 3.1416;

class Shape
{
public:
	virtual void area() = 0;
};

class Circle : public Shape
{
protected:
	double radius;
public:
	Circle(double r)
	{
		radius = r;
	}
	virtual void area()
	{
		cout << pi * radius * radius << endl;
	}
};

class Square : public Shape
{
protected:
	double length;
public:
	Square(double len)
	{
		length = len;
	}
	virtual void area()
	{
		cout << length * length << endl;
	}
};

class Rectangle : public Shape
{
protected:
	double height;
	double width;
public:
	Rectangle(double h, double w)
	{
		height = h;
		width = w;
	}
	virtual void area()
	{
		cout << height * width << endl;
	}
};

class Trapezoid : public Shape
{
protected:
	double height;
	double width1;
	double width2;
public:
	Trapezoid(double h, double w1, double w2)
	{
		height = h;
		width1 = w1;
		width2 = w2;
	}
	virtual void area()
	{
		cout << height * (width1 + width2) / 2 << endl;
	}
};

class Triangle : public Shape
{
protected:
	double length1;
	double length2;
	double length3;
public:
	Triangle(double a, double b, double c)
	{
		length1 = a;
		length2 = b;
		length3 = c;
	}
	virtual void area()
	{
		double p = (length1 + length2 + length3) / 2;
		cout << sqrt(p * (p - length1) * (p - length2) * (p - length3)) << endl;
	}
};

int main()
{
	Circle c1(5);
	Square s1(4);
	Rectangle r1(4, 3);
	Trapezoid t1(4, 7, 9);
	Triangle t2(3, 4, 5);
	Shape *s[5] = { &c1, &s1, &r1, &t1, &t2 };

	int i;
	for (i = 0; i < 5; i++)
	{
		s[i]->area();
	}

	return 0;
}