//1850059 ��1�� ��־Զ
//��� 1851573 ��� 1851726 ��һ�� 1852101 ��Ǭ 1852822 ������ 1852878 �˽� ���

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
using namespace std;

const int BytesEachLine = 16;

int usage(const char *procname)
{
	cout << "Usage : " << procname << " 16����debug��ʽ�ļ��� ԭʼ�ļ���" << endl;
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		usage(argv[0]);
		return 1;
	}
	ifstream in(argv[1], ios::in);
	if (!in.is_open())
	{
		cerr << "�ļ�" << argv[1] << "��ʧ��" << endl;
		return 3;
	}
	ofstream out(argv[2], ios::out | ios::binary);
	if (!out.is_open())
	{
		cerr << "�ļ�" << argv[2] << "��ʧ��" << endl;
		in.close();
		return 3;
	}
	int front = -BytesEachLine;
	int num[BytesEachLine + 4];
	for (;;)
	{
		char tempStr[BytesEachLine + 4];
		int numCount = 0, separatorCount = 0;
		memset(num, 0x7f, sizeof(num));
		in >> hex >> num[0];
		if(in.eof())//�������ָ�ʽ����
		{
			return 0;
		}
		else if (!in.good() || num[0] - front != BytesEachLine)//�����������
		{
			in.clear();
			cerr << "��������" << setw(8) << setfill('0') << hex << num[0] << "����" << endl;
			return 5;
		}
		else//������������
			front = num[0];
		for (int i = 0; i <= BytesEachLine; i++)
		{
			if (i % 8 == 0 && i != 0 && i != BytesEachLine)//�ָ���
			{
				in.get();
				in.ignore(1000, ' ');
				num[i] = INT_MIN;
				separatorCount++;
				continue;
			}
			in >> hex >> num[i];
			if (!in.good() || in.eof())//ĩβ�ַ���
			{
				in.clear();
				num[i] = INT_MIN;
				break;
			}
			else//��������
			{
				numCount++;
			}
		}
		if (numCount != BytesEachLine && num[numCount - 1 + separatorCount] > 0)//��һ�е��ַ�������������4A��00�����Ļ���ʮ��λ���ֻ������ַ���
			num[numCount - 1 + separatorCount] = INT_MIN;
		in >> tempStr; //����ÿһ�����һ���ַ���
		for (int i = 0; i <= numCount; i++) //д���ļ�
		{
			if (num[i] >= 0 && num[i] <= 0xff)
				out.put(char(num[i]));
		}
		if (numCount != BytesEachLine) //�˳�ѭ��
			break;
	}
	in.close();
	out.close();
	return 0;
}
