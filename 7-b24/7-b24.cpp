//1850059 计1班 杨志远

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
	"玩家昵称",
	"生命值",
	"力量值",
	"体质值",
	"灵巧值",
	"金钱值",
	"名声值",
	"魅力值",
	"活力值",
	"移动速度值",
	"攻击速度值",
	"攻击范围值",
	"攻击力值",
	"防御力值",
	"敏捷度值",
	"智力值",
	"经验值",
	"等级值",
	"魔法值",
	"消耗魔法值",
	"魔法伤害力值",
	"命中率值",
	"魔法防御力值",
	"暴击率值",
	"耐力值",
};

struct PlayerData
{
	char name[16];
	short HP;
	short STR;
	short CON;
	short DEX;//灵巧
	int money;
	int fame;
	int charm;
	unsigned int VIG1;//活力
	unsigned int VIG2;
	char MOVspeed;
	char ATKspeed;
	char ATKrange;
	char rest3;//预留
	short ATK;
	short DEF;
	char AGI;
	char INT;
	char exp;
	char level;
	short MP;
	char MPeachTime;
	char MGK;//魔法攻击
	char hitRate;
	char RGS;//魔法防御
	char CRI;//暴击率
	char VIT;//耐力
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

//操作第choice个struct成员对应的数据 mode: 0->输出 1->修改
bool operate_data(PlayerData &player, int choice, int mode, long long llNum = -1, char *data = NULL)
{
	int num = (int)llNum;
	if (mode == 1)
	{
		if (choice == Data_name && data == NULL)//检查修改的数据是否超出范围
			return false;
		if (choice != Data_name && (llNum < MinData[choice] || llNum > MaxData[choice]))//同上
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

void print_player_data(PlayerData &player)//输出结构体信息
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

int choose_mode(int listSize)//选择需要修改的数据，支持数字和字符串
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

int save_data(fstream &io, PlayerData &player)//选择是否要保存到文件
{
	cout << "是否要保存到文件？（Y/N）：";
	char save[DefaultStrLength];
	cin >> save;
	if (save[0] == 'Y' || save[0] == 'y')
	{
		write_player_data_to_file(io, player);
		cout << "保存完成" << endl << endl;
		return true;
	}
	else
		cout << "未保存" << endl << endl;
	return false;
}

int main()
{
	char fileName[] = "game2.dat";
	int listSize = sizeof(PrintInfo) / sizeof(PrintInfo[0]);
	PlayerData player;
	fstream io(fileName, ios::in | ios::out | ios::binary);
	cout << "存档查看和修改器" << endl;
	if (!io.is_open())
	{
		cerr << "文件" << fileName << "打开失败" << endl;
		return 3;
	}
	read_player_data_from_file(io, player);
	print_player_data(player);
	for (;;)
	{
		cout << "请输入需要修改的数据的序号或名称（输入0退出）：";//输入要修改的数据
		int choice = choose_mode(listSize);
		if (choice == 0)
			break;
		if (choice < 0)
		{
			cout << "输入错误，请重新输入" << endl;
			continue;
		}
		cout << "当前的 " << PrintInfo[choice] << " 为：";
		operate_data(player, choice, 0);
		cout << endl << "需要修改为：";
		for (;;)
		{
			char temp2[DefaultStrLength] = "";
			long long num = -1;
			if (choice == 1)
				cin >> temp2;
			else
				cin >> num;
			if (cin.good() && operate_data(player, choice, 1, num, temp2))//修改并保存
			{
				cout << "修改完成" << endl << endl;
				print_player_data(player);
				cout << endl;
				save_data(io, player);
				break;
			}
			else//处理修改失败的情况
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "输入超出范围，请重新输入：";
				continue;
			}
		}
	}
	io.close();
	return 0;
}
