//1850059 计1班 杨志远

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int usage(const char *procname)
{
	printf("Usage: %s -check a.txt\n", procname);
	printf("       %s -convert wtol a.txt b.txt\n", procname);
	printf("       %s -convert ltow a.txt b.txt\n", procname);
	return 0;
}

//1: Linux  0:Windows
int form(FILE *in)
{
	char ch;
	while ((ch = fgetc(in)) != EOF)
	{
		if (ch == 0x0D)
		{
			fseek(in, 0, SEEK_SET);
			return 0;
		}
	}
	fseek(in, 0, SEEK_SET);
	return 1;
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		if (strcmp(argv[1], "-check") != 0)//判别文件类型
		{
			printf("参数错误\n");
			return 2;
		}
		FILE *in = fopen(argv[2], "rb");
		if (in == NULL)
		{
			printf("文件%s打开失败\n", argv[2]);
			return 3;
		}
		printf("%s\n", (form(in) ? "Linux格式" : "Windows格式"));
		fclose(in);
	}
	else if (argc == 5)
	{
		if (strcmp(argv[1], "-convert") != 0)
		{
			printf("参数错误\n");
			return 2;
		}
		int winToLinux = (strcmp(argv[2], "wtol") == 0);
		if (strcmp(argv[2], "wtol") == 0 || strcmp(argv[2], "ltow") == 0)//Windows与Linux互相转换
		{
			FILE *in = fopen(argv[3], "rb");
			if (in == NULL)
			{
				printf("文件%s打开失败\n", argv[3]);
				return 3;
			}
			if ((winToLinux && form(in)) || (!winToLinux && !form(in)))
			{
				printf("文件格式错误\n");
				fclose(in);
				return 4;
			}
			FILE *out = fopen(argv[4], "wb");
			if (out == NULL)
			{
				printf("文件%s打开失败\n", argv[4]);
				fclose(in);
				return 3;
			}
			int ch = ' ';
			while ((ch = fgetc(in)) != EOF)//转换
			{
				if (winToLinux)//Windows转Linux
				{
					if (ch != 0x0D)
						fputc((char)ch, out);
				}
				else//Linux转Windows
				{
					if (ch == 0x0A)
					{
						fputc(0x0D, out);
						fputc(0x0A, out);
					}
					else
						fputc((char)ch, out);
				}
			}
			printf("%s文件 %s 转换%s文件 %s 完成\n", (winToLinux ? "Windows" : "Linux"), argv[3], (winToLinux ? "Linux" : "Windows"), argv[4]);
			fclose(in);
			fclose(out);
		}
		else
		{
			printf("参数错误\n");
			return 2;
		}
	}
	else
	{
		usage(argv[0]);
		//printf("参数数量错误\n");
		return 1;
	}
	return 0;
}
