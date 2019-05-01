//1850059 ��1�� ��־Զ

#include <iostream>
using namespace std;

const int months[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int minYear = 2000;
const int maxYear = 2030;

struct Date
{
	int year;
	int month;
	int day;
};

int days(struct Date &date)
{
	int count = date.day;
	int run4_nian2 = ((date.year % 4 == 0) && (date.year % 100 != 0)) || (date.year % 400 == 0);
	for (int i = 1; i < date.month; i++)
	{
		count += (i == 2 && run4_nian2 == 1) ? months[i] + 1 : months[i];
	}
	return count;
}

int main()
{
	bool run4_nian2;
	struct Date date;
	cout << "�������꣬�£���" << endl;
	while (1)
	{
		cin >> date.year >> date.month >> date.day;
		if (date.year < minYear || date.year > maxYear)
		{
			cout << "�������-��ݴ���" << endl;
			continue;
		}
		if (date.month <= 0 || date.month > 12)
		{
			cout << "�������-�·ݴ���" << endl;
			continue;
		}
		run4_nian2 = (((date.year % 4 == 0) && (date.year % 100 != 0)) || (date.year % 400 == 0));
		if (date.day <= 0 || (date.month == 2 && run4_nian2 && (date.day > months[date.month] + 1))
			|| (!(date.month == 2 && run4_nian2) && date.day > months[date.month]))
		{
			cout << "�������-�����µĹ�ϵ�Ƿ�" << endl;
			continue;
		}
		break;
	}
	int count = days(date);
	cout << date.year << "-" << date.month << "-" << date.day << "��" << date.year << "��ĵ�" << count << "��" << endl;
	return 0;
}