//1850059 ��1�� ��־Զ

#include <iostream>
using namespace std;

class student {
private:
	int num;
	float score;
public:
	void display();  //���ѧ�źͳɼ�
	void get(void);  //��������ѧ�źͳɼ�
//���в�����������κ����ݳ�Ա�ͳ�Ա����
};

/* �ڴ˸������Ա����������ʵ�� */

void student::display()
{
	cout << num << " " << score << endl;
}

void student::get()
{
	cin >> num;
	cin.clear();
	//cin.ignore(9999, '\n');
	cin >> score;
	cin.clear();
	//cin.ignore(9999, '\n');
}

int main()
{
	/* ��ע�⣺�������в������ٶ����κ����͵ı���(����ȫ�ֱ���) */
	student *p, s[5];

	/* ��������5���˵�ѧ�ż��ɼ�
	  ��Ҫ�󣺡����������ȷ��������ʾ�����硰�������**����ѧ�źͳɼ��� */
	p = s;
	for (int i = 0; i < 5; i++)
	{
		cout << "�������" << i + 1 << "����ѧ�źͳɼ�" << endl;
		p[i].get();
	}

	/* �����1��3��5���˵���Ϣ */

	//cout << "��1��ѧ������Ϣ��" << endl;
	p[0].display();
	//cout << "��3��ѧ������Ϣ��" << endl;
	p[2].display();
	//cout << "��5��ѧ������Ϣ��" << endl;
	p[4].display();

	return 0;
}