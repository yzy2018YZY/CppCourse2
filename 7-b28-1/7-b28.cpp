//1850059 ��1�� ��־Զ
//read������Ҫ�޸ģ�Խ�����⣩��line����������Ҫ�Ľ���/*...*/...�����⣩
#if defined(_MSC_VER)

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <io.h>
#include <string.h>
using namespace std;

const char Separator = '\\';
const char SeparatorStr[] = "\\";

#endif

#if defined(__linux) || defined(__linux__)

#include <iostream>
#include <iomanip>
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
const char *NameExtension[] = { "h", "c", "cpp" };
const char *WrongInfo[] =
{
	"ѧ�Ų�ƥ��",
	"�༶��ƥ��",
	"������ƥ��",
	"δȡ��������Ϣ",
	"������Ϣ��ȫ",
	"������Ϣ����",
	"δ�ύ",
};
enum WrongInfoIndex
{
	WIWrongNO = 0,
	WIWrongClass,
	WIWrongName,
	WIFirstLineInvalid,
	WIFirstLineIncomplete,
	WIFirstLineTooMuch,
	WIUncommitted,
};
const char *Optional[] =
{
	"checktitle",
	"linecount",
	"lineanalyse"
};
enum Settings
{
	ModeCheckTitle = 0,
	ModeLineCount,
	ModeLineAnalyze,
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
	cout << "Usage : " << procname << " -ָ��        �γ̱�� �ļ���" << endl;
	cout << "        " << procname << " -checktitle  100384   3-b3.cpp" << endl;
	cout << "        " << procname << " -checktitle  100215   all" << endl;
	cout << "        " << procname << " -linecount   100384   3-b3.cpp" << endl;
	cout << "        " << procname << " -linecount   100215   all" << endl;
	cout << "        " << procname << " -lineanalyse 100384   3-b3.cpp" << endl;
	cout << "        " << procname << " -lineanalyse 100215   all" << endl;
	return 0;
}

void print_student_info(const StudentInfo students[], int index, const char fileName[])
{
	cout << students[index].m_iNo << "-" << students[index].m_chName << "-" << students[index].m_chClassName << " : " << fileName << " : ";
}

//�����չ��
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

//��ѧ����������ṹ�������Ϣ
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

//���ַ���תΪ���֣�-1Ϊ�Ƿ�
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

//���ļ��������ж��Ƿ���Ͽγ���������ȡѧ��
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

//��ѧ���б�ѧ������
void sort_students_list(StudentInfo students[], int studentsCount)
{
	int sortedList[MaxStudentsNum];
	StudentInfo tempStudents[MaxStudentsNum];
	memcpy(&tempStudents, students, sizeof(StudentInfo) * MaxStudentsNum);
	for (int i = 0; i < studentsCount; i++)
		sortedList[i] = i;
	for (int i = studentsCount - 1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (students[sortedList[j]].m_iNo > students[sortedList[j + 1]].m_iNo)
			{
				int temp = sortedList[j];
				sortedList[j] = sortedList[j + 1];
				sortedList[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < studentsCount; i++)
	{
		memcpy(&students[i], &tempStudents[sortedList[i]], sizeof(StudentInfo));
	}
}

//�ӽṹ���в���ѧ��
int index_of_student(const StudentInfo students[], int studentsCount, int stuNum)
{
	for (int i = 0; i < studentsCount; i++)
	{
		if (stuNum == students[i].m_iNo)
			return i;
	}
	return -1;
}

//��������ַ�����ѧ����Ϣ�Ƿ������indexΪѧ���ڽṹ���е�λ��
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
		cout << WrongInfo[WIWrongNO] << " ";
		wrongInfo += (2 << WIWrongNO);
	}
	if (strcmp(students[index].m_chName, str[0]) != 0 && strcmp(students[index].m_chName, str[1]) != 0 && strcmp(students[index].m_chName, str[2]) != 0)
	{
		cout << WrongInfo[WIWrongName] << " ";
		wrongInfo += (2 << WIWrongName);
	}
	if (strcmp(students[index].m_chClassName, str[0]) != 0 && strcmp(students[index].m_chClassName, str[1]) != 0 && strcmp(students[index].m_chClassName, str[2]) != 0
		&& strcmp(students[index].m_chClassSubName, str[0]) != 0 && strcmp(students[index].m_chClassSubName, str[1]) != 0 && strcmp(students[index].m_chClassSubName, str[2]) != 0)
	{
		cout << WrongInfo[WIWrongClass] << " ";
		wrongInfo += (2 << WIWrongClass);
	}
	if (wrongInfo == 0)
	{
		cout << "ͨ��";
	}
	cout << endl;
	return -wrongInfo;
}

int check_title(ifstream &in, const StudentInfo students[], int studentsCount, int studentNo, const char fileName[])
{
	char tempStr[4][DefaultStringLength] = { "", "", "" };
	int tempCh = in.peek();
	int index = index_of_student(students, studentsCount, studentNo);
	print_student_info(students, index, fileName);
	while (tempCh == ' ' || tempCh == '\t' || tempCh == 0x0D || tempCh == 0x0A || tempCh == EOF)//�����ո�
	{
		in.get();
		tempCh = in.peek();
	}
	tempCh = in.get();//���ע�Ϳ�ͷ
	if (tempCh != '/')
	{
		cout << WrongInfo[WIFirstLineInvalid] << endl;
		return -1;
	}
	tempCh = in.get();
	if (tempCh != '/' && tempCh != '*' || in.peek() == 0x0D || in.peek() == 0x0A)
	{
		cout << WrongInfo[WIFirstLineInvalid] << endl;
		return -1;
	}
	bool doubleSlash = (tempCh == '/');//˫б�ܵ�ע��
	char strLine[DefaultStringLength * 3] = "";
	in.getline(strLine, DefaultStringLength * 3 - 1);
	int i, p, g;
	for (i = 0, p = 0, g = 0; i < 4 && strLine[g] != '\0'; )//�ϴ�д�ģ�̫���ӣ�û����
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
		cout << WrongInfo[WIFirstLineIncomplete] << endl;
		return -1;
	}
	if (i > 3)
	{
		cout << WrongInfo[WIFirstLineTooMuch] << endl;
		return -1;
	}
	if (tempStr[2][p - 1] == '*')//�����������ַ���ĩβ��*
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
		cout << WrongInfo[WIFirstLineInvalid] << endl;
		return -1;
	}
	//cout << tempStr[0] << "  " << tempStr[1] << " -" << tempStr[2] << "-" << endl;
	return check_student_info(students, studentsCount, tempStr, index);
}

//��鵥���ļ������ף�indexΪѧ���ڽṹ���е�λ��
void check_one_file(const StudentInfo students[], int studentsCount, int index, const char fileName[])
{
	ifstream in(fileName, ios::in | ios::binary);
	if (!in.is_open())//û���ļ�
	{
		print_student_info(students, index, (strrchr(fileName, Separator) + 1));
		cout << WrongInfo[WIUncommitted] << endl;
	}
	else//����ļ�����
	{
		check_title(in, students, studentsCount, students[index].m_iNo, strrchr(fileName, Separator) + 1);
	}
	in.close();
}

//ͳ��ÿ�����͵���Ϣ
int count_line(const char fileName[], int &contentCount, int &effectiveCount, int &commentCount)
{
	const int maxStrLength = 1024;
	int lineCount = 0;
	ifstream in;
	in.open(fileName, ios::in);
	if (!in.is_open())
		return -1;
	char temp[maxStrLength];
	bool inComment = false;//�ڶ���ע����
	for(lineCount = 0, contentCount = 0, effectiveCount = 0, commentCount = 0; in.eof() == false; lineCount++)
	{
		in.getline(temp, maxStrLength);
		bool isContent = false;
		int len = strlen(temp);
		char firstCh = 0;
		char *doubleSlash = strstr(temp, "//"), *singleSlashStart = strstr(temp, "/*"), *singleSlashEnd = strstr(temp, "*/");
		for (int i = 0; i < len; i++)
		{
			if (temp[i] != ' ' && temp[i] != '\t' && temp[i] != '\n' && temp[i] != '\r')
			{
				isContent = true;//������
				if (!firstCh)//��һ����Ч���ַ�
					firstCh = temp[i];
			}
		}
		if (in.eof() && len == 0)//һ������
			lineCount--;
		if (isContent)//������
			contentCount++;
		if ((!inComment && (doubleSlash != NULL || (singleSlashStart != NULL && singleSlashEnd != NULL))) || (inComment && singleSlashEnd != NULL))//����ע��
		{
			inComment = false;
			commentCount++;
		}
		if (!inComment && ((doubleSlash > temp) || (singleSlashStart > temp)) && firstCh != '/')//ͬʱ������ע��
			effectiveCount++;
		if (singleSlashStart != NULL && !(doubleSlash != NULL && doubleSlash < singleSlashStart) && singleSlashEnd == NULL)//����ע��
			inComment = true;
		if (inComment)
			commentCount++;
	}
	in.close();
	effectiveCount += (lineCount - commentCount);
	return lineCount;
}

//���Ĺ���
void core_func(const StudentInfo students[], const int studentsCount, const int mode, const int index, const char filePath[], const char fileName[])
{
	if (mode == ModeCheckTitle)
		check_one_file(students, studentsCount, index, filePath);
	else if (mode == ModeLineCount || mode == ModeLineAnalyze)
	{
		int commentCount, contentCount, effectiveCount;
		int lineCount = count_line(filePath, contentCount, effectiveCount, commentCount);
		print_student_info(students, index, fileName);
		if (lineCount >= 0)
		{
			if(mode == ModeLineCount)
				cout << "������-" << lineCount << endl;
			else
				cout << "������-" << lineCount << " ������-" << contentCount << " ��Ч���-" << effectiveCount << " ע��-" << commentCount << " ����-" << setiosflags(ios::fixed) << setprecision(2) << double(commentCount) / (commentCount + effectiveCount) * 100 << "%" << endl;
		}
			
		else
			cout << WrongInfo[WIUncommitted] << endl;
	}
}

int main(int argc, char *argv[])
{
	int mode = -1;
	if (argc != 4)//������
	{
		usage(strrchr(argv[0], Separator) + 1);
		return 1;
	}
	for (int i = 0; i < sizeof(Optional) / sizeof(Optional[0]); i++)
		if (strcmp(&argv[1][1], Optional[i]) == 0)
			mode = i;
	if (mode < 0)
	{
		cout << "����" << argv[1] << "����" << endl;
		return 2;
	}
	long long courseNumber = str_to_number<long long>(argv[2]);//����γ̺ź��ļ���
	if (courseNumber < 0)
	{
		cout << "����γ̺Ŵ���" << endl;
		return 3;
	}
	bool allMode = (strcmp(argv[3], "all") == 0);
	if (!allMode)//���Դ�����ļ�����չ��
	{
		if (check_file_extension(argv[3]) == false)
		{
			cout << "����Դ�����ļ�" << endl;
			return 4;
		}
	}

	StudentInfo students[MaxStudentsNum];
	int studentsCount = 0;
	char filePath[DefaultStringLength] = "";
	char listPath[DefaultStringLength] = "";
	strcpy(filePath, argv[0]);//��ȡ�γ������ļ�����·��
	filePath[strrchr(filePath, Separator) - filePath] = '\0';//��ȥ·���е����һ����б��
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
	ifstream in(listPath, ios::in);//��ȡ�γ�����
	if (!in.is_open())
	{
		cout << "û���ҵ��γ̵�ѧ������" << (strrchr(listPath, Separator) + 1) << endl;
		return 11;
	}
	else
	{
		studentsCount = read_students_list(in, students);//��ȡѧ���������ṹ��
		sort_students_list(students, studentsCount);//����
		in.close();
		if (studentsCount < 0)
		{
			cout << "�޷���ȡѧ������" << endl;
			return 13;
		}
	}

	char findFilePath[DefaultStringLength] = "";
	strcpy(findFilePath, filePath);
	int index = -1, preIndex = -1;
#if defined(_MSC_VER)
	strcat(findFilePath, "\\*.*");
#endif
#if defined(__linux) || defined(__linux__)
	strcat(findFilePath, "/*.*");
#endif

#if defined(_MSC_VER)
	struct _finddata_t file;
	int curFile;
	long HANDLE; //��¼��һ�δ򿪵��ļ�������ر�ʱ���ô�ֵ
	curFile = HANDLE = _findfirst(findFilePath, &file);	//Ҳ��дΪ ��C:/Windows/*.*��
	
	while (curFile >= 0)
	{
		int studentNo = get_student_NO_from_subfile(file.name, argv[2]);
		if ((file.attrib & _A_SUBDIR) != 0 && studentNo >= 0)//ĳ��ѧ�����ļ���
		{
			preIndex = index;
			index = index_of_student(students, studentsCount, studentNo);
			if (index < 0)//��ѧ�����ڿγ�������
			{
				curFile = _findnext(HANDLE, &file);
				continue;
			}
			char curFilePath[DefaultStringLength] = "";//���㵱ǰ�ļ���·��
			if (allMode)//������all��ȫ�����
			{
				struct _finddata_t innerFile;//��Ŀ¼
				int innerCurFile;
				long innerHANDLE;
				char innerFindFilePath[DefaultStringLength] = "";//���㵱ǰ�ļ���Ŀ¼��·��
				strcpy(innerFindFilePath, filePath);
				strcat(innerFindFilePath, SeparatorStr);
				strcat(innerFindFilePath, file.name);
				strcat(innerFindFilePath, "\\*.*");
				innerCurFile = innerHANDLE = _findfirst(innerFindFilePath, &innerFile);
				while (innerCurFile != -1)
				{
					if ((innerFile.attrib & _A_SUBDIR) == 0 && check_file_extension(innerFile.name) == true)//��չ����ȷ���ļ�
					{
						strcpy(curFilePath, filePath);//���㵱ǰ�ļ���Ŀ¼�е��ļ���·��
						strcat(curFilePath, SeparatorStr);
						strcat(curFilePath, file.name);
						strcat(curFilePath, SeparatorStr);
						strcat(curFilePath, innerFile.name);
						core_func(students, studentsCount, mode, index, curFilePath, innerFile.name);
					}
					innerCurFile = _findnext(innerHANDLE, &innerFile);
				}
				_findclose(innerHANDLE);
				cout << endl;
			}
#endif

#if defined(__linux) || defined(__linux__)
	DIR            *dir;
	struct dirent  *node;
	if ((dir = opendir(filePath)) == NULL)
	{
		cout << "Ŀ¼" << filePath << "����ʧ��" << endl;
		return 12;
	}
	while ((node = readdir(dir)) != NULL)
	{
		int studentNo = get_student_NO_from_subfile(node->d_name, argv[2]);
		if ((node->d_type & DT_DIR) != 0 && studentNo >= 0)//ĳ��ѧ�����ļ���
		{
			preIndex = index;
			index = index_of_student(students, studentsCount, studentNo);
			if (index < 0)//��ѧ�����ڿγ�������
			{
				node = readdir(dir);
				continue;
			}
			char curFilePath[DefaultStringLength] = "";//���㵱ǰ�ļ���·��
			if (allMode)//������all��ȫ�����
			{
				char innerFindFilePath[DefaultStringLength] = "";//���㵱ǰ�ļ���Ŀ¼��·��
				strcpy(innerFindFilePath, filePath);
				strcat(innerFindFilePath, SeparatorStr);
				strcat(innerFindFilePath, node->d_name);
				DIR            *innerDir;
				struct dirent  *innerNode;
				if ((innerDir = opendir(innerFindFilePath)) == NULL)
				{
					cout << "Ŀ¼" << innerFindFilePath << "����ʧ��" << endl;
					return 12;
				}
				while ((innerNode = readdir(innerDir)) != NULL)
				{
					if ((innerNode->d_type & DT_DIR) == 0 && check_file_extension(innerNode->d_name) == true)//��׺����ȷ���ļ�
					{
						strcpy(curFilePath, filePath);//���㵱ǰ�ļ���Ŀ¼�е��ļ���·��
						strcat(curFilePath, SeparatorStr);
						strcat(curFilePath, node->d_name);
						strcat(curFilePath, SeparatorStr);
						strcat(curFilePath, innerNode->d_name);
						core_func(students, studentsCount, mode, index, curFilePath, innerNode->d_name);
					}
				}
				closedir(innerDir);
				cout << endl;
			}
#endif
			else//ֻ���argv[3]���ļ�
			{
				strcpy(curFilePath, filePath);
				strcat(curFilePath, SeparatorStr);
#if defined(_MSC_VER)
				strcat(curFilePath, file.name);
#endif
#if defined(__linux) || defined(__linux__)
				strcat(curFilePath, node->d_name);
#endif
				strcat(curFilePath, SeparatorStr);
				strcat(curFilePath, argv[3]);
				if (index != preIndex + 1)//�ļ��б���������ѧ����δ��¼ƽ̨
				{
					print_student_info(students, preIndex + 1, argv[3]);
					cout << WrongInfo[WIUncommitted] << endl;
				}
				core_func(students, studentsCount, mode, index, curFilePath, argv[3]);
			}
		}
#ifdef _MSC_VER
		curFile = _findnext(HANDLE, &file);
#endif
	}

#if defined(_MSC_VER)
	_findclose(HANDLE);
#endif
#if defined(__linux) || defined(__linux__)
	closedir(dir);
#endif

	return 0;
}