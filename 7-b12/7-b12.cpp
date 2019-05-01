//1850059 计1班 杨志远

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
	"IP地址错误",
	"不是以-开头的合法参数",
};

int usage(const char *procname)
{
	cout << "Usage: " << procname << " [-l 大小] [-n 数量] [-t] IP地址" << endl;
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
	//长度检查
	if (len < 7 || len > 15)
		return false;
	int num = 0;
	int dotCount = 0;
	for (int i = 0; i < len; i++)
	{
		//不能是点和数字以外的字符
		if (!isdigit(str[i]) && str[i] != '.')
			return false;
		else if (str[i] == '.')
		{
			//每个点不能处在第一个或最后一个，并且每一个点的左右都是数字
			if (i == 0 || i == len - 1 || !isdigit(str[i - 1]) || !isdigit(str[i + 1]))
				return false;
			num = 0;
			dotCount++;
		}
		else
		{
			//数字累加
			num *= 10;
			num += (str[i] - '0');
		}
		if (num > 255)
			return false;
	}
	//IP地址共有3个点
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
	//检查参数数量
	if (argc == 1)
	{
		usage(argv[0]);
		return -1;
	}
	//检查ip
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
		//判断参数是否正确
		if (strlen(argv[i]) != 2)
		{
			cout << "参数" << argv[i] << "不存在" << endl;
			return 4;
		}
		//判断需要输入数值的参数
		bool flag = false;
		for (int k = 0; k < elementOfParametersWithValue; k++)
		{
			if (argv[i][1] == ParameterWithValue[k])
			{
				if (argv[i + 1][0] == '-' || is_ip(argv[i + 1]))
				{
					cout << "参数-" << ParameterWithValue[k] << "没有后续参数" << endl;
					return 3;
				}
				parameterValue[k] = atoi(argv[i + 1]);
				if (parameterValue[k] < MinOfParameter[k] || parameterValue[k] > MaxOfParameter[k])
					parameterValue[k] = DefaultOfParameter[k];
				i++;
				flag = true;
			}
		}
		//判断不需要输入数值的参数
		for (int k = 0; k < elementOfParametersWithoutValue; k++)
		{
			if (argv[i][1] == ParameterWithoutVaule[k])
			{
				parameterExist[k] = 1;
				flag = true;
			}
		}
		//判断参数是否正确
		if (flag == false)
		{
			cout << "参数" << argv[i] << "不存在" << endl;
			return 4;
		}
	}
	//输出信息
	cout << "参数检查通过" << endl;
	for (int k = 0; k < elementOfParametersWithValue; k++)
		cout << "-" << ParameterWithValue[k] << "参数：" << parameterValue[k] << endl;
	for (int k = 0; k < elementOfParametersWithoutValue; k++)
		cout << "-" << ParameterWithoutVaule[k] << "参数：" << parameterExist[k] << endl;
	cout << "IP地址：" << argv[argc - 1] << endl;
	delete[] parameterExist;
	delete[] parameterValue;
	return 0;
}