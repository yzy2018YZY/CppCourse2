//1850059 ��1�� ��־Զ

#include <iostream>
using namespace std;

class Days {
private:
	int year;
	int month;
	int day;
	//�����������private���ݳ�Ա�⣬������������κ����͵����ݳ�Ա

	int is_leap_year();  //�ж��Ƿ����꣬�ǣ�����1  /   �񣺷���0
public:
	int calc_days();     //�����ǵ���ĵڼ���
	/* ������Բ���������Ҫ�����Ա�����Ķ���(����ʵ��)���������� */
	Days(int _year, int _month, int _day);
};

/* �˴��������Ա����������ʵ�� */

int Days::is_leap_year()
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return 1;
	else
		return 0;
}

int Days::calc_days()
{
	const int daysOfMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int days = 0;
	if ((month == 2 && ((is_leap_year() && day > daysOfMonth[2] + 1) || (!is_leap_year() && day > daysOfMonth[2]))) || month < 1 || month > 12 || day > daysOfMonth[month])
		return -1;
	for (int i = 1; i < month; i++)
	{
		days += daysOfMonth[i];
	}
	if(month >= 3 && is_leap_year())
		days++;
	return days + day;
}

Days::Days(int _year, int _month, int _day)
{
	this->year = _year;
	this->month = _month;
	this->day = _day;
}

/* main������׼�� */
int main()
{
	if (1) {
		Days d1(2012, 3, 18);
		cout << "Ӧ�����78�� ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 12, 31);
		cout << "Ӧ�����365��ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2012, 12, 31);
		cout << "Ӧ�����366��ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 2, 29);
		cout << "Ӧ�����-1�� ʵ���ǣ�" << d1.calc_days() << endl;
	}

	return 0;
}