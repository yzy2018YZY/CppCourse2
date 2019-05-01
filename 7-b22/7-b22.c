//1850059 计1班 杨志远
//检查 1851726 汪一泓 1852878 邓杰 1852822 李宇龙 1851573 李博宇 1852101 曹乾 完成

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BytesEachLine 16
#define INF -2

int usage(const char *procname)
{
	printf("Usage : %s 16进制debug格式文件名 原始文件名\n", procname);
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		usage(argv[0]);
		return 1;
	}
	FILE *in = fopen(argv[1], "r");
	if (in == NULL)
	{
		printf("文件%s打开失败\n", argv[1]);
		return 3;
	}
	FILE *out = fopen(argv[2], "wb");
	if (out == NULL)
	{
		printf("文件%s打开失败\n", argv[2]);
		fclose(in);
		return 3;
	}
	int front = -BytesEachLine;
	for (;;)
	{
		char tempStr[BytesEachLine + 4];
		int numCount = 0, separatorCount = 0;
		int num[BytesEachLine + 4] = { 0 };
		memset(num, -1, sizeof(num));
		if ((fscanf(in, "%8x", &num[0]) != 1 || num[0] - front != BytesEachLine) && !feof(in))//检查行首数字
		{
			printf("行首序数%08x错误\n", num[0]);
			return 5;
		}
		else if (feof(in))
		{
			return 0;
		}
		else
			front = num[0];
		int i, flag = 1;
		for (i = 0; i <= BytesEachLine; i++)
		{
			if (i % 8 == 0 && i != 0 && i != BytesEachLine)//分隔符
			{
				fgetc(in);
				while (fgetc(in) != ' ')
					;
				num[i] = INF;
				separatorCount++;
				continue;
			}
			if (fscanf(in, "%x", &num[i]) != 1)//末尾字符串
			{
				num[i] = INF;
				if (!feof(in))
				{
					flag = 0;
					numCount--;
				}
				break;
			}
			if (feof(in))//文件尾
			{
				num[i] = INF;
				break;
			}
			else//正常数字
			{
				char tempCh = fgetc(in);
				if (tempCh != ' ')
					num[i] = INF;
				else
					numCount++;
			}
		}
		if (numCount != BytesEachLine && num[numCount + separatorCount] >= 0 && flag)//这一行的字符可能是类似于4A、00这样的会与十六位数字混淆的字符串
			num[numCount + separatorCount] = INF;
		fscanf(in, "%s", tempStr);//过滤每一行最后一个字符串
		for (i = 0; i <= numCount + separatorCount; i++) //写入文件
		{
			if (num[i] >= 0 && num[i] <= 0xff)
				fputc((char)num[i], out);
		}
		if (numCount != BytesEachLine) //退出循环
			break;
	}
	fclose(in);
	fclose(out);
	return 0;
}
