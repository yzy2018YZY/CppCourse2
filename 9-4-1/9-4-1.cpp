//1850059 ��1�� ��־Զ

#include <iostream>
using namespace std;

class student {
private:
	int num;
	float score;
public:
	void display();   //���ѧ�źͳɼ�
	/* ������Ҫ��������Ա�����Ķ��壬�������� */
	student(int _num, float _score);
};

/* �ڴ˸������Ա������ʵ�֣����ⷽʽ�� */

void student::display()
{
	cout << num << " " << score << endl;
}

student::student(int _num, float _score)
{
	this->num = _num;
	this->score = _score;
}

int main()
{
	student *p, s[5] = { student(1001, 78.5),
						 student(1002, 63.5),
						 student(1003, 87.5),
						 student(1004, 52.5),
						 student(1005, 34.5) };
	/* ������� 1001��1003��1005�����˵���Ϣ
	  ��ע�⣺���������ٶ����κ����͵ı��� */

	p = s;
	//cout << "��1��ѧ������Ϣ��" << endl;
	p[0].display();
	//cout << "��3��ѧ������Ϣ��" << endl;
	p[2].display();
	//cout << "��5��ѧ������Ϣ��" << endl;
	p[4].display();

	return 0;
}