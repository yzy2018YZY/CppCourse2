#include <iostream>
#include <iomanip>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <time.h>
//#include <thread>
#include <stdlib.h>  
#include <crtdbg.h>  
using namespace std;

const int Times = 50000000;

enum Direction
{
	Up = 0,
	Down,
	Left,
	Right
};

static bool row_col_in_map(const int row, const int col)
{
	if (row >= 0 && row < 10 && col >= 0 && col < 10)
		return true;
	else
		return false;
}

//判断坐标点是否在机头可能存在的范围内
static bool row_col_in_map_head(const int row, const int col)
{
	if (row_col_in_map(row, col) == false)
		return false;
	if (row < 2 && col < 2)
		return false;
	if (row < 2 && col >= 10 - 2)
		return false;
	if (row >= 10 - 2 && col < 2)
		return false;
	if (row >= 10 - 2 && col >= 10 - 2)
		return false;
	else
		return true;
}

static int bodies_of_plane(const int map[][10], const int row, const int col, const int direction)
{
	int ret = 0;
	if (direction == Down || direction == Up)
	{
		const int offsetX[] = { 0, -1, -2, 1, 2, 0, -1, 0, 1 }, offsetY[] = { 1, 1, 1, 1, 1, 2, 3, 3 ,3 };
		int dir = (direction == Down ? 1 : -1);
		for (int i = 0; i < sizeof(offsetX) / sizeof(offsetX[0]); i++)
		{
			if (map[row + offsetY[i] * dir][col + offsetX[i]] == 1 || map[row + offsetY[i] * dir][col + offsetX[i]] == 2)
				ret++;
		}
	}
	if (direction == Left || direction == Right)
	{
		const int offsetY[] = { 0, -1, -2, 1, 2, 0, -1, 0, 1 }, offsetX[] = { 1, 1, 1, 1, 1, 2, 3, 3 ,3 };
		int dir = (direction == Right ? 1 : -1);
		for (int i = 0; i < sizeof(offsetX) / sizeof(offsetX[0]); i++)
		{
			if (map[row + offsetY[i]][col + offsetX[i] * dir] == 1 || map[row + offsetY[i]][col + offsetX[i] * dir] == 2)
				ret++;
		}
	}
	return ret;
}

static void set_value_of_plane(int map[][10], const int row, const int col, const int direction, const int value)
{
	if (direction == Down || direction == Up)
	{
		const int offsetX[] = { 0, -1, -2, 1, 2, 0, -1, 0, 1 }, offsetY[] = { 1, 1, 1, 1, 1, 2, 3, 3 ,3 };
		int dir = (direction == Down ? 1 : -1);
		for (int i = 0; i < sizeof(offsetX) / sizeof(offsetX[0]); i++)
		{
			map[row + offsetY[i] * dir][col + offsetX[i]] = value;
		}
		map[row][col] = value;
	}
	if (direction == Left || direction == Right)
	{
		const int offsetY[] = { 0, -1, -2, 1, 2, 0, -1, 0, 1 }, offsetX[] = { 1, 1, 1, 1, 1, 2, 3, 3 ,3 };
		int dir = (direction == Right ? 1 : -1);
		for (int i = 0; i < sizeof(offsetX) / sizeof(offsetX[0]); i++)
		{
			map[row + offsetY[i]][col + offsetX[i] * dir] = value;
		}
		map[row][col] = value;
	}
}

bool map_full(const int map[][10], const int row, const int col)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (map[i][j] != 0)
				return false;
		}
	return true;
}

bool check(const int map[][10], const int row, const int col, const int dir)
{
	if (row_col_in_map_head(row, col) == false)
		return false;
	if (dir == Up)
	{
		if (row_col_in_map_head(row - 3, col - 2) == false)
			return false;
		if (row_col_in_map_head(row - 3, col + 2) == false)
			return false;
	}
	if (dir == Down)
	{
		if (row_col_in_map_head(row + 3, col - 2) == false)
			return false;
		if (row_col_in_map_head(row + 3, col + 2) == false)
			return false;
	}
	if (dir == Left)
	{
		if (row_col_in_map_head(row - 2, col - 3) == false)
			return false;
		if (row_col_in_map_head(row + 2, col - 3) == false)
			return false;
	}
	if (dir == Right)
	{
		if (row_col_in_map_head(row - 2, col + 3) == false)
			return false;
		if (row_col_in_map_head(row + 2, col + 3) == false)
			return false;
	}
	if (bodies_of_plane(map, row, col, dir) > 0)
		return false;
	return true;
}

void print(ostream &out, int arr[10][10])
{
	int maxn = -1, R[100] = { 0 }, C[100] = { 0 };
	for (int k = 0; k < 100; k++)
	{
		maxn = -1;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (maxn <= arr[i][j])
				{
					maxn = arr[i][j];
					R[k] = i;
					C[k] = j;
				}
			}
		}
		arr[R[k]][C[k]] = -1;
	}
	for (int k = 0; k < 100; k++)
	{
		out << R[k] << ", ";
	}
	cout << endl;
	for (int k = 0; k < 100; k++)
	{
		out << C[k] << ", ";
	}
	out << endl;
}

int main()
{
	//模拟情况
	srand((unsigned int)time(0));
	int map[10][10], body[10][10] = { 0 }, head[10][10] = { 0 }, score[10][10] = { 0 },x, y, dir;
	for (int k = 0; k < Times; k++)
	{
		memset(map, 0, sizeof(int) * 10 * 10);
		for (int i = 0; i < 3; i++)
		{
			do
			{
				x = rand() % 10;
				y = rand() % 10;
				dir = rand() % 4;
			} while (check(map, y, x, dir) == false);
			set_value_of_plane(map, y, x, dir, 1);
			map[y][x] = 2;
		}
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (map[i][j] == 1)
				{
					score[i][j] += 1;
					body[i][j]++;
				}
				if (map[i][j] == 2)
				{
					score[i][j] += 5;
					head[i][j]++;
				}
			}
			//cout << endl;
		}
		//cout << endl;
		if (k % 10000 == 0)
			cout << k * 100.0 / Times << "% over" << endl;
	}
	
	//找出所有的情况
	//int count = 0;
	//for (int i1 = 0; i1 < 10; i1++)
	//{
	//	for (int j1 = 0; j1 < 10; j1++)
	//	{
	//		for (int dir1 = 0; dir1 < 4; dir1++)
	//		{
	//			if (check(map, i1, j1, dir1) == true)
	//			{
	//				set_value_of_plane(map, i1, j1, dir1, 1);
	//				map[i1][j1] = 2;
	//				for (int i2 = 0; i2 < 10; i2++)
	//				{
	//					for (int j2 = 0; j2 < 10; j2++)
	//					{
	//						for (int dir2 = 0; dir2 < 4; dir2++)
	//						{
	//							if (check(map, i2, j2, dir2) == true)
	//							{
	//								set_value_of_plane(map, i2, j2, dir2, 2);
	//								map[i2][j2] = 2;
	//								for (int i3 = 0; i3 < 10; i3++)
	//								{
	//									for (int j3 = 0; j3 < 10; j3++)
	//									{
	//										for (int dir3 = 0; dir3 < 4; dir3++)
	//										{
	//											if (check(map, i3, j3, dir3) == true)
	//											{
	//												count++;
	//											}
	//										}
	//									}
	//								}
	//								set_value_of_plane(map, i2, j2, dir2, 0);
	//								map[i2][j2] = 0;
	//							}
	//						}
	//					}
	//				}
	//				set_value_of_plane(map, i1, j1, dir1, 0);
	//				map[i1][j1] = 0;
	//			}
	//		}
	//	}
	//}
	//cout << count << endl;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << setiosflags(ios::fixed) << setprecision(3) << setw(6) << (head[i][j] * 100.0) / Times << "  ";
		}
		cout << endl;
	}
	cout << endl << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << setiosflags(ios::fixed) << setprecision(3) << setw(6) << (body[i][j] * 100.0) / Times << "  ";
		}
		cout << endl;
	}
	cout << endl << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << setiosflags(ios::fixed) << setprecision(3) << setw(6) << (score[i][j] * 100.0) / Times << "  ";
		}
		cout << endl;
	}
	cout << endl << endl;
	print(cout, head);
	cout << endl << endl;
	print(cout, body);
	cout << endl << endl;
	print(cout, score);

	ofstream out;
	out.open("out.txt", ios::out);
	out << endl << endl;
	print(out, head);
	out << endl << endl;
	print(out, body);
	out << endl << endl;
	print(out, score);
	out.close();
}
