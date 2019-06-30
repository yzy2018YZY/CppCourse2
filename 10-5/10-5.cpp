//1850059 ��1�� ��־Զ

#include <iostream>
#include <string.h>
using namespace std;

class matrix {
private:
	int value[2][3];
	//����֮�ⲻ������������ݳ�Ա
public:
	matrix operator+(const matrix &b);

	/* ----������Ҫ��ӳ����ݳ�Ա����Ķ��壬��������---- */
	matrix(const int(*p)[3] = NULL);
	friend istream& operator>>(istream &in, matrix &p);
	friend ostream& operator<<(ostream &out, const matrix &p);
};

/* ----�������Ա����������ʵ��---- */

matrix::matrix(const int(*p)[3])
{
	if (p)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->value[i][j] = p[i][j];
			}
		}
	}
	else
		memset(this->value, 0, sizeof(int) * 2 * 3);
}

istream& operator>>(istream &in, matrix &p)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			in >> p.value[i][j];
		}
	}
	return in;
}

ostream& operator<<(ostream &out, const matrix &p)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			out << p.value[i][j] << " ";
		}
		out << endl;
	}
	return out;
}

matrix matrix::operator+(const matrix &b)
{
	matrix temp;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp.value[i][j] = this->value[i][j] + b.value[i][j];
		}
	}
	return temp;
}

/* ----main������׼��---- */
int main()
{
	matrix m1, m2, m3;

	cout << "���������m1��ֵ(��2��3�У������к��е�˳������)" << endl;
	cin >> m1;
	cout << "���������m2��ֵ(��2��3�У������к��е�˳������)" << endl;
	cin >> m2;

	cout << "��ʼ����m1��ֵ��" << endl;
	cout << m1 << endl;
	cout << "��ʼ����m2��ֵ��" << endl;
	cout << m2 << endl;
	cout << "��Ӻ����m3��ֵ��" << endl;
	cout << (m3 = m1 + m2) << endl;

	return 0;
}