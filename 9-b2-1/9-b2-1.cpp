//1850059 ��1�� ��־Զ

#include <iostream>
#include <cmath>
using namespace std;

class point {
private:
	int x;
	int y;
	//�����������private���ݳ�Ա�⣬������������κ����͵����ݳ�Ա
public:
	int getx() const
	{
		return x;
	}
	int gety() const
	{
		return y;
	}
	/* ���Զ�����Ҫ�ĳ�Ա�������������ޣ��������ڷ�ʽʵ�֣�������������ݳ�Ա */
	bool set(int _x, int _y)
	{
		this->x = _x;
		this->y = _y;
		return true;
	}
};

class triangle {
private:
	point p1;
	point p2;
	point p3;
	//�����������private���ݳ�Ա�⣬������������κ����͵����ݳ�Ա
public:
	/* ������Ҫ������Ӧ���������area����(�β�Ϊ�գ���׼��)��Ҫ����������ܹ��������Σ��򷵻���������򷵻� -1 */
	double area()
	{
		double s1 = sqrt((p1.getx() - p2.getx()) * (p1.getx() - p2.getx()) + (p1.gety() - p2.gety()) * (p1.gety() - p2.gety()));	//p1��p2֮��ľ���
		double s2 = sqrt((p2.getx() - p3.getx()) * (p2.getx() - p3.getx()) + (p2.gety() - p3.gety()) * (p2.gety() - p3.gety()));	//p2��p3֮��ľ���
		double s3 = sqrt((p3.getx() - p1.getx()) * (p3.getx() - p1.getx()) + (p3.gety() - p1.gety()) * (p3.gety() - p1.gety()));	//p3��p1֮��ľ���
		if (s1 + s2 <= s3 || s2 + s3 <= s1 || s3 + s1 <= s2)	//���ݲ��Ϸ�
			return -1;
		else
			return 0.5 * fabs(p1.getx() * p2.gety() + p2.getx() * p3.gety() + p3.getx() * p1.gety() - p1.getx() * p3.gety() - p2.getx() * p1.gety() - p3.getx() * p2.gety());	//��������ʽ�����������
	}
	/* ���캯�� */
	triangle(int p1_x, int p1_y, int p2_x, int p2_y, int p3_x, int p3_y)
	{
		/* ��p1/p2/p3������ֱ�x,y����ֵ */
		p1.set(p1_x, p1_y);
		p2.set(p2_x, p2_y);
		p3.set(p3_x, p3_y);
	}
	/* ���Զ�����Ҫ�ĳ�Ա�������������ޣ��������ڷ�ʽʵ�֣�������������ݳ�Ա */

};

/* main������׼�� */
int main()
{
	if (1) {
		triangle tr(0, 0, 0, 1, 1, 0);  //������Ϊ(0,0) (0,1) (1,0)�������
		cout << "���������Ӧ���ǣ�0.5��ʵ���ǣ�" << tr.area() << endl;
	}

	if (1) {
		triangle tr(0, 2, -1, -1, 1, -1);  //������Ϊ(0,2) (-1,-1) (1,-1)�������
		cout << "���������Ӧ���ǣ�3��  ʵ���ǣ�" << tr.area() << endl;
	}

	if (1) {
		triangle tr(5, 5, -3, 1, 9, -2);  //������Ϊ(5,5) (-3,1) (9,-2)�������
		cout << "���������Ӧ���ǣ�36�� ʵ���ǣ�" << tr.area() << endl;
	}

	if (1) {
		triangle tr(0, 0, 1, 1, 2, 2);  //���㹲��
		cout << "���������Ӧ���ǣ�-1�� ʵ���ǣ�" << tr.area() << endl;
	}

	return 0;
}