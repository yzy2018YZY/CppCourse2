//1850059 ��1�� ��־Զ

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
using namespace std;

const char ParameterWithValue[] = "nl";
const int MinOfParameter[] = { 1, 64 };
const int DefaultOfParameter[] = { 100, 128 };
const int MaxOfParameter[] = { 10000, 64000 };
const char ParameterWithoutVaule[] = "t";
const char *ErrorMessage[] =
{
	"IP��ַ����",
	"������-��ͷ�ĺϷ�����",
};

int usage(const char *procname)
{
	cout << "Usage: " << procname << " [-l ��С] [-n ����] [-t] IP��ַ" << endl;
	return 0;
}

bool is_number(char str[])
{
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

bool is_ip(char str[])
{
	int len = strlen(str);
	//���ȼ��
	if (len < 7 || len > 15)
		return false;
	int num = 0;
	int dotCount = 0;
	for (int i = 0; i < len; i++)
	{
		//�����ǵ������������ַ�
		if (!isdigit(str[i]) && str[i] != '.')
			return false;
		else if (str[i] == '.')
		{
			//ÿ���㲻�ܴ��ڵ�һ�������һ��������ÿһ��������Ҷ�������
			if (i == 0 || i == len - 1 || !isdigit(str[i - 1]) || !isdigit(str[i + 1]))
				return false;
			num = 0;
			dotCount++;
		}
		else
		{
			//�����ۼ�
			num *= 10;
			num += (str[i] - '0');
		}
		if (num > 255)
			return false;
	}
	//IP��ַ����3����
	if (dotCount != 3)
		return false;
	return true;
}

int main(int argc, char *argv[])
{
	int elementOfParametersWithValue = strlen(ParameterWithValue);
	int elementOfParametersWithoutValue = strlen(ParameterWithoutVaule);
	int *parameterValue = new int[elementOfParametersWithValue + 1];
	int *parameterExist = new int[elementOfParametersWithoutValue + 1];
	for (int i = 0; i < elementOfParametersWithValue; i++)
		parameterValue[i] = DefaultOfParameter[i];
	for (int i = 0; i < elementOfParametersWithoutValue; i++)
		parameterExist[i] = 0;
	//����������
	if (argc == 1)
	{
		usage(argv[0]);
		return -1;
	}
	//���ip
	if (!is_ip(argv[argc - 1]))
	{
		cout << ErrorMessage[0] << endl;
		return 1;
	}
	for (int i = 1; i < argc - 1; i++)
	{
		if (argv[i][0] != '-')
		{
			cout << ErrorMessage[1] << endl;
			return 2;
		}
		//�жϲ����Ƿ���ȷ
		if (strlen(argv[i]) != 2)
		{
			cout << "����" << argv[i] << "������" << endl;
			return 4;
		}
		//�ж���Ҫ������ֵ�Ĳ���
		bool flag = false;
		for (int k = 0; k < elementOfParametersWithValue; k++)
		{
			if (argv[i][1] == ParameterWithValue[k])
			{
				if (argv[i + 1][0] == '-' || is_ip(argv[i + 1]))
				{
					cout << "����-" << ParameterWithValue[k] << "û�к�������" << endl;
					return 3;
				}
				parameterValue[k] = atoi(argv[i + 1]);
				if (parameterValue[k] < MinOfParameter[k] || parameterValue[k] > MaxOfParameter[k])
					parameterValue[k] = DefaultOfParameter[k];
				i++;
				flag = true;
			}
		}
		//�жϲ���Ҫ������ֵ�Ĳ���
		for (int k = 0; k < elementOfParametersWithoutValue; k++)
		{
			if (argv[i][1] == ParameterWithoutVaule[k])
			{
				parameterExist[k] = 1;
				flag = true;
			}
		}
		//�жϲ����Ƿ���ȷ
		if (flag == false)
		{
			cout << "����" << argv[i] << "������" << endl;
			return 4;
		}
	}
	//�����Ϣ
	cout << "�������ͨ��" << endl;
	for (int k = 0; k < elementOfParametersWithValue; k++)
		cout << "-" << ParameterWithValue[k] << "������" << parameterValue[k] << endl;
	for (int k = 0; k < elementOfParametersWithoutValue; k++)
		cout << "-" << ParameterWithoutVaule[k] << "������" << parameterExist[k] << endl;
	cout << "IP��ַ��" << argv[argc - 1] << endl;
	delete[] parameterExist;
	delete[] parameterValue;
	return 0;
}