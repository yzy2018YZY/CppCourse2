//1850059 ��1�� ��־Զ

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

const int months[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int minYear = 2000;
const int maxYear = 2030;

struct Date
{
	int year;
	int month;
	int day;
};

int days(struct Date date)
{
	int count = date.day;
	int run4_nian2 = ((date.year % 4 == 0) && (date.year % 100 != 0)) || (date.year % 400 == 0);
	int i; 
	for (i = 1; i < date.month; i++)
	{
		count += (i == 2 && run4_nian2 == 1) ? months[i] + 1 : months[i];
	}
	return count;
}

int main()
{
	struct Date date;
	int run4_nian2;
	printf("�������꣬�£���\n");
	while (1)
	{
		scanf("%d%d%d", &date.year, &date.month, &date.day);
		if (date.year < minYear || date.year > maxYear)
		{
			printf("�������-��ݴ���\n");
			continue;
		}
		if (date.month <= 0 || date.month > 12)
		{
			printf("�������-�·ݴ���\n");
			continue;
		}
		run4_nian2 = ((date.year % 4 == 0) && (date.year % 100 != 0)) || (date.year % 400 == 0);
		if (date.day <= 0 || (date.month == 2 && run4_nian2 && (date.day > months[date.month] + 1))
			|| (!(date.month == 2 && run4_nian2) && date.day > months[date.month]))
		{
			printf("�������-�����µĹ�ϵ�Ƿ�\n");
			continue;
		}
		break;
	}
	int count = days(date);
	printf("%d-%d-%d��%d��ĵ�%d��\n", date.year, date.month, date.day, date.year, count);
	return 0;
}
