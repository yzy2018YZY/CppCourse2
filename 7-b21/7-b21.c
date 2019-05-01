//1850059 ��1�� ��־Զ

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
		printf("�ļ���������ʽ�����ԣ�");
		printf("    a.txt������·����ʽ\n");
		printf("    ../data/b.dat�����·����ʽ\n");
		printf("    C : /Windows/System32/c.dat���������·����ʽ\n");
		printf("�������ļ��� : ");
		scanf("%s", fileName);
	}
	else if (strlen(argv[1]) >= 100)
	{
		printf("�ļ�������\n");
		return 4;
	}
	else
	{
		strcpy(fileName, argv[1]);
	}
	FILE *in = fopen(fileName, "rb");
	if (in == NULL)
	{
		printf("�ļ�%s��ʧ��\n", fileName);
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
