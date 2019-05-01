//1850059 计1班 杨志远

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
	printf("请输入年，月，日\n");
	while (1)
	{
		scanf("%d%d%d", &date.year, &date.month, &date.day);
		if (date.year < minYear || date.year > maxYear)
		{
			printf("输入错误-年份错误\n");
			continue;
		}
		if (date.month <= 0 || date.month > 12)
		{
			printf("输入错误-月份错误\n");
			continue;
		}
		run4_nian2 = ((date.year % 4 == 0) && (date.year % 100 != 0)) || (date.year % 400 == 0);
		if (date.day <= 0 || (date.month == 2 && run4_nian2 && (date.day > months[date.month] + 1))
			|| (!(date.month == 2 && run4_nian2) && date.day > months[date.month]))
		{
			printf("输入错误-日与月的关系非法\n");
			continue;
		}
		break;
	}
	int count = days(date);
	printf("%d-%d-%d是%d年的第%d天\n", date.year, date.month, date.day, date.year, count);
	return 0;
}
