//1850059 计1班 杨志远

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

const int StudentsCount = 10;

struct student
{
	int no;
	char name[9];
	float score[3];
	int index;
	float sumScore;
	int isMax;
};

void PrintOneStudentInfo(struct student s, int sum)
{
	printf("%-4d %-7d %-8s ", s.index, s.no, s.name);
	int k;
	for (k = 0; k < 3; k++)
	{
		printf("%-4g ", s.score[k]);
	}
	if (sum)
	{
		printf("%-5g\n", s.sumScore);
	}
	else
	{
		printf("%-5.2f\n", s.sumScore / 3);
	}
}

int main()
{
	struct student students[10];
	float maxScore = 0;
	int i, k;
	for (i = 0; i < StudentsCount; i++)
	{
		printf("请输入第%2d个学生的信息：", i + 1);
		scanf("%d%s", &students[i].no, students[i].name);
		for (k = 0; k < 3; k++)
		{
			scanf("%f", &students[i].score[k]);
		}
		students[i].index = i + 1;
	}
	for (i = 0; i < StudentsCount; i++)
	{
		float sum = 0;
		for (k = 0; k < 3; k++)
		{
			sum += students[i].score[k];
		}
		students[i].sumScore = sum;
		maxScore = maxScore > sum ? maxScore : sum;
	}
	for (i = 0; i < StudentsCount; i++)
	{
		students[i].isMax = (students[i].sumScore == maxScore);
	}
	printf("\n%d个学生的成绩为：\n", StudentsCount);
	printf("序号 学号    姓名     三门课成绩     平均成绩\n");
	printf("=============================================\n");
	for (i = 0; i < StudentsCount; i++)
	{
		PrintOneStudentInfo(students[i], 0);
	}
	printf("\n最高分学生成绩：\n");
	printf("序号 学号    姓名     三门课成绩     总成绩\n");
	printf("=============================================\n");
	for (i = 0; i < StudentsCount; i++)
	{
		if (students[i].isMax)
		{
			PrintOneStudentInfo(students[i], 1);
		}
	}
	return 0;
}
