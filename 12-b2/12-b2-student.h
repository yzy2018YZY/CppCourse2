//1850059 ¼Æ1°à ÑîÖ¾Ô¶

#pragma once
#include <iostream>
#include <string>
using namespace std;

class student 
{
protected:
	int num;
	string name;
	char sex;
	float score;
	string addr;
public:
	student();
	student(int _num, const string &_name, char _sex, float _score, const string &_addr);
	int operator==(student &d1);
	int operator!=(student &d1);
	friend ostream &operator<<(ostream &out, const student &d);
	friend istream &operator>>(istream &in, student &d);
};

ostream &operator<<(ostream &out, const student &d);
istream &operator>>(istream &in, student &d);