//1850059 计1班 杨志远

#if defined(_MSC_VER)

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <io.h>
#include <string.h>

const char Separator = '\\';
const char SeparatorStr[] = "\\";

#endif


#if defined(__linux) || defined(__linux__)

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

const char Separator = '/';
const char SeparatorStr[] = "/";

#endif

#define DefaultStringLength 256
#define MaxStudentsNum 100
const char *NameExtension[] = { "h", "c", "cpp" };
const char *WrongInfo[] =
{
	NULL,
	"学号不匹配",
	"班级不匹配",
	"姓名不匹配",
	"未取到首行信息",
	"首行信息不全",
	"首行信息过多",
	"未提交",
};
enum WrongInfoIndex
{
	WrongNO = 1,
	WrongClass,
	WrongName,
	FirstLineInvalid,
	FirstLineIncomplete,
	FirstLineTooMuch,
	Uncommitted,
};

struct StudentInfo
{
	int m_iNo;
	char m_chName[12];
	char m_chClassName[30];
	char m_chClassSubName[12];
};

inline char peek(FILE *f) 
{
	char ans = getc(f);
	ungetc(ans, f);
	return ans;
}

int my_getline(FILE *in, char str[], int maxLen)
{
	int c, i;
	for (i = 0; i < maxLen - 1 && (c = fgetc(in)) != '\n' && c != EOF; i++)
		str[i] = c;
	if (c == '\n')
	{
		str[i++] = '\n';
	}
	str[i] = '\0';
	return i;
}

int usage(const char *procname)
{
	printf("Usage : %s -checktitle 课程编号 文件名\n", procname);
	printf("        %s -checktitle 100384   3-b3.cpp\n", procname);
	printf("        %s -checktitle 100215   all\n", procname);
	return 0;
}

//检查扩展名，0为错误
int check_file_extension(const char str[])
{
	int dot = strchr(str, '.') - str;
	if (dot <= 0)
		return 0;
	int i;
	for (i = 0; i < sizeof(NameExtension) / sizeof(NameExtension[0]); i++)
	{
		if (strcmp(&str[dot + 1], NameExtension[i]) == 0)
			return 1;
	}
	return 0;
}

//从学生名单中向结构体读入信息
int read_students_list(FILE *in, struct StudentInfo students[])
{
	int studentsCount = 0;
	int i;
	for (i = 0; feof(in) == 0; i++)
	{
		fscanf(in, "%d%s%s%s", &students[i].m_iNo, students[i].m_chName, students[i].m_chClassName, students[i].m_chClassSubName);
		if (feof(in) != 0)
			break;
		//printf(students[i].m_iNo << "  " << students[i].m_chName << "  " << students[i].m_chClassName << "  " << students[i].m_chClassSubName << endl;
		studentsCount++;
	}
	return studentsCount;
}

//将字符串转为数字，-1为非法
int str_to_number(const char str[])
{
	int num = 0, i;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return -1;
		num *= 10;
		num += (str[i] - '0');
	}
	return num;
}

long long str_to_number_ll(const char str[])//重载
{
	long long num = 0, i;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return -1;
		num *= 10;
		num += (str[i] - '0');
	}
	return num;
}

//从文件夹名称判断是否符合课程名，并提取学号
int get_student_NO_from_subfile(const char fileName[], const char courseNum[])
{
	int len = strlen(courseNum), i;
	for (i = 0; i < len; i++)
	{
		if (fileName[i] != courseNum[i])
			return -1;
	}
	return str_to_number(&fileName[len + 1]);
}

//从结构体中查找学生
int index_of_student(const struct StudentInfo students[], int studentsCount, int stuNum)
{
	int i;
	for (i = 0; i < studentsCount; i++)
	{
		if (stuNum == students[i].m_iNo)
			return i;
	}
	return -1;
}

//检查三个字符串与学生信息是否相符，index为学生在结构体中的位置
int check_student_info(const struct StudentInfo students[], int studentsCount, char str[3][DefaultStringLength], int index)
{
	int checkNum = -1, checkClass = -1, checkName = -1, wrongInfo = 0, No = -1, i;
	for (i = 0; i < 3; i++)
	{
		if (No < 0)
			No = str_to_number(str[i]);
		else
			break;
	}
	if (No != students[index].m_iNo)
	{
		printf(" %s",WrongInfo[WrongNO]);
		wrongInfo += (2 << WrongNO);
	}
	if (strcmp(students[index].m_chName, str[0]) != 0 && strcmp(students[index].m_chName, str[1]) != 0 && strcmp(students[index].m_chName, str[2]) != 0)
	{
		printf(" %s", WrongInfo[WrongName]);
		wrongInfo += (2 << WrongName);
	}
	if (strcmp(students[index].m_chClassName, str[0]) != 0 && strcmp(students[index].m_chClassName, str[1]) != 0 && strcmp(students[index].m_chClassName, str[2]) != 0
		&& strcmp(students[index].m_chClassSubName, str[0]) != 0 && strcmp(students[index].m_chClassSubName, str[1]) != 0 && strcmp(students[index].m_chClassSubName, str[2]) != 0)
	{
		printf(" %s", WrongInfo[WrongClass]);
		wrongInfo += (2 << WrongClass);
	}
	if (wrongInfo == 0)
	{
		printf(" 通过");
	}
	printf("\n");
	return -wrongInfo;
}

int check_title(FILE *in, const struct StudentInfo students[], int studentsCount, int studentNo, const char fileName[])
{
	char tempStr[4][DefaultStringLength] = { "", "", "" };
	int tempCh = peek(in);
	int index = index_of_student(students, studentsCount, studentNo);
	printf("%d-%s %s:", studentNo, students[index].m_chName, fileName);
	while (tempCh == ' ' || tempCh == '\t' || tempCh == 0x0D || tempCh == 0x0A || tempCh == EOF)//消除空格
	{
		fgetc(in);
		tempCh = peek(in);
	}
	tempCh = fgetc(in);//检查注释开头
	if (tempCh != '/')
	{
		printf(" %s\n", WrongInfo[FirstLineInvalid]);
		return -1;
	}
	tempCh = fgetc(in);
	if (tempCh != '/' && tempCh != '*' || peek(in) == 0x0D || peek(in) == 0x0A)
	{
		printf(" %s\n", WrongInfo[FirstLineInvalid]);
		return -1;
	}
	int doubleSlash = (tempCh == '/');//双斜杠的注释
	char strLine[DefaultStringLength * 3] = "";
	my_getline(in, strLine, DefaultStringLength * 3 - 1);
	int i, p, g;
	for (i = 0, p = 0, g = 0; i < 4 && strLine[g] != '\0'; )
	{
		tempCh = strLine[g++];
		if (tempCh == ' ' || tempCh == '\t')
		{
			if (tempStr[i][0] != '\0')
			{
				tempStr[i++][p + 1] = '\0';
				p = 0;
			}
			continue;
		}
		if (tempCh == 0x0D || tempCh == 0x0A)
		{
			break;
		}
		if (tempCh == '*' && strLine[g] == '/')
		{
			doubleSlash = 1;
			break;
		}
		tempStr[i][p++] = tempCh;
	}
	if (tempStr[0][0] == '\0' || tempStr[1][0] == '\0' || tempStr[2][0] == '\0')
	{
		printf(" %s\n", WrongInfo[FirstLineIncomplete]);
		return -1;
	}
	if (i > 3)
	{
		printf(" %s\n", WrongInfo[FirstLineTooMuch]);
		return -1;
	}
	if (tempStr[2][p - 1] == '*')//消除第三个字符串末尾的*
		tempStr[2][p - 1] = '\0';
	
	int k;
	for (k = g; strLine[k] != '\0'; k++)
	{
		if (tempCh == '*' && strLine[g++] == '/')
		{
			doubleSlash = 1;
			break;
		}
	}
	if (doubleSlash == 0)
	{
		printf(" %s\n", WrongInfo[FirstLineInvalid]);
		return -1;
	}
	return check_student_info(students, studentsCount, tempStr, index);
}

//检查单个文件的行首，index为学生在结构体中的位置
void check_one_file(const struct StudentInfo students[], int studentsCount, int index, const char fileName[])
{
	FILE *in = fopen(fileName, "rb");
	if (in == NULL)//没有文件
	{
		printf("%d-%s %s: %s\n", students[index].m_iNo, students[index].m_chName, (strrchr(fileName, Separator) + 1), WrongInfo[Uncommitted]);
	}
	else//检查文件首行
	{
		check_title(in, students, studentsCount, students[index].m_iNo, strrchr(fileName, Separator) + 1);
		fclose(in);
	}
}

int main(int argc, char *argv[])
{
	if (argc != 4)//检查参数
	{
		usage(strrchr(argv[0], Separator) + 1);
		return 1;
	}
	if (strcmp(argv[1], "-checktitle") != 0)
	{
		printf("命令%s错误\n", argv[1]);
		return 2;
	}
	long long courseNumber = str_to_number_ll(argv[2]);//输入课程号和文件名
	if (courseNumber < 0)
	{
		printf("输入课程号错误\n");
		return 3;
	}
	int allMode = (strcmp(argv[3], "all") == 0);
	if (!allMode)//检查源程序文件的扩展名
	{
		if (check_file_extension(argv[3]) == 0)
		{
			printf("不是源程序文件\n");
			return 4;
		}
	}

	struct StudentInfo students[MaxStudentsNum];
	int studentsCount = 0;
	char filePath[DefaultStringLength] = "";
	char listPath[DefaultStringLength] = "";
	strcpy(filePath, argv[0]);
	filePath[strrchr(filePath, Separator) - filePath] = '\0';//截去路径中的最后一个右斜杠
#if defined(_MSC_VER)
	strcat(filePath, "\\source");
#endif
#if defined(__linux) || defined(__linux__)
	strcat(filePath, "/source");
#endif
	strcpy(listPath, filePath);
	strcat(listPath, SeparatorStr);
	strcat(listPath, argv[2]);
	strcat(listPath, ".dat");
	FILE *in = fopen(listPath, "r");
	if (in == NULL)
	{
		printf("没有找到课程的学生名单%s\n", (strrchr(listPath, Separator) + 1));
		return 11;
	}
	else
	{
		studentsCount = read_students_list(in, students);
		fclose(in);
	}

	short subFileVisited[MaxStudentsNum] = { 0 };
	char findFilePath[DefaultStringLength] = "";
	strcpy(findFilePath, filePath);
#if defined(_MSC_VER)
	strcat(findFilePath, "\\*.*");
#endif
#if defined(__linux) || defined(__linux__)
	strcat(findFilePath, "/*.*");
#endif

#if defined(_MSC_VER)
	struct _finddata_t file;
	int curFile;
	long HANDLE; //记录第一次打开的文件句柄，关闭时需用此值
	curFile = HANDLE = _findfirst(findFilePath, &file);	//也可写为 “C:/Windows/*.*”

	while (curFile != -1)
	{
		int studentNo = get_student_NO_from_subfile(file.name, argv[2]);
		if ((file.attrib & _A_SUBDIR) != 0 && studentNo >= 0)//某个学生的文件夹
		{
			int index = index_of_student(students, studentsCount, studentNo);
			if (index < 0)//该学生不在课程名单上
			{
				curFile = _findnext(HANDLE, &file);
				continue;
			}
			subFileVisited[index] = 1;//记录每个名单上学生所对应的文件夹是否被访问过
			char curFileName[DefaultStringLength] = "";//计算当前文件的路径
			if (allMode)//输入了all，全部检查
			{
				struct _finddata_t innerFile;//子目录
				int innerCurFile;
				long innerHANDLE;
				char innerFindFilePath[DefaultStringLength] = "";//计算当前文件子目录的路径
				strcpy(innerFindFilePath, filePath);
				strcat(innerFindFilePath, SeparatorStr);
				strcat(innerFindFilePath, file.name);
				strcat(innerFindFilePath, "\\*.*");
				innerCurFile = innerHANDLE = _findfirst(innerFindFilePath, &innerFile);
				while (innerCurFile != -1)
				{
					if ((innerFile.attrib & _A_SUBDIR) == 0 && check_file_extension(innerFile.name) != 0)//扩展名正确的文件
					{
						strcpy(curFileName, filePath);//计算当前文件子目录中的文件的路径
						strcat(curFileName, SeparatorStr);
						strcat(curFileName, file.name);
						strcat(curFileName, SeparatorStr);
						strcat(curFileName, innerFile.name);
						check_one_file(students, studentsCount, index, curFileName);
					}
					innerCurFile = _findnext(innerHANDLE, &innerFile);
				}
				_findclose(innerHANDLE);
				printf("\n");
			}
			else//只检查argv[3]的文件
			{
				strcpy(curFileName, filePath);
				strcat(curFileName, SeparatorStr);
				strcat(curFileName, file.name);
				strcat(curFileName, SeparatorStr);
				strcat(curFileName, argv[3]);
				check_one_file(students, studentsCount, index, curFileName);
			}
		}
		curFile = _findnext(HANDLE, &file);
	}
	_findclose(HANDLE);
#endif

#if defined(__linux) || defined(__linux__)

	DIR            *dir;
	struct dirent  *node;
	if ((dir = opendir(filePath)) == NULL)
	{
		printf("目录%s访问失败\n", filePath);
		return 12;
	}
	while ((node = readdir(dir)) != NULL)
	{
		//printf(node->d_name << ((node->d_type & DT_DIR) != 0 ? "是文件夹" : "") << endl;
		int studentNo = get_student_NO_from_subfile(node->d_name, argv[2]);
		if ((node->d_type & DT_DIR) != 0 && studentNo >= 0)//某个学生的文件夹
		{
			int index = index_of_student(students, studentsCount, studentNo);
			if (index < 0)//该学生不在课程名单上
			{
				node = readdir(dir);
				continue;
			}
			subFileVisited[index] = 1;//记录每个名单上学生所对应的文件夹是否被访问过
			char curFileName[DefaultStringLength] = "";//计算当前文件的路径
			if (allMode)//输入了all，全部检查
			{
				char innerFindFilePath[DefaultStringLength] = "";//计算当前文件子目录的路径
				strcpy(innerFindFilePath, filePath);
				strcat(innerFindFilePath, SeparatorStr);
				strcat(innerFindFilePath, node->d_name);
				DIR            *innerDir;
				struct dirent  *innerNode;
				if ((innerDir = opendir(innerFindFilePath)) == NULL)
				{
					printf("目录%s访问失败\n", innerFindFilePath);
					return 12;
				}
				while ((innerNode = readdir(innerDir)) != NULL)
				{
					if ((innerNode->d_type & DT_DIR) == 0 && check_file_extension(innerNode->d_name) == 1)//后缀名正确的文件
					{
						strcpy(curFileName, filePath);//计算当前文件子目录中的文件的路径
						strcat(curFileName, SeparatorStr);
						strcat(curFileName, node->d_name);
						strcat(curFileName, SeparatorStr);
						strcat(curFileName, innerNode->d_name);
						check_one_file(students, studentsCount, index, curFileName);
					}
				}
				closedir(innerDir);
				printf("\n");
			}
			else//只检查argv[3]的文件
			{
				strcpy(curFileName, filePath);
				strcat(curFileName, SeparatorStr);
				strcat(curFileName, node->d_name);
				strcat(curFileName, SeparatorStr);
				strcat(curFileName, argv[3]);
				check_one_file(students, studentsCount, index, curFileName);
			}
		}
	}
	closedir(dir);

#endif

	if (!allMode)//将所有在名单中但没有对应文件夹的学生列出
	{
		int i;
		for (i = 0; i < studentsCount; i++)
		{
			if (subFileVisited[i] == 0)
				printf("%d-%s %s: %s\n", students[i].m_iNo, students[i].m_chName, argv[3], WrongInfo[Uncommitted]);
		}
	}
	return 0;
}