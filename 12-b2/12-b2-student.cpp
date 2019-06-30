//1850059 ¼Æ1°à ÑîÖ¾Ô¶

#include "12-b2-student.h"

student::student()
{
	num = 0;
	name = "";
	sex = ' ';
	score = 0;
	addr = "";
}

student::student(int _num, const string &_name, char _sex, float _score, const string &_addr)
{
	num = _num;
	name = _name;
	sex = _sex;
	score = _score;
	addr = _addr;
}

int student::operator==(student &d1)
{
	if (num == d1.num)
		return 1;
	else
		return 0;
}

int student::operator!=(student &d1)
{
	if (num == d1.num)
		return 0;
	else
		return 1;
}

ostream &operator<<(ostream &out, const student &d)
{
	out << d.num << "-" << d.name << "-" << d.sex << "-" << d.score << "-" << d.addr;
	return out;
}

istream &operator>>(istream &in, student &d)
{
	in >> d.num >> d.name >> d.sex >> d.score >> d.addr;
	return in;
}