//1850059 计1班 杨志远

#include <iostream>
#include <string>
using namespace std;

class Student
{
public:
	void get_value()
	{
		cin >> num >> name >> sex;
	}
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

class Student1 :public Student
{
public:
	void get_value_1()
	{
		get_value();
		cin >> age >> addr;
	}
	void display_1()
	{
		display();
		cout << "age:" << age << endl;
		cout << "address:" << addr << endl;
	}
private:
	int age;
	string addr;
};

int main()
{
	Student1 stud;
	cout << "请输入号码、姓名、性别、年龄、地址" << endl;
	stud.get_value_1();
	stud.display_1();
	return 0;
}