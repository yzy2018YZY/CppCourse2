//1850059 ��1�� ��־Զ

#include <iostream>
using namespace std;

const int N = 3;

class Cube
{
	double length;
	double width;
	double height;
	double vol;	//���
public:
	bool input();
	void volumn();
	void output();
};

bool Cube::input()
{
	double _length, _width, _height;
	cin >> _length >> _width >> _height;
	//if (_length < 0 || _width < 0 || _height < 0)	//��ֹ������������
	//	return false;
	this->length = _length;
	this->width = _width;
	this->height = _height;
	return true;
}

void Cube::volumn()
{
	vol = length * width * height;
}

void Cube::output()
{
	cout << vol << endl;
}

int main()
{
	Cube cube;
	for (int i = 0; i < N; i++)
	{
		cube.input();
		cube.volumn();
		cube.output();
	}
	return 0;
}