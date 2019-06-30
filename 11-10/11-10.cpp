//1850059 计1班 杨志远

#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class Teacher
{
public:
	Teacher(int n, string nam, char s)
	{
		num = n;
		name = nam;
		sex = s;
	}
protected:
	void display()
	{
		cout << "num:" << num << endl;
		cout << "name:" << name << endl;
		cout << "sex:" << sex << endl;
	}
private:
	int num;
	string name;
	char sex;
};

class BirthDate
{
public:
	void set(int y, int m, int d)	//忽略了输入检查
	{
		year = y;
		month = m;
		day = d;
	}
	void display()
	{
		cout << "birthday: " << year << "." << month << "." << day << endl;
	}
private:
	int year;
	int month;
	int day;
};

class Professor :public Teacher 
{
public:
	Professor(int num, string name, char sex, int year, int month, int day) :Teacher(num, name, sex)
	{
		birthday.set(year, month, day);
	}
	void display()
	{
		Teacher::display();
		birthday.display();
	}
private:
	BirthDate birthday;
};

int main()
{
	Professor prof1(1001, "Wang", 'm', 1970, 1, 23);
	prof1.display();
	return 0;
}