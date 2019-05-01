//1850059 计1班 杨志远

#if defined(_MSC_VER)

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <io.h>
#include <string.h>
using namespace std;

const char Separator = '\\';
const char SeparatorStr[] = "\\";

#endif


#if defined(__linux) || defined(__linux__)

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
using namespace std;

const char Separator = '/';
const char SeparatorStr[] = "/";

#endif

const int DefaultStringLength = 256;
const int MaxStudentsNum = 100;
const char *NameExtension[] = { "h", "c", "cpp"};
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

int usage(const char *procname)
{
	cout << "Usage : " << procname << " -checktitle 课程编号 文件名" << endl;
	cout << "        " << procname << " -checktitle 100384   3-b3.cpp" << endl;
	cout << "        " << procname << " -checktitle 100215   all" << endl;
	return 0;
}

//检查扩展名
bool check_file_extension(const char str[])
{
	int dot = strchr(str, '.') - str;
	if (dot <= 0)
		return false;
	for (int i = 0; i < sizeof(NameExtension) / sizeof(NameExtension[0]); i++)
	{
		if (strcmp(&str[dot + 1], NameExtension[i]) == 0)
			return true;
	}
	return false;
}

//从学生名单中向结构体读入信息
int read_students_list(ifstream &in, StudentInfo students[])
{
	int studentsCount = 0;
	for (int i = 0; in.eof() == false; i++)
	{
		char temp[DefaultStringLength] = "";
		in >> students[i].m_iNo;
		if (in.eof())
			break;
		if (!in.good())
		{
			return -1;
		}
		in >> students[i].m_chName >> students[i].m_chClassName >> students[i].m_chClassSubName;
		if (in.eof())
		{
			break;
		}
		if (!in.good())
		{
			return -1;
		}
		//cout << students[i].m_iNo << "  " << students[i].m_chName << "  " << students[i].m_chClassName << "  " << students[i].m_chClassSubName << endl;
		studentsCount++;
	}
	return studentsCount;
}

//将字符串转为数字，-1为非法
template <typename T>
T str_to_number(const char str[])
{
	T num = 0;
	for (int i = 0; str[i] != '\0'; i++)
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
	int len = strlen(courseNum);
	for (int i = 0; i < len; i++)
	{
		if (fileName[i] != courseNum[i])
			return -1;
	}
	return str_to_number<int>(&fileName[len + 1]);
}

//从结构体中查找学生
int index_of_student(const StudentInfo students[], int studentsCount, int stuNum)
{
	for (int i = 0; i < studentsCount; i++)
	{
		if (stuNum == students[i].m_iNo)
			return i;
	}
	return -1;
}

//检查三个字符串与学生信息是否相符，index为学生在结构体中的位置
int check_student_info(const StudentInfo students[], int studentsCount, const char str[3][DefaultStringLength], int index)
{
	int checkNum = -1, checkClass = -1, checkName = -1, wrongInfo = 0, No = -1;
	for (int i = 0; i < 3; i++)
	{
		if (No < 0)
			No = str_to_number<int>(str[i]);
		else
			break;
	}
	if (No != students[index].m_iNo)
	{
		cout << " " << WrongInfo[WrongNO];
		wrongInfo += (2 << WrongNO);
	}
	if (strcmp(students[index].m_chName, str[0]) != 0 && strcmp(students[index].m_chName, str[1]) != 0 && strcmp(students[index].m_chName, str[2]) != 0)
	{
		cout << " " << WrongInfo[WrongName];
		wrongInfo += (2 << WrongName);
	}
	if (strcmp(students[index].m_chClassName, str[0]) != 0 && strcmp(students[index].m_chClassName, str[1]) != 0 && strcmp(students[index].m_chClassName, str[2]) != 0
		&& strcmp(students[index].m_chClassSubName, str[0]) != 0 && strcmp(students[index].m_chClassSubName, str[1]) != 0 && strcmp(students[index].m_chClassSubName, str[2]) != 0)
	{
		cout << " " << WrongInfo[WrongClass];
		wrongInfo += (2 << WrongClass);
	}
	if (wrongInfo == 0)
	{
		cout << " 通过";
	}
	cout << endl;
	return -wrongInfo;
}

int check_title(ifstream &in, const StudentInfo students[], int studentsCount, int studentNo, const char fileName[])
{
	char tempStr[4][DefaultStringLength] = { "", "", ""};
	int tempCh = in.peek();
	int index = index_of_student(students, studentsCount, studentNo);
	cout << studentNo << "-" << students[index].m_chName << " " << fileName << ":";
	while (tempCh == ' ' || tempCh == '\t' || tempCh == 0x0D || tempCh == 0x0A || tempCh == EOF)//消除空格
	{
		in.get();
		tempCh = in.peek();
	}
	tempCh = in.get();//检查注释开头
	if (tempCh != '/')
	{
		cout << " " << WrongInfo[FirstLineInvalid] << endl;
		return -1;
	}
	tempCh = in.get();
	if (tempCh != '/' && tempCh != '*' || in.peek() == 0x0D || in.peek() == 0x0A)
	{
		cout << " " << WrongInfo[FirstLineInvalid] << endl;
		return -1;
	}
	bool doubleSlash = (tempCh == '/');//双斜杠的注释
	char strLine[DefaultStringLength * 3] = "";
	in.getline(strLine, DefaultStringLength * 3 - 1);
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
			doubleSlash = true;
			break;
		}
		tempStr[i][p++] = tempCh;
	}
	if (tempStr[0][0] == '\0' || tempStr[1][0] == '\0' || tempStr[2][0] == '\0')
	{
		cout << " " << WrongInfo[FirstLineIncomplete] << endl;
		return -1;
	}
	if (i > 3)
	{
		cout << " " << WrongInfo[FirstLineTooMuch] << endl;
		return -1;
	}
	if (tempStr[2][p - 1] == '*')//消除第三个字符串末尾的*
		tempStr[2][p - 1] = '\0';
		
	for (int k = g; strLine[k] != '\0'; k++)
	{
		if (tempCh == '*' && strLine[g++] == '/')
		{
			doubleSlash = true;
			break;
		}
	}
	if (!doubleSlash)
	{
		cout << " " << WrongInfo[FirstLineInvalid] << endl;
		return -1;
	}
	//cout << tempStr[0] << "  " << tempStr[1] << " -" << tempStr[2] << "-" << endl;
	return check_student_info(students, studentsCount, tempStr, index);
}

//检查单个文件的行首，index为学生在结构体中的位置
void check_one_file(const StudentInfo students[], int studentsCount, int index, const char fileName[])
{
	ifstream in(fileName, ios::in | ios::binary);
	if (!in.is_open())//没有文件
	{
		cout << students[index].m_iNo << "-" << students[index].m_chName << " " << (strrchr(fileName, Separator) + 1) << ": " << WrongInfo[Uncommitted] <<" " << endl;
	}
	else//检查文件首行
	{
		check_title(in, students, studentsCount, students[index].m_iNo, strrchr(fileName, Separator) + 1);
	}
	in.close();
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
		cout << "命令" << argv[1] << "错误" << endl;
		return 2;
	}
	long long courseNumber = str_to_number<long long>(argv[2]);//输入课程号和文件名
	if (courseNumber < 0)
	{
		cout << "输入课程号错误" << endl;
		return 3;
	}
	bool allMode = (strcmp(argv[3], "all") == 0);
	if (!allMode)//检查源程序文件的扩展名
	{
		if (check_file_extension(argv[3]) == false)
		{
			cout << "不是源程序文件" << endl;
			return 4;
		}
	}

	StudentInfo students[MaxStudentsNum];
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
	ifstream in(listPath, ios::in);
	if (!in.is_open())
	{
		cout << "没有找到课程的学生名单" << (strrchr(listPath, Separator) + 1) << endl;
		in.close();
		return 11;
	}
	else
	{
		studentsCount = read_students_list(in, students);
		if (studentsCount < 0)
		{
			cout << "无法读取学生名单" << endl;
			in.close();
			return 13;
		}
		in.close();
	}

	bool subFileVisited[MaxStudentsNum] = { 0 };
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

	while (curFile >= 0)
	{
		int studentNo = get_student_NO_from_subfile(file.name, argv[2]);
		//cout << file.name << endl;
		if ((file.attrib & _A_SUBDIR) != 0 && studentNo >= 0)//某个学生的文件夹
		{
			int index = index_of_student(students, studentsCount, studentNo);
			if (index < 0)//该学生不在课程名单上
			{
				curFile = _findnext(HANDLE, &file);
				continue;
			}
			subFileVisited[index] = true;//记录每个名单上学生所对应的文件夹是否被访问过
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
					if ((innerFile.attrib & _A_SUBDIR) == 0 && check_file_extension(innerFile.name) == true)//扩展名正确的文件
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
				cout << endl;
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
		cout << "目录" << filePath << "访问失败" << endl;
		return 12;
	}
	while ((node = readdir(dir)) != NULL) 
	{
		//cout << node->d_name << ((node->d_type & DT_DIR) != 0 ? "是文件夹" : "") << endl;
		int studentNo = get_student_NO_from_subfile(node->d_name, argv[2]);
		if ((node->d_type & DT_DIR) != 0 && studentNo >= 0)//某个学生的文件夹
		{
			int index = index_of_student(students, studentsCount, studentNo);
			if (index < 0)//该学生不在课程名单上
			{
				node = readdir(dir);
				continue;
			}
			subFileVisited[index] = true;//记录每个名单上学生所对应的文件夹是否被访问过
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
					cout << "目录" << innerFindFilePath << "访问失败" << endl;
					return 12;
				}
				while ((innerNode = readdir(innerDir)) != NULL)
				{
					if ((innerNode->d_type & DT_DIR) == 0 && check_file_extension(innerNode->d_name) == true)//后缀名正确的文件
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
				cout << endl;
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
		for (int i = 0; i < studentsCount; i++)
		{
			if (subFileVisited[i] == false)
				cout << students[i].m_iNo << "-" << students[i].m_chName << " " << argv[3] << ": " << WrongInfo[Uncommitted] << endl;
		}
	}
	return 0;
}