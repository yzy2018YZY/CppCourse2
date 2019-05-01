#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;

int main(int argc, char *argv[])
{
	char fileName1[100] = "7-b28-1.exe -linecount 100384 all";
	char fileName2[100] = "7-b28-demo.exe -linecount 100384 all";
	char instruction[100] = "";
	/*
	if(argc == 3)
	{
		strcpy(fileName1, argv[1]);
		strcpy(fileName2, argv[2]);
	}
	else
	{
		cout << "请输入文件名7-b16 7-b21" << endl;
		cin >> fileName1;
		cout << "请输入文件名7-b17 7-b22" << endl;
		cin >> fileName2;
	}*/
	
	
	
	strcpy(instruction, fileName1);
	strcat(instruction, " > b.txt");
	cout << system(instruction) << endl;
	
	strcpy(instruction, fileName2);
	strcat(instruction, " > a.txt");
	cout << system(instruction) << endl;
	
	
	
	cout << system("comp a.txt b.txt < no.txt") << endl;
	
	system("pause");
}
