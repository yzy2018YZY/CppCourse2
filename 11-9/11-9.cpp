//1850059 º∆1∞‡ —Ó÷æ‘∂

#include <iostream>
#include <string>
using namespace std;

class Teacher
{
public:
	Teacher(string _name, int _age, char _sex, string _address, string _telNum, string _title)
	{
		name = _name;
		age = _age;
		sex = _sex;
		address = _address;
		telNum = _telNum;
		title = _title;
	}
	void display()
	{
		cout << "name:" << name << endl;
		cout << "age:" << age << endl;
		cout << "sex:" << sex << endl;
		cout << "address:" << address << endl;
		cout << "tel number:" << telNum << endl;
		cout << "title:" << title << endl;
	}
protected:
	string name;
	int age;
	char sex;
	string address;
	string telNum;
	string title;
};

class Cadre
{
public:
	Cadre(string _name, int _age, char _sex, string _address, string _telNum, string _post)
	{
		name = _name;
		age = _age;
		sex = _sex;
		address = _address;
		telNum = _telNum;
		post = _post;
	}
protected:
	string name;
	int age;
	char sex;
	string address;
	string telNum;
	string post;
};

class Teacher_Cadre :public Teacher, public Cadre
{
public:
	Teacher_Cadre(string name, int age, char sex, string address, string telNum, string title, string post, float wage):Teacher(name, age, sex, address, telNum, title), Cadre(name, age, sex, address, telNum, post)
	{
		wages = wage;
	}
	void show()
	{
		Teacher::display();
		cout << "post:" << Cadre::post << endl;
		cout << "wages:" << wages << endl;
	}
private:
	float wages;
};

int main()
{
	Teacher_Cadre tc1("Wang", 50, 'm', "Shanghai", "13400001234", "Professor", "Leader", 5000);
	tc1.show();
	return 0;
}