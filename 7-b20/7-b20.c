//1850059 ��1�� ��־Զ

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
		if (strcmp(argv[1], "-check") != 0)//�б��ļ�����
		{
			printf("��������\n");
			return 2;
		}
		FILE *in = fopen(argv[2], "rb");
		if (in == NULL)
		{
			printf("�ļ�%s��ʧ��\n", argv[2]);
			return 3;
		}
		printf("%s\n", (form(in) ? "Linux��ʽ" : "Windows��ʽ"));
		fclose(in);
	}
	else if (argc == 5)
	{
		if (strcmp(argv[1], "-convert") != 0)
		{
			printf("��������\n");
			return 2;
		}
		int winToLinux = (strcmp(argv[2], "wtol") == 0);
		if (strcmp(argv[2], "wtol") == 0 || strcmp(argv[2], "ltow") == 0)//Windows��Linux����ת��
		{
			FILE *in = fopen(argv[3], "rb");
			if (in == NULL)
			{
				printf("�ļ�%s��ʧ��\n", argv[3]);
				return 3;
			}
			if ((winToLinux && form(in)) || (!winToLinux && !form(in)))
			{
				printf("�ļ���ʽ����\n");
				fclose(in);
				return 4;
			}
			FILE *out = fopen(argv[4], "wb");
			if (out == NULL)
			{
				printf("�ļ�%s��ʧ��\n", argv[4]);
				fclose(in);
				return 3;
			}
			int ch = ' ';
			while ((ch = fgetc(in)) != EOF)//ת��
			{
				if (winToLinux)//WindowsתLinux
				{
					if (ch != 0x0D)
						fputc((char)ch, out);
				}
				else//LinuxתWindows
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
			printf("%s�ļ� %s ת��%s�ļ� %s ���\n", (winToLinux ? "Windows" : "Linux"), argv[3], (winToLinux ? "Linux" : "Windows"), argv[4]);
			fclose(in);
			fclose(out);
		}
		else
		{
			printf("��������\n");
			return 2;
		}
	}
	else
	{
		usage(argv[0]);
		//printf("������������\n");
		return 1;
	}
	return 0;
}
