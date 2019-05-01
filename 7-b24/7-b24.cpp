//1850059 ��1�� ��־Զ

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <stdlib.h> 
using namespace std;

const int DefaultStrLength = 100;

const long long MinData[] = { 0, 0, 0, 0, 0,
							0, 0, 0, 0, 100000000000, 
							0, 0, 0, 0, 0, 
							0, 0, 0, 0, 0, 
							0, 0, 0, 0, 0,
							0, };
const long long MaxData[] = { 0, 0, 10000, 10000, 8192,
							1024, 100000000, 1000000, 1000000, 200000000000, 
							100, 100, 100, 2000, 2000, 
							100, 100, 100, 100, 10000, 
							100, 100, 100, 100, 100, 
							100, };

enum DataName
{
	Data_name = 1,
	Data_HP,
	Data_STR,
	Data_CON,
	Data_DEX,
	Data_money,
	Data_fame,
	Data_charm,
	Data_VIG,
	Data_MOVspeed,
	Data_ATKspeed,
	Data_ATKrange,
	Data_ATK,
	Data_DEF,
	Data_AGI,
	Data_INT,
	Data_exp,
	Data_level,
	Data_MP,
	Data_MPeachTime,
	Data_MGK,
	Data_hitRate,
	Data_RGS,
	Data_CRI,
	Data_VIT,
};

const char *PrintInfo[] = 
{
	NULL,
	"����ǳ�",
	"����ֵ",
	"����ֵ",
	"����ֵ",
	"����ֵ",
	"��Ǯֵ",
	"����ֵ",
	"����ֵ",
	"����ֵ",
	"�ƶ��ٶ�ֵ",
	"�����ٶ�ֵ",
	"������Χֵ",
	"������ֵ",
	"������ֵ",
	"���ݶ�ֵ",
	"����ֵ",
	"����ֵ",
	"�ȼ�ֵ",
	"ħ��ֵ",
	"����ħ��ֵ",
	"ħ���˺���ֵ",
	"������ֵ",
	"ħ��������ֵ",
	"������ֵ",
	"����ֵ",
};

struct PlayerData
{
	char name[16];
	short HP;
	short STR;
	short CON;
	short DEX;//����
	int money;
	int fame;
	int charm;
	unsigned int VIG1;//����
	unsigned int VIG2;
	char MOVspeed;
	char ATKspeed;
	char ATKrange;
	char rest3;//Ԥ��
	short ATK;
	short DEF;
	char AGI;
	char INT;
	char exp;
	char level;
	short MP;
	char MPeachTime;
	char MGK;//ħ������
	char hitRate;
	char RGS;//ħ������
	char CRI;//������
	char VIT;//����
};

void read_player_data_from_file(fstream &io, PlayerData &player)
{
	io.read((char *)(&player), sizeof(PlayerData));
	io.seekg(0, ios::beg);
}

void write_player_data_to_file(fstream &io, PlayerData &player)
{
	io.write((char *)(&player), sizeof(PlayerData));
	io.seekp(0, ios::beg);
}

//������choice��struct��Ա��Ӧ������ mode: 0->��� 1->�޸�
bool operate_data(PlayerData &player, int choice, int mode, long long llNum = -1, char *data = NULL)
{
	int num = (int)llNum;
	if (mode == 1)
	{
		if (choice == Data_name && data == NULL)//����޸ĵ������Ƿ񳬳���Χ
			return false;
		if (choice != Data_name && (llNum < MinData[choice] || llNum > MaxData[choice]))//ͬ��
			return false;
	}
	switch (choice)
	{
		case Data_name:
			if (mode == 0)
				cout << player.name;
			if (mode == 1)
				strcpy(player.name, data);
			break;
		case Data_HP:
			if (mode == 0)
				cout << player.HP;
			if (mode == 1)
				player.HP = num;
			break;
		case Data_STR:
			if (mode == 0)
				cout << player.STR;
			if (mode == 1)
				player.STR = num;
			break;
		case Data_CON:
			if (mode == 0)
				cout << player.CON;
			if (mode == 1)
				player.CON = num;
			break;
		case Data_DEX:
			if (mode == 0)
				cout << player.DEX;
			if (mode == 1)
				player.DEX = num;
			break;
		case Data_money:
			if (mode == 0)
				cout << player.money;
			if (mode == 1)
				player.money = num;
			break;
		case Data_fame:
			if (mode == 0)
				cout << player.fame;
			if (mode == 1)
				player.fame = num;
			break;
		case Data_charm:
			if (mode == 0)
				cout << player.charm;
			if (mode == 1)
				player.charm = num;
			break;
		case Data_VIG:
			if (mode == 0)
				cout << (((long long)(player.VIG2) << 32) + (long long)player.VIG1);
			if (mode == 1)
			{
				player.VIG1 = (unsigned int)(llNum % 4294967296);
				player.VIG2 = (unsigned int)(llNum >> 32);
			}
			break;
		case Data_MOVspeed:
			if (mode == 0)
				cout << (int)player.MOVspeed;
			if (mode == 1)
				player.MOVspeed = num;
			break;
		case Data_ATKspeed:
			if (mode == 0)
				cout << (int)player.ATKspeed;
			if (mode == 1)
				player.ATKspeed = num;
			break;
		case Data_ATKrange:
			if (mode == 0)
				cout << (int)player.ATKrange;
			if (mode == 1)
				player.ATKrange = num;
			break;
		case Data_ATK:
			if (mode == 0)
				cout << player.ATK;
			if (mode == 1)
				player.ATK = num;
			break;
		case Data_DEF:
			if (mode == 0)
				cout << player.DEF;
			if (mode == 1)
				player.DEF = num;
			break;
		case Data_AGI:
			if (mode == 0)
				cout << (int)player.AGI;
			if (mode == 1)
				player.AGI = num;
			break;
		case Data_INT:
			if (mode == 0)
				cout << (int)player.INT;
			if (mode == 1)
				player.INT = num;
			break;
		case Data_exp:
			if (mode == 0)
				cout << (int)player.exp;
			if (mode == 1)
				player.exp = num;
			break;
		case Data_level:
			if (mode == 0)
				cout << (int)player.level;
			if (mode == 1)
				player.level = num;
			break;
		case Data_MP:
			if (mode == 0)
				cout << player.MP;
			if (mode == 1)
				player.MP = num;
			break;
		case Data_MPeachTime:
			if (mode == 0)
				cout << (int)player.MPeachTime;
			if (mode == 1)
				player.MPeachTime = num;
			break;
		case Data_MGK:
			if (mode == 0)
				cout << (int)player.MGK;
			if (mode == 1)
				player.MGK = num;
			break;
		case Data_hitRate:
			if (mode == 0)
				cout << (int)player.hitRate;
			if (mode == 1)
				player.hitRate = num;
			break;
		case Data_RGS:
			if (mode == 0)
				cout << (int)player.RGS;
			if (mode == 1)
				player.RGS = num;
			break;
		case Data_CRI:
			if (mode == 0)
				cout << (int)player.CRI;
			if (mode == 1)
				player.CRI = num;
			break;
		case Data_VIT:
			if (mode == 0)
				cout << (int)player.VIT;
			if (mode == 1)
				player.VIT = num;
			break;
		default:
			break;
	}
	return true;
}

void print_player_data(PlayerData &player)//����ṹ����Ϣ
{
	int listSize = sizeof(PrintInfo) / sizeof(PrintInfo[0]);
	for (int i = 1; i < listSize; i++)
	{
		int len = strlen(PrintInfo[i]);
		for (int k = 0; k < 15 - len; k++)
			cout << " ";
		cout << setw(2) << i << "-" << PrintInfo[i] << " : ";
		operate_data(player, i, 0);
		cout << endl;
	}
}

int choose_mode(int listSize)//ѡ����Ҫ�޸ĵ����ݣ�֧�����ֺ��ַ���
{
	char temp[DefaultStrLength];
	cin >> temp;
	int choice = -1;
	if (strcmp("0", temp) == 0)
		return 0;
	for (int i = 1; i < listSize; i++)
	{
		int num = atoi(temp);
		if ((num == i) || strcmp(PrintInfo[i], temp) == 0)
		{
			choice = i;
			break;
		}
	}
	return choice;
}

int save_data(fstream &io, PlayerData &player)//ѡ���Ƿ�Ҫ���浽�ļ�
{
	cout << "�Ƿ�Ҫ���浽�ļ�����Y/N����";
	char save[DefaultStrLength];
	cin >> save;
	if (save[0] == 'Y' || save[0] == 'y')
	{
		write_player_data_to_file(io, player);
		cout << "�������" << endl << endl;
		return true;
	}
	else
		cout << "δ����" << endl << endl;
	return false;
}

int main()
{
	char fileName[] = "game2.dat";
	int listSize = sizeof(PrintInfo) / sizeof(PrintInfo[0]);
	PlayerData player;
	fstream io(fileName, ios::in | ios::out | ios::binary);
	cout << "�浵�鿴���޸���" << endl;
	if (!io.is_open())
	{
		cerr << "�ļ�" << fileName << "��ʧ��" << endl;
		return 3;
	}
	read_player_data_from_file(io, player);
	print_player_data(player);
	for (;;)
	{
		cout << "��������Ҫ�޸ĵ����ݵ���Ż����ƣ�����0�˳�����";//����Ҫ�޸ĵ�����
		int choice = choose_mode(listSize);
		if (choice == 0)
			break;
		if (choice < 0)
		{
			cout << "�����������������" << endl;
			continue;
		}
		cout << "��ǰ�� " << PrintInfo[choice] << " Ϊ��";
		operate_data(player, choice, 0);
		cout << endl << "��Ҫ�޸�Ϊ��";
		for (;;)
		{
			char temp2[DefaultStrLength] = "";
			long long num = -1;
			if (choice == 1)
				cin >> temp2;
			else
				cin >> num;
			if (cin.good() && operate_data(player, choice, 1, num, temp2))//�޸Ĳ�����
			{
				cout << "�޸����" << endl << endl;
				print_player_data(player);
				cout << endl;
				save_data(io, player);
				break;
			}
			else//�����޸�ʧ�ܵ����
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "���볬����Χ�����������룺";
				continue;
			}
		}
	}
	io.close();
	return 0;
}
