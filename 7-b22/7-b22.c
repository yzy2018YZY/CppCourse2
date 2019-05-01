//1850059 ��1�� ��־Զ
//��� 1851726 ��һ�� 1852878 �˽� 1852822 ������ 1851573 ��� 1852101 ��Ǭ ���

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BytesEachLine 16
#define INF -2

int usage(const char *procname)
{
	printf("Usage : %s 16����debug��ʽ�ļ��� ԭʼ�ļ���\n", procname);
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
		printf("�ļ�%s��ʧ��\n", argv[1]);
		return 3;
	}
	FILE *out = fopen(argv[2], "wb");
	if (out == NULL)
	{
		printf("�ļ�%s��ʧ��\n", argv[2]);
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
		if ((fscanf(in, "%8x", &num[0]) != 1 || num[0] - front != BytesEachLine) && !feof(in))//�����������
		{
			printf("��������%08x����\n", num[0]);
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
			if (i % 8 == 0 && i != 0 && i != BytesEachLine)//�ָ���
			{
				fgetc(in);
				while (fgetc(in) != ' ')
					;
				num[i] = INF;
				separatorCount++;
				continue;
			}
			if (fscanf(in, "%x", &num[i]) != 1)//ĩβ�ַ���
			{
				num[i] = INF;
				if (!feof(in))
				{
					flag = 0;
					numCount--;
				}
				break;
			}
			if (feof(in))//�ļ�β
			{
				num[i] = INF;
				break;
			}
			else//��������
			{
				char tempCh = fgetc(in);
				if (tempCh != ' ')
					num[i] = INF;
				else
					numCount++;
			}
		}
		if (numCount != BytesEachLine && num[numCount + separatorCount] >= 0 && flag)//��һ�е��ַ�������������4A��00�����Ļ���ʮ��λ���ֻ������ַ���
			num[numCount + separatorCount] = INF;
		fscanf(in, "%s", tempStr);//����ÿһ�����һ���ַ���
		for (i = 0; i <= numCount + separatorCount; i++) //д���ļ�
		{
			if (num[i] >= 0 && num[i] <= 0xff)
				fputc((char)num[i], out);
		}
		if (numCount != BytesEachLine) //�˳�ѭ��
			break;
	}
	fclose(in);
	fclose(out);
	return 0;
}
