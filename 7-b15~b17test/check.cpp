#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;

int main(int argc, char *argv[])
{
	char fileName1[100] = "";
	char fileName2[100] = "";
	char instruction[100] = "";
	
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
	}
	
	strcpy(instruction, fileName1);
	strcat(instruction, " in1.txt > hex_in1.txt");
	cout << "1:" << system(instruction) << endl;
	
	strcpy(instruction, fileName1);
	strcat(instruction, " in2.txt > hex_in2.txt");
	cout << "2:" << system(instruction) << endl;
	
	strcpy(instruction, fileName1);
	strcat(instruction, " in3.txt > hex_in3.txt");
	cout << "3:" << system(instruction) << endl;
	
	strcpy(instruction, fileName1);
	strcat(instruction, " in4.txt > hex_in4.txt");
	cout << "4:" << system(instruction) << endl;
	
	strcpy(instruction, fileName1);
	strcat(instruction, " inp.txt > hex_inp.txt");
	cout << "p:" << system(instruction) << endl;
	
	strcpy(instruction, fileName1);
	strcat(instruction, " inword.txt > hex_inword.txt");
	cout << "w:" << system(instruction) << endl;
	
	
	strcpy(instruction, fileName2);
	strcat(instruction, " hex_in1.txt hex_out1.txt");
	cout << "1:" << system(instruction) << endl;
	
	strcpy(instruction, fileName2);
	strcat(instruction, " hex_in2.txt hex_out2.txt");
	cout << "2:" << system(instruction) << endl;
	
	strcpy(instruction, fileName2);
	strcat(instruction, " hex_in3.txt hex_out3.txt");
	cout << "3:" << system(instruction) << endl;
	
	strcpy(instruction, fileName2);
	strcat(instruction, " hex_in4.txt hex_out4.txt");
	cout << "4:" << system(instruction) << endl;
	
	strcpy(instruction, fileName2);
	strcat(instruction, " hex_inp.txt hex_outp.txt");
	cout << "p:" << system(instruction) << endl;
	
	strcpy(instruction, fileName2);
	strcat(instruction, " hex_inword.txt hex_outword.txt");
	cout << "w:" << system(instruction) << endl;
	
	
	
	cout << system("comp in1.txt hex_out1.txt < input.txt") << endl;
	cout << system("comp in2.txt hex_out2.txt < input.txt") << endl;
	cout << system("comp in3.txt hex_out3.txt < input.txt") << endl;
	cout << system("comp in4.txt hex_out4.txt < input.txt") << endl;
	cout << system("comp inp.txt hex_outp.txt < input.txt") << endl;
	cout << system("comp inword.txt hex_outword.txt < input.txt") << endl;
	
	system("pause");
}
