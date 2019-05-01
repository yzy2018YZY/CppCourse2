//1850059 计1班 杨志远

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BytesEachLine 16
const char Separator[] = "-";

int main(int argc, char *argv[])
{
	char fileName[100] = "";
	if (argc == 1)
	{
		printf("文件名以下形式均可以：");
		printf("    a.txt：不带路径形式\n");
		printf("    ../data/b.dat：相对路径形式\n");
		printf("    C : /Windows/System32/c.dat：绝对相对路径形式\n");
		printf("请输入文件名 : ");
		scanf("%s", fileName);
	}
	else if (strlen(argv[1]) >= 100)
	{
		printf("文件名过长\n");
		return 4;
	}
	else
	{
		strcpy(fileName, argv[1]);
	}
	FILE *in = fopen(fileName, "rb");
	if (in == NULL)
	{
		printf("文件%s打开失败\n", fileName);
		return 3;
	}
	int lineCount = 0;
	while (!feof(in))
	{
		int ch[BytesEachLine + 4];
		int i; 
		for (i = 0; i < BytesEachLine; i++)
		{
			ch[i] = fgetc(in);
			if (ch[i] == EOF)
			{
				int k;
				for (k = i + 1; k < BytesEachLine; k++)
					ch[k] = EOF;
				break;
			}
		}
		if (ch[0] == EOF)
			break;
		printf("%08x", BytesEachLine * lineCount++);
		printf("  ");
		for (i = 0; i < BytesEachLine; i++)
		{
			if (i % 8 == 0 && i != 0)
				printf("%s ", (ch[i] == EOF ? " " : Separator));
			if (ch[i] == EOF)
				printf("   ");
			else
				printf("%02x ", (int)ch[i]);
		}
		printf("    ");
		for (i = 0; i < BytesEachLine; i++)
		{
			if (ch[i] == EOF)
				printf("");
			else if (ch[i] >= 33 && ch[i] <= 126)
				printf("%c", (char)ch[i]);
			else
				printf(".");
		}
		printf("\n");
	}
	fclose(in);
	return 0;
}
