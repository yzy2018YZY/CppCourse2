//1850059 计1班 杨志远

#include <iostream>
#include <iomanip>
using namespace std;

const int StudentsCount = 10;

struct student
{
	int no;
	char name[9];
	float score[3];
	int index;
	float sumScore;
	bool isMax;
};

void PrintOneStudentInfo(student &s, bool sum = false)
{
	cout << setiosflags(ios::left) << setw(4) << s.index << " " << setw(7) << s.no << " " << setw(8) << s.name << " ";
	for (int k = 0; k < 3; k++)
	{
		cout << setw(4) << resetiosflags(ios::fixed) << setprecision(3) << s.score[k] << " ";
	}
	if (sum)
	{
		cout << setw(5) << resetiosflags(ios::fixed) << setprecision(4) << s.sumScore << endl;
	}
	else
	{
		cout << setw(5) << setiosflags(ios::fixed) << setprecision(2) << s.sumScore / 3 << endl;
	}
}

int main()
{
	student students[StudentsCount];
	float maxScore = 0;
	for (int i = 0; i < StudentsCount; i++)
	{
		cout << "请输入第" << setw(2) << i + 1 << "个学生的信息：";
		cin >> students[i].no >> students[i].name;
		for (int k = 0; k < 3; k++)
		{
			cin >> students[i].score[k];
		}
		students[i].index = i + 1;
	}
	for (int i = 0; i < StudentsCount; i++)
	{
		float sum = 0;
		for (int k = 0; k < 3; k++)
		{
			sum += students[i].score[k];
		}
		students[i].sumScore = sum;
		maxScore = maxScore > sum ? maxScore : sum;
	}
	for (int i = 0; i < StudentsCount; i++)
	{
		students[i].isMax = (students[i].sumScore == maxScore);
	}
	cout << endl;
	cout << StudentsCount << "个学生的成绩为：" << endl;
	cout << "序号 学号    姓名     三门课成绩     平均成绩" << endl;
	cout << "=============================================" << endl;
	for (int i = 0; i < StudentsCount; i++)
	{
		PrintOneStudentInfo(students[i]);
	}
	cout << endl;
	cout << "最高分学生成绩:" << endl;
	cout << "序号 学号    姓名     三门课成绩     总成绩" << endl;
	cout << "=============================================" << endl;
	for (int i = 0; i < StudentsCount; i++)
	{
		if (students[i].isMax)
		{
			PrintOneStudentInfo(students[i], true);
		}
	}
	return 0;
}
