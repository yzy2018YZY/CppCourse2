//1850059 计1班 杨志远

#include <iostream>
#include <string>
using namespace std;

class Student
{
public:

protected:
	int num;
	string name;
	char sex;
};

class Student1 :public Student
{
public:
	void get_value1();
	void display1();
private:
	int age;
	string addr;
};

void Student1::get_value1()
{
	cin >> num >> name >> sex;
	cin >> age >> addr;
}

void Student1::display1()
{
	cout << "num:" << num << endl;
	cout << "name:" << name << endl;
	cout << "sex:" << sex << endl;
	cout << "age:" << age << endl;
	cout << "address:" << addr << endl;
}

int main()
{
	Student1 stud;
	cout << "请输入号码、姓名、性别、年龄、地址" << endl;
	stud.get_value1();
	stud.display1();
	return 0;
}