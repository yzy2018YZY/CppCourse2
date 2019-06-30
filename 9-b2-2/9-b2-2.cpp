//1850059 计1班 杨志远

#include <iostream>
#include <cmath>
using namespace std;

class triangle;  //类的提前声明，思考一下，放在这里的目的是为什么
class point {
private:
	int x;
	int y;
public:
	/* 仅允许在此添加一个成员函数【仅限1个】,要求体内实现 */
	bool set(int& _x, int& _y)
	{
		this->x = _x;
		this->y = _y;
		return true;
	}
	/* 除上面允许的那个成员函数外，不再允许添加任何的数据成员和成员函数，但可以根据需要添加其它内容 */
	friend triangle;
};

class triangle {
private:
	point p1;
	point p2;
	point p3;
public:
	/* 根据需要补充相应的语句后完成area函数(形参为空，不准改)，要求：如果三点能构成三角形，则返回面积，否则返回 -1 */
	double area()
	{
		int x1 = p1.x, x2 = p2.x, x3 = p3.x, y1 = p1.y, y2 = p2.y, y3 = p3.y;
		double s1 = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));	//p1和p2之间的距离
		double s2 = sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3));	//p2和p3之间的距离
		double s3 = sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));	//p3和p1之间的距离
		if (s1 + s2 <= s3 || s2 + s3 <= s1 || s3 + s1 <= s2)	//数据不合法
			return -1;
		else
			return 0.5 * fabs(x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2);	//三阶行列式求三角形面积
	}
	/* 构造函数 */
	triangle(int p1_x, int p1_y, int p2_x, int p2_y, int p3_x, int p3_y)
	{
		/* 给p1/p2/p3三个点分别赋x,y坐标值 */
		p1.set(p1_x, p1_y);
		p2.set(p2_x, p2_y);
		p3.set(p3_x, p3_y);
	}
	/* 可以定义需要的成员函数，数量不限，并以体内方式实现，不允许添加数据成员 */

};

/* main函数不准动 */
int main()
{
	if (1) {
		triangle tr(0, 0, 0, 1, 1, 0);  //三角形为(0,0) (0,1) (1,0)三点组成
		cout << "三角形面积应该是：0.5，实际是：" << tr.area() << endl;
	}

	if (1) {
		triangle tr(0, 2, -1, -1, 1, -1);  //三角形为(0,2) (-1,-1) (1,-1)三点组成
		cout << "三角形面积应该是：3，  实际是：" << tr.area() << endl;
	}

	if (1) {
		triangle tr(5, 5, -3, 1, 9, -2);  //三角形为(5,5) (-3,1) (9,-2)三点组成
		cout << "三角形面积应该是：36， 实际是：" << tr.area() << endl;
	}

	if (1) {
		triangle tr(0, 0, 1, 1, 2, 2);  //三点共线
		cout << "三角形面积应该是：-1， 实际是：" << tr.area() << endl;
	}

	return 0;
}