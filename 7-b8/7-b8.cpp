//1850059 ��1�� ��־Զ
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
/* �������Ҫ���˴��������ͷ�ļ� */
using namespace std;

/* �����峣����/�궨�壬����������ȫ�ֱ��� */
const char HuaSe[] = { 5, 4, 3, 6, 0 };
const char HaoMa[] = "3456789TJQKA2";
const char *Joker[] = { "BJ", "RJ" };

/* ��������Լ���Ҫ�ĺ��� */
unsigned long long new_card(unsigned long long *player, int target)
{
	int num;
	do
	{
		num = rand() % 54;
	} while ((player[0] & ((unsigned long long)0x0001 << (unsigned long long)num)) != 0
		 || ((player[1] & ((unsigned long long)0x0001 << (unsigned long long)num)) != 0)
		 || ((player[2] & ((unsigned long long)0x0001 << (unsigned long long)num)) != 0));
	player[target] = player[target] | ((unsigned long long)0x0001 << (unsigned long long)num);
	return player[target];
}

/* ��ӡĳ����ҵ�������Ϣ������ǵ���������ӱ�� */
int print(const char *prompt, const int landlord, const unsigned long long player)
{
	/* ֻ�����岻����ʮ���������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
	cout << prompt;
	for (int i = 0; i < 54; i++)
	{
		unsigned long long temp = (player & ((unsigned long long)0x0001 << (unsigned long long)i));
		if (temp)
		{
			if (i < 52)
				cout << HuaSe[i % 4] << HaoMa[i / 4] << " ";
			else if (i == 52 || i == 53)
				cout << Joker[i - 52] << " ";
		}
	}
	if(landlord)
		cout << "(����)";
	cout << endl;
	return 0;
}

int deal(unsigned long long *player)
{
	/* ֻ�����岻����ʮ���������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
	srand((unsigned int)time(0));
	int landlord;
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 3; j++)
			new_card(player, j);
		cout << "��" << i + 1 << "�ֽ�����" << endl;
		print("�׵��ƣ�", 0, player[0]);
		print("�ҵ��ƣ�", 0, player[1]);
		print("�����ƣ�", 0, player[2]);
	}
	for (;;)
	{
		cout << endl << "��ѡ��һ������[0-2]��" << endl;
		if (!(cin >> landlord) || landlord < 0 || landlord > 2)
		{
			cin.clear();
			cin.ignore(99999, '\n');
			continue;
		}
		break;
	}
	for (int i = 0; i < 3; i++)
		new_card(player, landlord);
	return landlord; //�˴��޸�Ϊѡ���ĵ���(0-2)
}

/* main��������׼�޸� */
int main()
{
	unsigned long long player[3] = { 0 }; //���������ҵķ�����Ϣ
	int landlord; //����0-2��ʾ�ĸ�����ǵ���

	cout << "���س�����ʼ����";
	while (getchar() != '\n')
		;

	landlord = deal(player);
	print("�׵��ƣ�", landlord == 0, player[0]);
	print("�ҵ��ƣ�", landlord == 1, player[1]);
	print("�����ƣ�", landlord == 2, player[2]);
	
	return 0;
}
