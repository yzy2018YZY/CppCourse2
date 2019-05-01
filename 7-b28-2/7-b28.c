//1850059 ��1�� ��־Զ
//read������Ҫ�޸ģ�Խ�����⣩��line����������Ҫ�Ľ���/*...*/...�����⣩
#if defined(_MSC_VER)

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <io.h>
#include <string.h>

const char Separator = '\\';
const char SeparatorStr[] = "\\";

#endif

#if defined(__linux) || defined(__linux__)

#include <stdio.h>
#include <stdbool.h>
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

typedef struct
{
	int m_iNo;
	char m_chName[12];
	char m_chClassName[30];
	char m_chClassSubName[12];
}StudentInfo;

inline char peek(FILE *f)
{
	char ans = getc(f);
	ungetc(ans, f);
	return ans;
}

int my_getline(FILE *in, char str[], const int maxLen)
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
	printf("Usage : %s -ָ��        �γ̱�� �ļ���\n", procname);
	printf("        %s -checktitle  100384   3-b3.cpp\n", procname);
	printf("        %s -checktitle  100215   all\n", procname);
	printf("        %s -linecount   100384   3-b3.cpp\n", procname);
	printf("        %s -linecount   100215   all\n", procname);
	printf("        %s -lineanalyse 100384   3-b3.cpp\n", procname);
	printf("        %s -lineanalyse 100215   all\n", procname);
	return 0;
}

void print_student_info(const StudentInfo students[], const int index, const char fileName[])
{
	printf("%d-%s-%s : %s : ", students[index].m_iNo, students[index].m_chName, students[index].m_chClassName, fileName);
}

//�����չ��
bool check_file_extension(const char str[])
{
	int dot = strchr(str, '.') - str;
	if (dot <= 0)
		return false;
	int i;
	for (i = 0; i < sizeof(NameExtension) / sizeof(NameExtension[0]); i++)
	{
		if (strcmp(&str[dot + 1], NameExtension[i]) == 0)
			return true;
	}
	return false;
}

//��ѧ����������ṹ�������Ϣ
int read_students_list(FILE *in, StudentInfo students[])
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

//���ַ���תΪ���֣�-1Ϊ�Ƿ�
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

long long str_to_number_ll(const char str[])//����
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

//���ļ��������ж��Ƿ���Ͽγ���������ȡѧ��
int get_student_NO_from_subfile(const char fileName[], const char courseNum[])
{
	int len = strlen(courseNum);
	int i;
	for (i = 0; i < len; i++)
	{
		if (fileName[i] != courseNum[i])
			return -1;
	}
	return str_to_number(&fileName[len + 1]);
}

//��ѧ���б�ѧ������
void sort_students_list(StudentInfo students[], const int studentsCount)
{
	int sortedList[MaxStudentsNum], i, j;
	StudentInfo tempStudents[MaxStudentsNum];
	memcpy(&tempStudents, students, sizeof(StudentInfo) * MaxStudentsNum);
	for (i = 0; i < studentsCount; i++)
		sortedList[i] = i;
	for (i = studentsCount - 1; i >= 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (students[sortedList[j]].m_iNo > students[sortedList[j + 1]].m_iNo)
			{
				int temp = sortedList[j];
				sortedList[j] = sortedList[j + 1];
				sortedList[j + 1] = temp;
			}
		}
	}
	for (i = 0; i < studentsCount; i++)
	{
		memcpy(&students[i], &tempStudents[sortedList[i]], sizeof(StudentInfo));
	}
}

//�ӽṹ���в���ѧ��
int index_of_student(const StudentInfo students[], const int studentsCount, const int stuNum)
{
	int i;
	for (i = 0; i < studentsCount; i++)
	{
		if (stuNum == students[i].m_iNo)
			return i;
	}
	return -1;
}

//��������ַ�����ѧ����Ϣ�Ƿ������indexΪѧ���ڽṹ���е�λ��
int check_student_info(const StudentInfo students[], const int studentsCount, char str[3][DefaultStringLength], const int index)
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
		printf("%s ", WrongInfo[WIWrongNO]);
		wrongInfo += (2 << WIWrongNO);
	}
	if (strcmp(students[index].m_chName, str[0]) != 0 && strcmp(students[index].m_chName, str[1]) != 0 && strcmp(students[index].m_chName, str[2]) != 0)
	{
		printf("%s ", WrongInfo[WIWrongName]);
		wrongInfo += (2 << WIWrongName);
	}
	if (strcmp(students[index].m_chClassName, str[0]) != 0 && strcmp(students[index].m_chClassName, str[1]) != 0 && strcmp(students[index].m_chClassName, str[2]) != 0
		&& strcmp(students[index].m_chClassSubName, str[0]) != 0 && strcmp(students[index].m_chClassSubName, str[1]) != 0 && strcmp(students[index].m_chClassSubName, str[2]) != 0)
	{
		printf("%s ", WrongInfo[WIWrongClass]);
		wrongInfo += (2 << WIWrongClass);
	}
	if (wrongInfo == 0)
	{
		printf("ͨ��");
	}
	printf("\n");
	return -wrongInfo;
}

int check_title(FILE *in, const StudentInfo students[], const int studentsCount, const int studentNo, const char fileName[])
{
	char tempStr[4][DefaultStringLength] = { "", "", "" };
	int tempCh = peek(in);
	int index = index_of_student(students, studentsCount, studentNo);
	print_student_info	(students, index, fileName);
	while (tempCh == ' ' || tempCh == '\t' || tempCh == 0x0D || tempCh == 0x0A || tempCh == EOF)//�����ո�
	{
		fgetc(in);
		tempCh = peek(in);
	}
	tempCh = fgetc(in);//���ע�Ϳ�ͷ
	if (tempCh != '/')
	{
		printf("%s\n", WrongInfo[WIFirstLineInvalid]);
		return -1;
	}
	tempCh = fgetc(in);
	if (tempCh != '/' && tempCh != '*' || peek(in) == 0x0D || peek(in) == 0x0A)
	{
		printf("%s\n", WrongInfo[WIFirstLineInvalid]);
		return -1;
	}
	int doubleSlash = (tempCh == '/');//˫б�ܵ�ע��
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
		printf("%s\n", WrongInfo[WIFirstLineIncomplete]);
		return -1;
	}
	if (i > 3)
	{
		printf("%s\n", WrongInfo[WIFirstLineTooMuch]);
		return -1;
	}
	if (tempStr[2][p - 1] == '*')//�����������ַ���ĩβ��*
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
		printf("%s\n", WrongInfo[WIFirstLineInvalid]);
		return -1;
	}
	return check_student_info(students, studentsCount, tempStr, index);
}

//��鵥���ļ������ף�indexΪѧ���ڽṹ���е�λ��
void check_one_file(const StudentInfo students[], const int studentsCount, const int index, const char fileName[])
{
	FILE *in = fopen(fileName, "rb");
	if (in == NULL)//û���ļ�
	{
		print_student_info(students, index, (strrchr(fileName, Separator) + 1));
		printf("%s\n", WrongInfo[WIUncommitted]);
		}
	else//����ļ�����
	{
		check_title(in, students, studentsCount, students[index].m_iNo, strrchr(fileName, Separator) + 1);
		fclose(in);
	}
}

#define maxStrLength 1024
//ͳ��ÿ�����͵���Ϣ
int count_line(const char fileName[], int *contentCount, int *effectiveCount, int *commentCount)
{
	int lineCount = 0;
	FILE *in = fopen(fileName, "r");
	if (in == NULL)
		return -1;
	char temp[maxStrLength];
	bool inComment = false;//�ڶ���ע����
	for (lineCount = 0, (*contentCount) = 0, (*effectiveCount) = 0, (*commentCount) = 0; !feof(in); lineCount++)
	{
		my_getline(in, temp, maxStrLength);
		bool isContent = false;
		int len = strlen(temp), i;
		char firstCh = 0;
		char *doubleSlash = strstr(temp, "//"), *singleSlashStart = strstr(temp, "/*"), *singleSlashEnd = strstr(temp, "*/");
		for (i = 0; i < len; i++)
		{
			if (temp[i] != ' ' && temp[i] != '\t' && temp[i] != '\n' && temp[i] != '\r')
			{
				isContent = true;//������
				if (!firstCh)//��һ����Ч���ַ�
					firstCh = temp[i];
			}
		}
		if (feof(in) && len == 0)//һ������
			lineCount--;
		if (isContent)//������
			(*contentCount)++;
		if ((!inComment && (doubleSlash != NULL || (singleSlashStart != NULL && singleSlashEnd != NULL))) || (inComment && singleSlashEnd != NULL))//����ע��
		{
			inComment = false;
			(*commentCount)++;
		}
		if (!inComment && ((doubleSlash > temp) || (singleSlashStart > temp)) && firstCh != '/')//ͬʱ������ע��
			(*effectiveCount)++;
		if (singleSlashStart != NULL && !(doubleSlash != NULL && doubleSlash < singleSlashStart) && singleSlashEnd == NULL)//����ע��
			inComment = true;
		if (inComment)
			(*commentCount)++;
	}
	fclose(in);
	(*effectiveCount) += (lineCount - (*commentCount));
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
		int lineCount = count_line(filePath, &contentCount, &effectiveCount, &commentCount);
		print_student_info(students, index, fileName);
		if (lineCount >= 0)
		{
			if (mode == ModeLineCount)
				printf("������-%d\n", lineCount);
			else
				printf("������-%d ������-%d ��Ч���-%d ע��-%d ����-%.2f%%\n", lineCount, contentCount, effectiveCount, commentCount, ((double)commentCount / (commentCount + effectiveCount) * 100));
		}
		else
			printf("%s\n", WrongInfo[WIUncommitted]);
	}
}

int main(int argc, char *argv[])
{
	int mode = -1, i;
	if (argc != 4)//������
	{
		usage(strrchr(argv[0], Separator) + 1);
		return 1;
	}
	for (i = 0; i < sizeof(Optional) / sizeof(Optional[0]); i++)
		if (strcmp(&argv[1][1], Optional[i]) == 0)
			mode = i;
	if (mode < 0)
	{
		printf("����%s����\n", argv[1]);
		return 2;
	}
	long long courseNumber = str_to_number_ll(argv[2]);//����γ̺ź��ļ���
	if (courseNumber < 0)
	{
		printf("����γ̺Ŵ���\n");
		return 3;
	}
	bool allMode = (strcmp(argv[3], "all") == 0);
	if (!allMode)//���Դ�����ļ�����չ��
	{
		if (check_file_extension(argv[3]) == false)
		{
			printf("����Դ�����ļ�\n");
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
	FILE *in = fopen(listPath, "r");//��ȡ�γ�����
	if (in == NULL)
	{
		printf("û���ҵ��γ̵�ѧ������%s\n", (strrchr(listPath, Separator) + 1));
		return 11;
	}
	else
	{
		studentsCount = read_students_list(in, students);//��ȡѧ���������ṹ��
		sort_students_list(students, studentsCount);//����
		fclose(in);
		if (studentsCount < 0)
		{
			printf("�޷���ȡѧ������%d\n", studentsCount);
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
				printf("\n");
			}
#endif

#if defined(__linux) || defined(__linux__)
	DIR            *dir;
	struct dirent  *node;
	if ((dir = opendir(filePath)) == NULL)
	{
		printf("Ŀ¼%s����ʧ��\n", filePath);
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
					printf("Ŀ¼%s����ʧ��\n", innerFindFilePath);
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
				printf("\n");
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
					printf("%s\n", WrongInfo[WIUncommitted]);
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