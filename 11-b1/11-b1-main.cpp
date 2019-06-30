//1850059 计1班 杨志远

#include <stdio.h>
#include "11-b1-datetime.h"

#if defined(__linux) || defined(__linux__)
#include <sys/time.h>
void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (getchar() != '\n')
		;
	cout << endl << endl;
}
#else
#include <Windows.h>
#include <conio.h>
void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}
#endif

void test_Date()
{
	if (1)
	{
		cout << "Date类测试：" << endl;
		Date date1, date2(2019, 5, 31), date3(365), date4(1840, 4, 25), date5(-1), date6((int)4294967296);
		cout << "默认构造函数：" << endl;
		cout << "应该是1900-01-01   int=0" << endl;
		cout << "实际是" << date1 << "   int=" << (int)date1 << endl;
		cout << "三个参数的构造函数：" << endl;
		cout << "应该是2019-05-31   int=43614" << endl;
		cout << "实际是" << date2 << "   int=" << (int)date2 << endl;
		cout << "一个参数的构造函数：" << endl;
		cout << "应该是1900-12-31   int=364" << endl;
		cout << "实际是" << date3 << "   int=" << (int)date3 << endl;
		cout << "错误参数的构造函数：" << endl;
		cout << "应该是1900-01-01   int=0" << endl;
		cout << "实际是" << date4 << "   int=" << (int)date4 << endl;
		cout << "错误参数的构造函数：" << endl;
		cout << "应该是1900-01-01   int=0" << endl;
		cout << "实际是" << date5 << "   int=" << (int)date5 << endl;
		cout << "错误参数的构造函数：" << endl;
		cout << "应该是1900-01-01   int=0" << endl;
		cout << "实际是" << date6 << "   int=" << (int)date6 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "Date类测试：" << endl;
		Date date1, date2, date3, date4, date5, date6;
		cout << "无参set函数：" << endl;
		date1.set();
		cout << "应该是1900-01-01   int=0" << endl;
		cout << "实际是" << date1 << "   int=" << (int)date1 << endl;
		cout << "三个参数的set函数：" << endl;
		date2.set(2019, 5, 31);
		cout << "应该是2019-05-31   int=43614" << endl;
		cout << "实际是" << date2 << "   int=" << (int)date2 << endl;
		cout << "一个参数的set函数：" << endl;
		date3.set(365);
		cout << "应该是1900-12-31   int=364" << endl;
		cout << "实际是" << date3 << "   int=" << (int)date3 << endl;
		cout << "错误参数的set函数：" << endl;
		date4.set(1840, 4, 25);
		cout << "应该是1900-01-01   int=0" << endl;
		cout << "实际是" << date4 << "   int=" << (int)date4 << endl;
		cout << "错误参数的set函数：" << endl;
		date5.set(-1);
		cout << "应该是1900-01-01   int=0" << endl;
		cout << "实际是" << date5 << "   int=" << (int)date5 << endl;
		cout << "错误参数的set函数：" << endl;
		date6.set((int)4294967296);
		cout << "应该是1900-01-01   int=0" << endl;
		cout << "实际是" << date6 << "   int=" << (int)date6 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "Date类测试：" << endl;
		Date date1(1900, 1, 1), date2(2019, 5, 31), date3(2099, 12, 31), date4(1900, 1, 2);
		int step1 = 1, step2 = 5, step3 = 50;

		cout << "+号测试（包括越界）：" << endl;
		cout << "应该是1900-01-01 + 1 = 1900-01-02" << endl;
		cout << "实际是" << date1 << " + " << step1 << " = " << (date1 + step1) << endl;
		cout << "应该是2019-05-31 + 5 = 2019-06-05" << endl;
		cout << "实际是" << date2 << " + " << step2 << " = " << (date2 + step2) << endl;
		cout << "应该是2099-12-31 + 50 = 1900-02-19" << endl;
		cout << "实际是" << date3 << " + " << step3 << " = " << (date3 + step3) << endl;

		cout << "-号测试（包括越界）：" << endl;
		cout << "应该是1900-01-01 - 1 = 2099-12-31" << endl;
		cout << "实际是" << date1 << " - " << step1 << " = " << (date1 - step1) << endl;
		cout << "应该是2019-05-31 - 5 = 2019-05-26" << endl;
		cout << "实际是" << date2 << " - " << step2 << " = " << (date2 - step2) << endl;
		cout << "应该是2099-12-31 - 50 = 2099-11-11" << endl;
		cout << "实际是" << date3 << " - " << step3 << " = " << (date3 - step3) << endl;

		cout << "-号测试（包括越界）：" << endl;
		cout << "应该是2099-12-31 - 2019-05-31 = 29434" << endl;
		cout << "实际是" << date3 << " - " << date2 << " = " << (date3 - date2) << endl;
		cout << "应该是2019-05-31 - 2099-12-31 = -29434" << endl;
		cout << "实际是" << date2 << " - " << date3 << " = " << (date2 - date3) << endl;
		cout << "应该是2019-05-31 - 1900-01-01 = 43614" << endl;
		cout << "实际是" << date2 << " - " << date1 << " = " << (date2 - date1) << endl;
		cout << "应该是1900-01-01 - 2019-05-31 = -43614" << endl;
		cout << "实际是" << date1 << " - " << date2 << " = " << (date1 - date2) << endl;
		cout << "应该是2099-12-31 - 1900-01-01 = 73048" << endl;
		cout << "实际是" << date3 << " - " << date1 << " = " << (date3 - date1) << endl;
		cout << "应该是1900-01-01 - 2099-12-31 = -73048" << endl;
		cout << "实际是" << date1 << " - " << date3 << " = " << (date1 - date3) << endl;
		cout << "应该是1900-01-02 - 1900-01-01 = 1" << endl;
		cout << "实际是" << date4 << " - " << date1 << " = " << (date4 - date1) << endl;
		cout << "应该是1900-01-01 - 1900-01-02 = -1" << endl;
		cout << "实际是" << date1 << " - " << date4 << " = " << (date1 - date4) << endl;

		wait_for_enter();
	}

	if (1)
	{
		cout << "Date类测试：" << endl;
		Date date1(1900, 1, 1), date2(2019, 5, 31), date3(2099, 12, 31);
		cout << "前置++号测试（包括越界）：" << endl;
		cout << "++" << date1 << " = ";
		cout << ++date1 << endl;
		cout << "++" << date2 << " = ";
		cout << ++date2 << endl;
		cout << "++" << date3 << " = ";
		cout << ++date3 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "Date类测试：" << endl;
		Date date1(1900, 1, 1), date2(2019, 5, 31), date3(2099, 12, 31);
		cout << "前置--号测试（包括越界）：" << endl;
		cout << "--" << date1 << " = ";
		cout << --date1 << endl;
		cout << "--" << date2 << " = ";
		cout << --date2 << endl;
		cout << "--" << date3 << " = ";
		cout << --date3 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "Date类测试：" << endl;
		Date date1(1900, 1, 1), date2(2019, 5, 31), date3(2099, 12, 31);
		cout << "后置++号测试（包括越界）：" << endl;
		cout << date1++ << "++ = " << date1 << endl;
		cout << date2++ << "++ = " << date2 << endl;
		cout << date3++ << "++ = " << date3 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "Date类测试：" << endl;
		Date date1(1900, 1, 1), date2(2019, 5, 31), date3(2099, 12, 31);
		cout << "后置--号测试（包括越界）：" << endl;
		cout << date1-- << "-- = " << date1 << endl;
		cout << date2-- << "-- = " << date2 << endl;
		cout << date3-- << "-- = " << date3 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "Date类测试：" << endl;
		Date date1(1900, 1, 1), date2(2019, 5, 31), date3(2099, 12, 31);
		cout << "逻辑运算符号运算符测试：" << endl;
		cout << "应该为 101100 010101 011010" << endl;
		cout << date1 << " == " << date1 << " 结果 = " << (date1 == date1) << endl;
		cout << date1 << " != " << date1 << " 结果 = " << (date1 != date1) << endl;
		cout << date1 << " >= " << date1 << " 结果 = " << (date1 >= date1) << endl;
		cout << date1 << " <= " << date1 << " 结果 = " << (date1 <= date1) << endl;
		cout << date1 << " >  " << date1 << " 结果 = " << (date1 > date1) << endl;
		cout << date1 << " <  " << date1 << " 结果 = " << (date1 < date1) << endl;
		cout << endl;
		cout << date1 << " == " << date2 << " 结果 = " << (date1 == date2) << endl;
		cout << date1 << " != " << date2 << " 结果 = " << (date1 != date2) << endl;
		cout << date1 << " >= " << date2 << " 结果 = " << (date1 >= date2) << endl;
		cout << date1 << " <= " << date2 << " 结果 = " << (date1 <= date2) << endl;
		cout << date1 << " >  " << date2 << " 结果 = " << (date1 > date2) << endl;
		cout << date1 << " <  " << date2 << " 结果 = " << (date1 < date2) << endl;
		cout << endl;
		cout << date2 << " == " << date1 << " 结果 = " << (date2 == date1) << endl;
		cout << date2 << " != " << date1 << " 结果 = " << (date2 != date1) << endl;
		cout << date2 << " >= " << date1 << " 结果 = " << (date2 >= date1) << endl;
		cout << date2 << " <= " << date1 << " 结果 = " << (date2 <= date1) << endl;
		cout << date2 << " >  " << date1 << " 结果 = " << (date2 > date1) << endl;
		cout << date2 << " <  " << date1 << " 结果 = " << (date2 < date1) << endl;
		wait_for_enter();
	}
}

void test_Time()
{
	if (1)
	{
		cout << "Time类测试：" << endl;
		Time time1, time2(15, 30, 2), time3(2048), time4(23, 99, 5), time5(-10), time6(999999); 
		cout << "默认构造函数：" << endl;
		cout << "应该是00:00:00   int=0" << endl;
		cout << "实际是" << time1 << "   int=" << (int)time1 << endl;
		cout << "三个参数的构造函数：" << endl;
		cout << "应该是15:30:02   int=55802" << endl;
		cout << "实际是" << time2 << "   int=" << (int)time2 << endl;
		cout << "一个参数的构造函数：" << endl;
		cout << "应该是00:34:08   int=2048" << endl;
		cout << "实际是" << time3 << "   int=" << (int)time3 << endl;
		cout << "错误参数的构造函数：" << endl;
		cout << "应该是00:00:00   int=0" << endl;
		cout << "实际是" << time4 << "   int=" << (int)time4 << endl;
		cout << "错误参数的构造函数：" << endl;
		cout << "应该是00:00:00   int=0" << endl;
		cout << "实际是" << time5 << "   int=" << (int)time5 << endl;
		cout << "错误参数的构造函数：" << endl;
		cout << "应该是00:00:00   int=0" << endl;
		cout << "实际是" << time6 << "   int=" << (int)time6 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "Time类测试：" << endl;
		Time time1, time2, time3, time4, time5, time6;
		cout << "无参set函数：" << endl;
		time1.set();
		cout << "应该是00:00:00   int=0" << endl;
		cout << "实际是" << time1 << "   int=" << (int)time1 << endl;
		cout << "三个参数的set函数：" << endl;
		time2.set(15, 30, 2);
		cout << "应该是15:30:02   int=55802" << endl;
		cout << "实际是" << time2 << "   int=" << (int)time2 << endl;
		cout << "一个参数的set函数：" << endl;
		time3.set(2048);
		cout << "应该是00:34:08   int=2048" << endl;
		cout << "实际是" << time3 << "   int=" << (int)time3 << endl;
		cout << "错误参数的set函数：" << endl;
		time4.set(23, 99, 5);
		cout << "应该是00:00:00   int=0" << endl;
		cout << "实际是" << time4 << "   int=" << (int)time4 << endl;
		cout << "错误参数的set函数：" << endl;
		time5.set(-10);
		cout << "应该是00:00:00   int=0" << endl;
		cout << "实际是" << time5 << "   int=" << (int)time5 << endl;
		cout << "错误参数的set函数：" << endl;
		time6.set(999999);
		cout << "应该是00:00:00   int=0" << endl;
		cout << "实际是" << time6 << "   int=" << (int)time6 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "Time类测试：" << endl;
		Time time1(0, 0, 0), time2(15, 30, 2), time3(23, 59, 59);
		int step1 = 100, step2 = 500, step3 = 1000;

		cout << "+号测试（包括越界）：" << endl;
		cout << "应该是00:00:00 + 100 = 00:01:40" << endl;
		cout << "实际是" << time1 << " + " << step1 << " = " << (time1 + step1) << endl;
		cout << "应该是15:30:02 + 500 = 15:38:22" << endl;
		cout << "实际是" << time2 << " + " << step2 << " = " << (time2 + step2) << endl;
		cout << "应该是23:59:59 + 1000 = 00:16:39" << endl;
		cout << "实际是" << time3 << " + " << step3 << " = " << (time3 + step3) << endl;

		cout << "-号测试（包括越界）：" << endl;
		cout << "应该是00:00:00 - 100 = 23:58:20" << endl;
		cout << "实际是" << time1 << " - " << step1 << " = " << (time1 - step1) << endl;
		cout << "应该是15:30:02 - 500 = 15:21:42" << endl;
		cout << "实际是" << time2 << " - " << step2 << " = " << (time2 - step2) << endl;
		cout << "应该是23:59:59 - 1000 = 23:43:19" << endl;
		cout << "实际是" << time3 << " - " << step3 << " = " << (time3 - step3) << endl;

		cout << "-号测试（包括越界）：" << endl;
		cout << "应该是23:59:59 - 15:30:02 = 30597" << endl;
		cout << "实际是" << time3 << " - " << time2 << " = " << (time3 - time2) << endl;
		cout << "应该是15:30:02 - 23:59:59 = -30597" << endl;
		cout << "实际是" << time2 << " - " << time3 << " = " << (time2 - time3) << endl;
		cout << "应该是15:30:02 - 00:00:00 = 55802" << endl;
		cout << "实际是" << time2 << " - " << time1 << " = " << (time2 - time1) << endl;
		cout << "应该是00:00:00 - 15:30:02 = -55802" << endl;
		cout << "实际是" << time1 << " - " << time2 << " = " << (time1 - time2) << endl;
		cout << "应该是23:59:59 - 00:00:00 = 86399" << endl;
		cout << "实际是" << time3 << " - " << time1 << " = " << (time3 - time1) << endl;
		cout << "应该是00:00:00 - 23:59:59 = -86399" << endl;
		cout << "实际是" << time1 << " - " << time3 << " = " << (time1 - time3) << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "Time类测试：" << endl;
		Time time1(0, 0, 0), time2(15, 30, 59), time3(23, 59, 59);
		cout << "前置++号测试（包括越界）：" << endl;
		cout << "++" << time1 << " = ";
		cout << ++time1 << endl;
		cout << "++" << time2 << " = ";
		cout << ++time2 << endl;
		cout << "++" << time3 << " = ";
		cout << ++time3 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "Time类测试：" << endl;
		Time time1(0, 0, 0), time2(15, 30, 0), time3(23, 59, 59);
		cout << "前置--号测试（包括越界）：" << endl;
		cout << "--" << time1 << " = ";
		cout << --time1 << endl;
		cout << "--" << time2 << " = ";
		cout << --time2 << endl;
		cout << "--" << time3 << " = ";
		cout << --time3 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "Time类测试：" << endl;
		Time time1(0, 0, 0), time2(15, 30, 59), time3(23, 59, 59);
		cout << "后置++号测试（包括越界）：" << endl;
		cout << time1++ << "++ = " << time1 << endl;
		cout << time2++ << "++ = " << time2 << endl;
		cout << time3++ << "++ = " << time3 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "Time类测试：" << endl;
		Time time1(0, 0, 0), time2(15, 30, 0), time3(23, 59, 59);
		cout << "后置--号测试（包括越界）：" << endl;
		cout << time1-- << "-- = " << time1 << endl;
		cout << time2-- << "-- = " << time2 << endl;
		cout << time3-- << "-- = " << time3 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "Time类测试：" << endl;
		Time time1(0, 0, 0), time2(15, 30, 2), time3(23, 59, 59);
		cout << "逻辑运算符号运算符测试：" << endl;
		cout << "应该为 101100 010101 011010" << endl;
		cout << time1 << " == " << time1 << " 结果 = " << (time1 == time1) << endl;
		cout << time1 << " != " << time1 << " 结果 = " << (time1 != time1) << endl;
		cout << time1 << " >= " << time1 << " 结果 = " << (time1 >= time1) << endl;
		cout << time1 << " <= " << time1 << " 结果 = " << (time1 <= time1) << endl;
		cout << time1 << " >  " << time1 << " 结果 = " << (time1 > time1) << endl;
		cout << time1 << " <  " << time1 << " 结果 = " << (time1 < time1) << endl;
		cout << endl;
		cout << time1 << " == " << time2 << " 结果 = " << (time1 == time2) << endl;
		cout << time1 << " != " << time2 << " 结果 = " << (time1 != time2) << endl;
		cout << time1 << " >= " << time2 << " 结果 = " << (time1 >= time2) << endl;
		cout << time1 << " <= " << time2 << " 结果 = " << (time1 <= time2) << endl;
		cout << time1 << " >  " << time2 << " 结果 = " << (time1 > time2) << endl;
		cout << time1 << " <  " << time2 << " 结果 = " << (time1 < time2) << endl;
		cout << endl;
		cout << time2 << " == " << time1 << " 结果 = " << (time2 == time1) << endl;
		cout << time2 << " != " << time1 << " 结果 = " << (time2 != time1) << endl;
		cout << time2 << " >= " << time1 << " 结果 = " << (time2 >= time1) << endl;
		cout << time2 << " <= " << time1 << " 结果 = " << (time2 <= time1) << endl;
		cout << time2 << " >  " << time1 << " 结果 = " << (time2 > time1) << endl;
		cout << time2 << " <  " << time1 << " 结果 = " << (time2 < time1) << endl;
		wait_for_enter();
	}
}

void test_DateTime()
{
	if (1)
	{
		cout << "DateTime类测试：" << endl;
		DateTime dt1, dt2(2019, 5, 31, 15, 30, 2), dt3(2019, 5, 31), dt4(4294967296ll), dt5(1940, 41, 2, 12, 30, 15), dt6(-1000), dt7(6311433600ll);
		cout << "默认构造函数：" << endl;
		cout << "应该是1900-01-01 00:00:00   long long=0" << endl;
		cout << "实际是" << dt1 << "   long long=" << (long long)dt1 << endl;
		cout << "六个参数的构造函数：" << endl;
		cout << "应该是2019-05-31 15:30:02   long long=3768305402" << endl;
		cout << "实际是" << dt2 << "   long long=" << (long long)dt2 << endl;
		cout << "三个参数的构造函数：" << endl;
		cout << "实际是2019-05-31 00:00:00   long long=3768249600" << endl;
		cout << "实际是" << dt3 << "   long long=" << (long long)dt3 << endl;
		cout << "一个参数的构造函数：" << endl;
		cout << "应该是2036-02-07 06:28:16   long long=4294967296" << endl;
		cout << "实际是" << dt4 << "   long long=" << (long long)dt4 << endl;
		cout << "错误参数的构造函数：" << endl;
		cout << "应该是1900-01-01 00:00:00   long long=0" << endl;
		cout << "实际是" << dt5 << "   long long=" << (long long)dt5 << endl;
		cout << "错误参数的构造函数：" << endl;
		cout << "应该是1900-01-01 00:00:00   long long=0" << endl;
		cout << "实际是" << dt6 << "   long long=" << (long long)dt6 << endl;
		cout << "错误参数的构造函数：" << endl;
		cout << "应该是1900-01-01 00:00:00   long long=0" << endl;
		cout << "实际是" << dt7 << "   long long=" << (long long)dt7 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "DateTime类测试：" << endl;
		DateTime dt1, dt2, dt3, dt4, dt5, dt6, dt7;
		cout << "无参set函数：" << endl;
		dt1.set();
		dt2.set(2019, 5, 31, 15, 30, 2);
		dt3.set(2019, 5, 31);
		dt4.set(4294967296ll);
		dt5.set(1940, 41, 2, 12, 30, 15);
		dt6.set(-1000);
		dt7.set(6311433600ll);
		cout << "默认set函数：" << endl;
		cout << "应该是1900-01-01 00:00:00   long long=0" << endl;
		cout << "实际是" << dt1 << "   long long=" << (long long)dt1 << endl;
		cout << "六个参数的set函数：" << endl;
		cout << "应该是2019-05-31 15:30:02   long long=3768305402" << endl;
		cout << "实际是" << dt2 << "   long long=" << (long long)dt2 << endl;
		cout << "三个参数的set函数：" << endl;
		cout << "应该是2019-05-31 00:00:00   long long=3768249600" << endl;
		cout << "实际是" << dt3 << "   long long=" << (long long)dt3 << endl;
		cout << "一个参数的set函数：" << endl;
		cout << "应该是2036-02-07 06:28:16   long long=4294967296" << endl;
		cout << "实际是" << dt4 << "   long long=" << (long long)dt4 << endl;
		cout << "错误参数的set函数：" << endl;
		cout << "应该是1900-01-01 00:00:00   long long=0" << endl;
		cout << "实际是" << dt5 << "   long long=" << (long long)dt5 << endl;
		cout << "错误参数的set函数：" << endl;
		cout << "应该是1900-01-01 00:00:00   long long=0" << endl;
		cout << "实际是" << dt6 << "   long long=" << (long long)dt6 << endl;
		cout << "错误参数的set函数：" << endl;
		cout << "应该是1900-01-01 00:00:00   long long=0" << endl;
		cout << "实际是" << dt7 << "   long long=" << (long long)dt7 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "DateTime类测试：" << endl;
		DateTime dt1(1900, 1, 1, 0, 0, 0), dt2(2019, 5, 31, 15, 30, 1), dt3(2099, 12, 31, 23, 59, 59), dt4(2019, 5, 31, 15, 30, 2);
		int step1 = 100, step2 = 5000000ll, step3 = 200000000ll;
		cout << "+号测试（包括越界）：" << endl;

		cout << "应该是1900-01-01 00:00:00 + 100 = 1900-01-01 00:01:40" << endl;
		cout << "实际是" << dt1 << " + " << step1 << " = " << (dt1 + step1) << endl;
		cout << "应该是2019-05-31 15:30:01 + 5000000 = 2019-07-28 12:23:21" << endl;
		cout << "实际是" << dt2 << " + " << step2 << " = " << (dt2 + step2) << endl;
		cout << "应该是2099-12-31 23:59:59 + 200000000 = 1906-05-04 19:33:19" << endl;
		cout << "实际是" << dt3 << " + " << step3 << " = " << (dt3 + step3) << endl;

		cout << "-号测试（包括越界）：" << endl;
		cout << "应该是1900-01-01 00:00:00 - 100 = 2099-12-31 23:58:20" << endl;
		cout << "实际是" << dt1 << " - " << step1 << " = " << (dt1 - step1) << endl;
		cout << "应该是2019-05-31 15:30:01 - 5000000 = 2019-04-03 18:36:41" << endl;
		cout << "实际是" << dt2 << " - " << step2 << " = " << (dt2 - step2) << endl;
		cout << "应该是2099-12-31 23:59:59 - 200000000 = 2093-08-30 04:26:39" << endl;
		cout << "实际是" << dt3 << " - " << step3 << " = " << (dt3 - step3) << endl;

		cout << "-号测试（包括越界）：" << endl;
		cout << "应该是2099-12-31 23:59:59 - 2019-05-31 15:30:01 = 2543128198" << endl;
		cout << "实际是" << dt3 << " - " << dt2 << " = " << (dt3 - dt2) << endl;
		cout << "应该是2019-05-31 15:30:01 - 2099-12-31 23:59:59 = -2543128198" << endl;
		cout << "实际是" << dt2 << " - " << dt3 << " = " << (dt2 - dt3) << endl;
		cout << "应该是2019-05-31 15:30:01 - 1900-01-01 00:00:00 = 3768305401" << endl;
		cout << "实际是" << dt2 << " - " << dt1 << " = " << (dt2 - dt1) << endl;
		cout << "应该是1900-01-01 00:00:00 - 2019-05-31 15:30:01 = -3768305401" << endl;
		cout << "实际是" << dt1 << " - " << dt2 << " = " << (dt1 - dt2) << endl;
		cout << "应该是2099-12-31 23:59:59 - 1900-01-01 00:00:00 = 6311433599" << endl;
		cout << "实际是" << dt3 << " - " << dt1 << " = " << (dt3 - dt1) << endl;
		cout << "应该是1900-01-01 00:00:00 - 2099-12-31 23:59:59 = -6311433599" << endl;
		cout << "实际是" << dt1 << " - " << dt3 << " = " << (dt1 - dt3) << endl;
		cout << "应该是2019-05-31 15:30:02 - 2019-05-31 15:30:01 = 1" << endl;
		cout << "实际是" << dt4 << " - " << dt2 << " = " << (dt4 - dt2) << endl;
		cout << "应该是2019-05-31 15:30:01 - 2019-05-31 15:30:02 = -1" << endl;
		cout << "实际是" << dt2 << " - " << dt4 << " = " << (dt2 - dt4) << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "DateTime类测试：" << endl;
		DateTime dt1(1900, 1, 1, 0, 0, 0), dt2(2019, 5, 30, 23, 59, 59), dt3(2099, 12, 31, 23, 59, 59);
		cout << "前置++号测试（包括越界）：" << endl;
		cout << "++" << dt1 << " = ";
		cout << ++dt1 << endl;
		cout << "++" << dt2 << " = ";
		cout << ++dt2 << endl;
		cout << "++" << dt3 << " = ";
		cout << ++dt3 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "DateTime类测试：" << endl;
		DateTime dt1(1900, 1, 1, 0, 0, 0), dt2(2019, 5, 31, 0, 0, 0), dt3(2099, 12, 31, 23, 59, 59);
		cout << "前置--号测试（包括越界）：" << endl;
		cout << "--" << dt1 << " = ";
		cout << --dt1 << endl;
		cout << "--" << dt2 << " = ";
		cout << --dt2 << endl;
		cout << "--" << dt3 << " = ";
		cout << --dt3 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "DateTime类测试：" << endl;
		DateTime dt1(1900, 1, 1, 0, 0, 0), dt2(2019, 5, 30, 23, 59, 59), dt3(2099, 12, 31, 23, 59, 59);
		cout << "后置++号测试（包括越界）：" << endl;
		cout << dt1++ << "++ = " << dt1 << endl;
		cout << dt2++ << "++ = " << dt2 << endl;
		cout << dt3++ << "++ = " << dt3 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "DateTime类测试：" << endl;
		DateTime dt1(1900, 1, 1, 0, 0, 0), dt2(2019, 5, 31, 0, 0, 0), dt3(2099, 12, 31, 23, 59, 59);
		cout << "后置--号测试（包括越界）：" << endl;
		cout << dt1-- << "-- = " << dt1 << endl;
		cout << dt2-- << "-- = " << dt2 << endl;
		cout << dt3-- << "-- = " << dt3 << endl;
		wait_for_enter();
	}

	if (1)
	{
		cout << "DateTime类测试：" << endl;
		DateTime dt1(1900, 1, 1, 0, 0, 0), dt2(2019, 5, 31, 15, 30, 2), dt3(2099, 12, 31, 23, 59, 59);
		cout << "逻辑运算符号运算符测试：" << endl;
		cout << "应该为 101100 010101 011010" << endl;
		cout << dt1 << " == " << dt1 << " 结果 = " << (dt1 == dt1) << endl;
		cout << dt1 << " != " << dt1 << " 结果 = " << (dt1 != dt1) << endl;
		cout << dt1 << " >= " << dt1 << " 结果 = " << (dt1 >= dt1) << endl;
		cout << dt1 << " <= " << dt1 << " 结果 = " << (dt1 <= dt1) << endl;
		cout << dt1 << " >  " << dt1 << " 结果 = " << (dt1 > dt1) << endl;
		cout << dt1 << " <  " << dt1 << " 结果 = " << (dt1 < dt1) << endl;
		cout << endl;
		cout << dt1 << " == " << dt2 << " 结果 = " << (dt1 == dt2) << endl;
		cout << dt1 << " != " << dt2 << " 结果 = " << (dt1 != dt2) << endl;
		cout << dt1 << " >= " << dt2 << " 结果 = " << (dt1 >= dt2) << endl;
		cout << dt1 << " <= " << dt2 << " 结果 = " << (dt1 <= dt2) << endl;
		cout << dt1 << " >  " << dt2 << " 结果 = " << (dt1 > dt2) << endl;
		cout << dt1 << " <  " << dt2 << " 结果 = " << (dt1 < dt2) << endl;
		cout << endl;
		cout << dt2 << " == " << dt1 << " 结果 = " << (dt2 == dt1) << endl;
		cout << dt2 << " != " << dt1 << " 结果 = " << (dt2 != dt1) << endl;
		cout << dt2 << " >= " << dt1 << " 结果 = " << (dt2 >= dt1) << endl;
		cout << dt2 << " <= " << dt1 << " 结果 = " << (dt2 <= dt1) << endl;
		cout << dt2 << " >  " << dt1 << " 结果 = " << (dt2 > dt1) << endl;
		cout << dt2 << " <  " << dt1 << " 结果 = " << (dt2 < dt1) << endl;
		wait_for_enter();
	}
}

int main()
{
	test_Date();
	test_Time();
	test_DateTime();
	return 0;
}