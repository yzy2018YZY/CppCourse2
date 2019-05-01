/* 1850059 ��1�� ��־Զ */
#define _CRT_SECURE_NO_WARNINGS		//ʹ����VS2017��Ϊunsafe�ĺ���
#include <iostream>
#include <ctime>
#include <cstring>
#include <conio.h>
#include <chrono>
#include <Windows.h>
using namespace std;

struct tj_time {
	int tj_year;	//��ʾ���
	int tj_month;	//��ʾ��(1-12)
	int tj_day;		//��ʾ��(1-28/29/30/31)
	int tj_hour;	//��ʾСʱ(0-23)
	int tj_minute;	//��ʾ��(0-59)
	int tj_second;	//��ʾ��(0-59)
};

/* �����ڴ˶���������Ҫ�ĺ��� */

const int months[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void calc_day(tj_time &result, int days, bool run4_nian2)
{
	for (int k = 0; k < days; k++)
	{
		if ((result.tj_month == 2 && run4_nian2 && result.tj_day > months[2] + 1)
			|| (!(result.tj_month == 2 && run4_nian2) && result.tj_day > months[result.tj_month]))
		{
			if (result.tj_month == 2 && run4_nian2 && result.tj_day > months[2] + 1)
			{
				result.tj_day -= months[2] + 1;
			}
			if (!(result.tj_month == 2 && run4_nian2) && result.tj_day > months[result.tj_month])
			{
				result.tj_day -= months[result.tj_month];
			}
			result.tj_month++;
		}
		if (result.tj_month > 12)
		{
			result.tj_month -= 12;
			result.tj_year++;
			run4_nian2 = ((result.tj_year % 4 == 0) && (result.tj_year % 100 != 0)) || (result.tj_year % 400 == 0);
		}
	}
}

bool is_daylight(const tj_time &result, const TIME_ZONE_INFORMATION &tzi, bool north)
{
	bool over  = (result.tj_month > tzi.DaylightDate.wMonth || (result.tj_month == tzi.DaylightDate.wMonth && (result.tj_day > tzi.DaylightDate.wDay || (result.tj_day == tzi.DaylightDate.wDay && result.tj_hour >= tzi.DaylightDate.wHour))));
	bool under = (result.tj_month < tzi.StandardDate.wMonth || (result.tj_month == tzi.StandardDate.wMonth && (result.tj_day < tzi.StandardDate.wDay || (result.tj_day == tzi.DaylightDate.wDay && result.tj_hour <= tzi.DaylightDate.wHour))));
	if (north)
	{
		if (tzi.DaylightDate.wMonth < tzi.StandardDate.wMonth && over && under)
			return true;
		else 
			return false;
	}
	else
	{
		if (tzi.DaylightDate.wMonth > tzi.StandardDate.wMonth && (over || under))
			return true;
		else
			return false;
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ʾ���ȴ��س���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void wait_for_enter(const char *prompt = "")
{
	if (strlen(prompt) == 0)
		cout << endl << "���س�������";
	else
		cout << endl << prompt << "�����س�������";

	while (_getch() != '\r')
		;
	cout << endl << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ϵͳ��ת��������������ֵת��Ϊ�뱾�����ƵĽṹ�岢���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void system_time_output(const time_t input_time)  //time_t�ı�����64λ�޷�������
{
	struct tm *tt;	//struct tm Ϊϵͳ����Ľṹ��

	tt = localtime(&input_time);	//localtimeΪϵͳ����

	/* tm_*** Ϊstruct tm�еĳ�Ա���ͱ����struct tj_time��������ݲ���ȫ���ϣ����庬���Լ������������ */
	cout << tt->tm_year + 1900 << '-' << tt->tm_mon + 1 << '-' << tt->tm_mday << ' ' << tt->tm_hour << ':' << tt->tm_min << ':' << tt->tm_sec << endl;

	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��Զ���ת������������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void tj_time_output(struct tj_time *tp)
{
	/* ʵ���Զ���ṹ������������ʽ��system_time_output��ͬ */
	cout << tp->tj_year << '-' << tp->tj_month << '-' << tp->tj_day << ' ' << tp->tj_hour << ':' << tp->tj_minute << ':' << tp->tj_second << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��Զ���ת������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
struct tj_time *tj_time_convert(int input_time)
{
	static struct tj_time result;	//���徲̬�ֲ���������׼��

	//time.h�ĺ������޷���������ʱ
	//time_t timeCount = time(0);
	//tm *gmt = gmtime(&timeCount);
	//gmt->tm_isdst = 1;
	//tm *gmt = new tm;
	//tm *lct = new tm;
	//gmt->tm_isdst = -1;
	//lct->tm_isdst = -1;
	//gmtime_s(gmt, &timeCount);
	//localtime_s(lct, &timeCount);

	//Windows API
	//https://docs.microsoft.com/zh-cn/windows/desktop/api/timezoneapi/nf-timezoneapi-gettimezoneinformation
	TIME_ZONE_INFORMATION tzi;
	int daylight = GetTimeZoneInformation(&tzi);

	//cout << GetTimeZoneInformation(&tzi) << endl;
	//cout << tzi.Bias << " " << tzi.DaylightBias << " " << tzi.StandardBias << endl;
	//tm *lct = localtime(&timeCount);
	//lct->tm_isdst = -1;
	//time_t timeZone = mktime(localtime(&timeCount)) - mktime(gmtime(&timeCount));
	//time_t timeZone = mktime(lct) - mktime(gmt);
	
	//c++11�ķ������޷���������ʱ
	/*std::chrono::system_clock::time_point tp;
	time_t t = chrono::system_clock::to_time_t(tp);
	char ts[100], tss[100];
	strcpy(ts, ctime(&t));
	strcpy(tss, asctime(gmtime(&t)));
	int timeZone = (ts[11] - tss[11]) * 60 * 60 * 10 + (ts[12] - tss[12]) * 60 * 60 + (ts[14] - tss[14]) * 60 * 10 + (ts[15] - tss[15]) * 60;
	*/
	//cout << timeZone << endl;

	result.tj_year = 1969;//��ʼ����������ʱ������µĴ�λ
	result.tj_month = 12;
	result.tj_day = 31;
	result.tj_hour = 12;
	result.tj_minute = 0;
	result.tj_second =  12 * 60 * 60 - tzi.Bias * 60;

	//����ʱ����
	bool run4_nian2 = ((result.tj_year % 4 == 0) && (result.tj_year % 100 != 0)) || (result.tj_year % 400 == 0);
	result.tj_second += input_time;
	result.tj_minute += result.tj_second / 60;
	result.tj_second %= 60;
	result.tj_hour += result.tj_minute / 60;
	result.tj_minute %= 60;
	result.tj_day += result.tj_hour / 24;
	int days = result.tj_hour / 24;
	result.tj_hour %= 24;

	//��������
	calc_day(result, days, run4_nian2);
	
	//��������ʱ   ������ DaylightDate < StandardDate   �ϰ��� DaylightDate > StandardDate
	if (daylight != 0 && (is_daylight(result, tzi, true) || is_daylight(result, tzi, false)))
	{
		//��1Сʱ�����¼�������
		result.tj_hour++;
		result.tj_day += result.tj_hour / 24;
		result.tj_hour %= 24;
		calc_day(result, days, run4_nian2);
	}

	return &result;	//ע�⣬���ص��Ǿ�̬�ֲ������ĵ�ַ������䲻׼��
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	int test_time[] = { 1, 123456789, 349823021, 987654321, 1202990407, 1216468807, 1250312143, 1272636353, 1326193524, 1336549496, 1392837128, 1625675376, 2052743737 };
	int i;
	struct tj_time *tp;

	for (i = 0; i < sizeof(test_time) / sizeof(int); i++) {
		cout << "����            ��" << test_time[i] << endl;
		cout << "ϵͳת���Ľ��  ��";
		system_time_output(test_time[i]);

		cout << "�Զ���ת���Ľ����";
		tp = tj_time_convert(test_time[i]);
		tj_time_output(tp);

		wait_for_enter();
	}

	if (1) {
		struct tj_time *tp;
		int t = (int)time(0);		//ϵͳ������ȡ��ǰϵͳʱ�䣨��1970-01-01 00:00:00��ʼ��������

		cout << "��ǰϵͳʱ��    ��" << t << endl;
		cout << "ϵͳת���Ľ��  ��";
		system_time_output(t);

		cout << "�Զ���ת���Ľ����";
		tp = tj_time_convert(t);
		tj_time_output(tp);

		wait_for_enter();
	}

	return 0;
}
