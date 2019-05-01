//1850059 计1班 杨志远
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
/* 如果有需要，此处可以添加头文件 */
using namespace std;

/* 允许定义常变量/宏定义，但不允许定义全局变量 */
const char HuaSe[] = { 5, 4, 3, 6, 0 };
const char HaoMa[] = "3456789TJQKA2";
const char *Joker[] = { "BJ", "RJ" };

/* 可以添加自己需要的函数 */
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

/* 打印某个玩家的牌面信息，如果是地主，后面加标记 */
int print(const char *prompt, const int landlord, const unsigned long long player)
{
	/* 只允许定义不超过十个基本类型的简单变量，不能定义数组变量、结构体、string等 */
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
		cout << "(地主)";
	cout << endl;
	return 0;
}

int deal(unsigned long long *player)
{
	/* 只允许定义不超过十个基本类型的简单变量，不能定义数组变量、结构体、string等 */
	srand((unsigned int)time(0));
	int landlord;
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 3; j++)
			new_card(player, j);
		cout << "第" << i + 1 << "轮结束：" << endl;
		print("甲的牌：", 0, player[0]);
		print("乙的牌：", 0, player[1]);
		print("丙的牌：", 0, player[2]);
	}
	for (;;)
	{
		cout << endl << "请选择一个地主[0-2]：" << endl;
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
	return landlord; //此处修改为选定的地主(0-2)
}

/* main函数，不准修改 */
int main()
{
	unsigned long long player[3] = { 0 }; //存放三个玩家的发牌信息
	int landlord; //返回0-2表示哪个玩家是地主

	cout << "按回车键开始发牌";
	while (getchar() != '\n')
		;

	landlord = deal(player);
	print("甲的牌：", landlord == 0, player[0]);
	print("乙的牌：", landlord == 1, player[1]);
	print("丙的牌：", landlord == 2, player[2]);
	
	return 0;
}
