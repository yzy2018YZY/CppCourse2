//1850059 计1班 杨志远

#include <iostream>
#include <string.h>
using namespace std;

class matrix {
private:
	int value[2][3];
	//除此之外不允许再添加数据成员
public:
	matrix operator+(const matrix &b);

	/* ----根据需要添加除数据成员以外的定义，数量不限---- */
	matrix(const int(*p)[3] = NULL);
	friend istream& operator>>(istream &in, matrix &p);
	friend ostream& operator<<(ostream &out, const matrix &p);
};

/* ----给出类成员函数的体外实现---- */

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

/* ----main函数不准动---- */
int main()
{
	matrix m1, m2, m3;

	cout << "请输入矩阵m1的值(共2行3列，按先行后列的顺序输入)" << endl;
	cin >> m1;
	cout << "请输入矩阵m2的值(共2行3列，按先行后列的顺序输入)" << endl;
	cin >> m2;

	cout << "初始矩阵m1的值：" << endl;
	cout << m1 << endl;
	cout << "初始矩阵m2的值：" << endl;
	cout << m2 << endl;
	cout << "相加后矩阵m3的值：" << endl;
	cout << (m3 = m1 + m2) << endl;

	return 0;
}