//1850059 计1班 杨志远

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

#define DefaultStringLength 256
#define MaxDepth 5
const char *Optional[] =
{
	"a",
	"d",
};
enum Settings
{
	ShowHided = 0,
	ShowNoFile = 1,
};

int usage(const char *procname)
{
	printf("Usage : %s \n", procname);
	printf("        %s 路径\n", procname);
	printf("        %s -a 路径\n", procname);
	printf("        %s -d 路径\n", procname);
	return 0;
}

int type_of_LNK(const char path[], int *endOfOutputInfo, char outputInfo[], int *dicCount, int *fileCount)
{
	struct stat buffer;
	char tempStr[DefaultStringLength] = "";
	stat(path, &buffer);
	int rslt = readlink(path, tempStr, DefaultStringLength - 1);
	if (rslt >= 0 && rslt < DefaultStringLength - 1)
	{
		tempStr[rslt] = '\0';
		if (S_ISLNK(buffer.st_mode))
			return type_of_LNK(tempStr, endOfOutputInfo, outputInfo, dicCount, fileCount);
		else
		{
			(*endOfOutputInfo) += sprintf(outputInfo + (*endOfOutputInfo), " -> %s", tempStr);
			if (S_ISDIR(buffer.st_mode))
				(*dicCount)++;
			else
				(*fileCount)++;
			return buffer.st_mode;
		}
	}
	return 0;
}

int tree(int depth, char path[], const int setting[], int *dicCount, int *fileCount)
{
	DIR            *dir;
	struct dirent  *node;
	//printf("path:%s\n", path);
	if ((dir = opendir(path)) == NULL)
	{
		//printf("Open %s Fail! Error info:%s！\n", path, strerror(errno));
		return -1;
	}
	//printf("\n");
	while ((node = readdir(dir)) != NULL)
	{
		if (strcmp(node->d_name, ".") != 0 && strcmp(node->d_name, "..") != 0)
		{
			char outputInfo[DefaultStringLength] = "";
			int printEnter = 0, endOfOutputInfo = 0;
			int isNotHided = (!(node->d_name[0] == '.' && !setting[ShowHided]));
			if (!(node->d_type == DT_DIR || node->d_type == DT_LNK) && isNotHided)
			{
				(*fileCount)++;
			}
			if (isNotHided)//编辑输出信息
			{
				if (depth >= 1)
					endOfOutputInfo += sprintf(outputInfo + endOfOutputInfo, "|");
				int i;
				for (i = 1; i < depth * 4; i++)
					endOfOutputInfo += sprintf(outputInfo + endOfOutputInfo, " ");
				endOfOutputInfo += sprintf(outputInfo + endOfOutputInfo, "|-- %s", node->d_name);
				printEnter = 1;
			}


			//struct stat buffer;
			//if (node->d_type == DT_LNK && isNotHided)//读取链接文件信息
			//{
			//	char tempStr[DefaultStringLength] = "", tempStr2[DefaultStringLength] = "";
			//	strcpy(tempStr, path);
			//	strcat(tempStr, "/");
			//	strcat(tempStr, node->d_name);
			//	
			//	stat(tempStr, &buffer);
			//	int rslt = readlink(tempStr, tempStr2, DefaultStringLength - 1);
			//	if (rslt >= 0 &&  rslt < DefaultStringLength - 1)
			//	{
			//		tempStr2[rslt] = '\0';
			//		endOfOutputInfo += sprintf(outputInfo + endOfOutputInfo, " -> %s", tempStr2);
			//		//endOfOutputInfo += sprintf(outputInfo + endOfOutputInfo, " %x ", buffer.st_mode);
			//		if (S_ISDIR(buffer.st_mode))
			//			(*dicCount)++;
			//		else
			//			(*fileCount)++;
			//		printEnter = 1;
			//	}
			//}

			int linkFileType = 0;
			if (node->d_type == DT_LNK && isNotHided)//读取链接文件信息
			{
				char tempStr[DefaultStringLength] = "";
				strcpy(tempStr, path);
				strcat(tempStr, "/");
				strcat(tempStr, node->d_name);
				linkFileType = type_of_LNK(tempStr, &endOfOutputInfo, outputInfo, dicCount, fileCount);
				if (linkFileType > 0)
					printEnter = 1;
			}

			//endOfOutputInfo += sprintf(outputInfo + endOfOutputInfo, " file:%s type:%x", node->d_name, node->d_type);
			if (printEnter)//添加回车
				endOfOutputInfo += sprintf(outputInfo + endOfOutputInfo, "\n");
			//if (isNotHided && !(setting[ShowNoFile] && !(node->d_type == DT_DIR || (node->d_type == DT_LNK && S_ISDIR(buffer.st_mode)))))//输出信息
			//	printf("%s", outputInfo);
			if (isNotHided && !(setting[ShowNoFile] && !(node->d_type == DT_DIR || (node->d_type == DT_LNK && S_ISDIR(linkFileType)))))//输出信息
				printf("%s", outputInfo);
			if ((node->d_type == DT_DIR || node->d_type == DT_UNKNOWN) && isNotHided)//递归遍历子目录
			//if ((node->d_type != DT_REG && node->d_type != DT_LNK) && isNotHided)//递归遍历子目录
			{
				int len = strlen(path);
				strcat(path, node->d_name);
				strcat(path, "/");
				if (node->d_type == DT_DIR)
					(*dicCount)++;
				tree(depth + 1, path, setting, dicCount, fileCount);
				//printf("path:%s type:%d return:%d\n", path, node->d_type, tree(depth + 1, path, setting, dicCount, fileCount));
				//path[strrchr(path, '/') - path] = '\0';
				path[len] = '\0';
			}
		}
	}
	//printf("closedir\n");
	closedir(dir);
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc > 4)
	{
		usage(strrchr(argv[0], '/') + 1);
		return 1;
	}
	int setting[sizeof(Optional) / sizeof(Optional[0])] = { 0 };
	int pathInput = 0;
	char path[DefaultStringLength] = "";
	if (argc != 1)
	{
		int k, i, count = 0;
		for (k = 1; k <= argc - 1; k++)
		{
			if (argv[k][0] == '-')
			{
				for (i = 0; i < sizeof(Optional) / sizeof(Optional[0]); i++)
					if (strcmp(&argv[k][1], Optional[i]) == 0)
					{
						setting[i] = 1;
						count++;
					}
			}
			else
			{
				strcpy(path, argv[k]);
				strcat(path, "/");
				pathInput = 1;
			}
		}
		if (count + pathInput + 1 != argc)
		{
			usage(strrchr(argv[0], '/') + 1);
			return 2;
		}
	}
	if (!pathInput)
	{
		strcpy(path, "./");
	}
	int dicCount = 0, fileCount = 0;
	printf("%s\n", path);
	tree(0, path, setting, &dicCount, &fileCount);
	printf("\n%d directories", dicCount);
	if (!setting[ShowNoFile])
		printf(", %d files", fileCount);
	printf("\n");
	return 0;
}