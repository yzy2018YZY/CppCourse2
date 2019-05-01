/*7772232 ���ݿ�ѧ������ݼ��� ÷���� 7772256 ���� */

#include <iostream>
using namespace std;

/* ������ԭ�Ͷ��岻׼�� */
int   tj_strlen(const char *str);
char *tj_strcat(char *s1, const char *s2);
char *tj_strcpy(char *s1, const char *s2);
char *tj_strncpy(char *s1, const char *s2, const int len);
int   tj_strcmp(const char *s1, const char *s2);
int   tj_strcasecmp(const char *s1, const char *s2);
int   tj_strncmp(const char *s1, const char *s2, const int len);
int   tj_strcasencmp(const char *s1, const char *s2, const int len);
char *tj_strupr(char *str);
char *tj_strlwr(char *str);
int   tj_strchr(const char *str, const char ch);
int   tj_strstr(const char *str, const char *substr);
int   tj_strrchr(const char *str, const char ch);
int   tj_strrstr(const char *str, const char *substr);
char *tj_strrev(char *str);


/* ----- �����������κ���ʽ��ȫ������!!!!! ----- */

/* ����ʵ�ֲ��֣�{ }�ڵĶ����������������Ŀǰ��returnֻ��һ��ʾ�����ɸı� */
int tj_strlen(const char *str)
{
    /* ע�⣺�����ڲ����������κ���ʽ�����飨������̬���飩 */
	int num=0;
	if (str==0)
		return num;
	for (;*str!=0;str++)
		num++;
    return num;
}

char *tj_strcat(char *s1, const char *s2)
{
    /* ע�⣺�����ڲ����������κ���ʽ�����飨������̬���飩 */
	char *head=s1;
	if (s1==0)
		return 0;

	if (s2==0)
		return s1;
	
	for (;*s1!=0;s1++)
		;

	for (;*s2!=0;s1++,s2++)
		*s1=*s2;

	*s1=0;
	
	s1=head;
    return s1;
}

char *tj_strcpy(char *s1, const char *s2)
{
    /* ע�⣺�����ڲ����������κ���ʽ�����飨������̬���飩 */
	char *head=s1;
	if (s1==0)
		return 0;

	if (s2==0){
		*s1=0;
		return s1;
		}

	for (;*s2!=0;s1++,s2++)
		*s1=*s2;

	*s1=0;
	
	s1=head;
    return s1;
}

char *tj_strncpy(char *s1, const char *s2, const int len)
{
	char *head=s1;
	int n=0;
	if (s1==0)
		return 0;

	if (s2==0){
		return s1;
		}

	for (;*s2!=0;s1++,s2++){
		*s1=*s2;
		n++;
		if (n==len)
			break;
		}
	
	s1=head;
    return s1;
}

int tj_strcmp(const char *s1, const char *s2)
{
    /* ע�⣺�����ڲ����������κ���ʽ�����飨������̬���飩 */
	int ASC1=0,ASC2=0,flag=0;

	if (s1==0 && s2==0)
		return 0;
	if (s1==0)
		return -1;
	if (s2==0)
		return 1;

	for (;*s1!=0 || *s2!=0;s1++,s2++){
		if (*s1!=*s2)
			return (*s1-*s2);
		else if (*s1==0 && *s2!=0)
			return *s2;
		else if (*s1!=0 && *s2==0)
			return *s1;
		else 
			continue;
		}

	return 0;

}

int tj_strcasecmp(const char *s1, const char *s2)
{
    /* ע�⣺�����ڲ����������κ���ʽ�����飨������̬���飩 */
	int ASC1=0,ASC2=0,flag=0;

	if (s1==0 && s2==0)
		return 0;
	if (s1==0)
		return -1;
	if (s2==0)
		return 1;

	for (;*s1!=0 || *s2!=0;s1++,s2++){
		if (*s1!=*s2){
			if (*s1==*s2+32 || *s1==*s2-32)
				continue;
			else 
				return (*s1-*s2);
			}
		else if (*s1==0 && *s2!=0)
			return *s2;
		else if (*s1!=0 && *s2==0)
			return *s1;
		else 
			continue;
		}

	return 0;
}

int tj_strncmp(const char *s1, const char *s2, const int len)
{
    /* ע�⣺�����ڲ����������κ���ʽ�����飨������̬���飩 */
	int ASC1=0,ASC2=0,flag=0,n=0;

	if (s1==0 && s2==0)
		return 0;
	if (s1==0)
		return -1;
	if (s2==0)
		return 1;

	for (;*s1!=0 || *s2!=0;s1++,s2++){
		if (*s1!=*s2)
			return (*s1-*s2);
		if (*s1==0 && *s2!=0)
			return *s2;
		if (*s1!=0 && *s2==0)
			return *s1;
		n++;
		if (n==len)
			break;
		}

	return flag;

    return 0;
}

int tj_strcasencmp(const char *s1, const char *s2, const int len)
{
    /* ע�⣺�����ڲ����������κ���ʽ�����飨������̬���飩 */
	int ASC1=0,ASC2=0,flag=0,n=0;

	if (s1==0 && s2==0)
		return 0;
	if (s1==0)
		return -1;
	if (s2==0)
		return 1;

	for (;*s1!=0 || *s2!=0;s1++,s2++){
		if (*s1!=*s2){
			if (*s1==*s2+32 || *s1==*s2-32)
				flag=0;
			else 
				return (*s1-*s2);
			}
		if (*s1==0 && *s2!=0)
			return *s2;
		if (*s1!=0 && *s2==0)
			return *s1;
		n++;
		if (n==len)
			break;
		}

	return flag;
}

char *tj_strupr(char *str)
{
    /* ע�⣺�����ڲ����������κ���ʽ�����飨������̬���飩 */
	char *head=str;
	if (str==0)
		return 0;

	for (;*str!=0;str++){
		if (*str>='a' && *str<='z')
			*str=*str-32;
		}

	return head;
}

char *tj_strlwr(char *str)
{
    /* ע�⣺�����ڲ����������κ���ʽ�����飨������̬���飩 */
	char *head=str;
	if (str==0)
		return 0;

	for (;*str!=0;str++){
		if (*str>='A' && *str<='Z')
			*str=*str+32;
		}

	return head;
}

int tj_strchr(const char *str, const char ch)
{
    /* ע�⣺�����ڲ����������κ���ʽ�����飨������̬���飩 */
	int n=0;
	if (str==0)
		return 0;

	for (;*str!=0;str++){
		n++;
		if (*str==ch)
			return n;
		}
	return 0;
}

int tj_strstr(const char *str, const char *substr)
{
    /* ע�⣺�����ڲ����������κ���ʽ�����飨������̬���飩 */
	int n=0,len=0;
	if (str==0 || substr==0)
		return 0;
	
	len=tj_strlen(substr);

	for (;*str!=0;str++){
		n++;
		if (*str==*substr){
			if (tj_strncmp(str,substr,len)==0)
				return n;
			}
		}
    return 0;
}

int tj_strrchr(const char *str, const char ch)
{
    /* ע�⣺�����ڲ����������κ���ʽ�����飨������̬���飩 */
	int len;
	if (str==0)
		return 0;

	len=tj_strlen(str);
	str=str+len-1;

	for (;len>0;str--,len--){
		if (*str==ch)
			return len;
		}
    return 0;
}

int tj_strrstr(const char *str, const char *substr)
{
    /* ע�⣺�����ڲ����������κ���ʽ�����飨������̬���飩 */
	int len1=0,len2=0;
	if (str==0 || substr==0)
		return 0;
	
	len1=tj_strlen(str);
	len2=tj_strlen(substr);

	str=str+len1-1;

	for (;len1>0;str--,len1--){
		if (*str==*substr){
			if (tj_strncmp(str,substr,len2)==0)
				return len1;
			}
		}

    return 0;
}

char *tj_strrev(char *str)
{
    /* ע�⣺�����ڲ����������κ���ʽ�����飨������̬���飩 */
	char temp;
	char *head=str,*last;
	int len=0,n=1;

	if (str==0)
		return 0;

	len=strlen(str);
	last=str+len-1;

	for (;n<=(len/2);head++,last--,n++){
		temp=*head;
		*head=*last;
		*last=temp;
		}

    return str;
}
/* ==The End==(����ʵ�ֲ���) */

void press_key(char *prompt="")
{
    cout << endl << prompt << "�����س�������" << endl;
    getchar();
    cin.clear();
    cin.sync();
}

/* main����(ϸ�ڿ����д��������֣��뼰ʱ��ӳ) */
int main()
{
    if (1) {
        char  s1[]="abcdefghijklmnopqrstuvwxyz";
        char  s2[]="abcdefghijklmnopqrstuvwxyz\0UVWXYZ";
        char  s3[]="";
        char *p4 =NULL;

        cout << "tj_strlen()���Բ��֣�" << endl;
        cout << "1.s1      �ĳ���Ӧ����26��ʵ���ǣ�" << tj_strlen(s1)      << endl;
        cout << "2.s2      �ĳ���Ӧ����26��ʵ���ǣ�" << tj_strlen(s2)      << endl;
        cout << "3.&s2[27] �ĳ���Ӧ����6�� ʵ���ǣ�" << tj_strlen(&s2[27]) << endl;
        cout << "4.s3      �ĳ���Ӧ����0�� ʵ���ǣ�" << tj_strlen(s3)      << endl;
        cout << "5.p4      �ĳ�����Ϊ��0�� ʵ���ǣ�" << tj_strlen(p4)      << endl;

        press_key("tj_strlen() �������");
        }

    if (1) {
        char  s1[80]="abcdefghij";
        char  s2[]="abcde";
        char  s3[]="hello\0UVWXYZ";
        char  s4[]="";
        char *p5=NULL;

        cout << "tj_strcat()���Բ��֣�" << endl;
        cout << "1.s1�����Ӧ����abcdefghij��                ʵ���ǣ�" << s1 << endl;
        cout << "  s1�ĳ���Ӧ����10��                        ʵ���ǣ�" << tj_strlen(s1) << endl;

        cout << "2.s1�����Ӧ����abcdefghijabcde��           ʵ���ǣ�" << tj_strcat(s1, s2) << endl;
        cout << "  s1�ĳ���Ӧ����15��                        ʵ���ǣ�" << tj_strlen(s1)     << endl;

        cout << "3.s1�����Ӧ����abcdefghijabcdehello��      ʵ���ǣ�" << tj_strcat(s1, s3) << endl;
        cout << "  s1�ĳ���Ӧ����20��                        ʵ���ǣ�" << tj_strlen(s1)     << endl;

        cout << "4.s1�����Ӧ����abcdefghijabcdehelloUVWXYZ��ʵ���ǣ�" << tj_strcat(s1, &s3[6]) << endl;
        cout << "  s1�ĳ���Ӧ����26��                        ʵ���ǣ�" << tj_strlen(s1)         << endl;

        cout << "5.s1�����Ӧ����abcdefghijabcdehelloUVWXYZ��ʵ���ǣ�" << tj_strcat(s1, s4) << endl;
        cout << "  s1�ĳ���Ӧ����26��                        ʵ���ǣ�" << tj_strlen(s1)     << endl;

        cout << "6.s1�����Ӧ����abcdefghijabcdehelloUVWXYZ��ʵ���ǣ�" << tj_strcat(s1, p5) << endl;
        cout << "  s1�ĳ���Ӧ����26��                        ʵ���ǣ�" << tj_strlen(s1)     << endl;

        cout << "7.p5�����Ӧ����<NULL>��                    ʵ���ǣ�" << (tj_strcat(p5, s1)==NULL ? "<NULL>":tj_strcat(p5, s1)) << endl;
        cout << "  p5�ĳ���Ӧ����0��                         ʵ���ǣ�" << tj_strlen(p5)     << endl;

        cout << "8.p5�����Ӧ����<NULL>��                    ʵ���ǣ�" << (tj_strcat(p5, NULL)==NULL ? "<NULL>":tj_strcat(p5, NULL)) << endl;
        cout << "  p5�ĳ���Ӧ����0��                         ʵ���ǣ�" << tj_strlen(p5)     << endl;

        press_key("tj_strcat() �������");
        }

    if (1) {
        char  s0[80];
        char  s1[80]="abcdefghijklm";
        char  s2[]="abcde";
        char  s3[]="hello\0UVWXYZ";
        char  s4[]="";
        char *p5=NULL;
        char *p6=NULL;

        cout << "tj_strcpy()���Բ��֣�" << endl;
        cout << "1.s1�����Ӧ����abcdefghijklm��   ʵ���ǣ�" << s1            << endl;
        cout << "  s1�ĳ���Ӧ����13��              ʵ���ǣ�" << tj_strlen(s1) << endl;

        cout << "2.s1�����Ӧ����abcde��           ʵ���ǣ�" << tj_strcpy(s1, s2) << endl;
        cout << "  s1�ĳ���Ӧ����5��               ʵ���ǣ�" << tj_strlen(s1)     << endl;

        cout << "3.s1�����Ӧ����UVWXYZ��          ʵ���ǣ�" << tj_strcpy(s1, &s3[6]) << endl;
        cout << "  s1�ĳ���Ӧ����6��               ʵ���ǣ�" << tj_strlen(s1)         << endl;

        cout << "4.s1�����Ӧ����hello��           ʵ���ǣ�" << tj_strcpy(s1, s3) << endl;
        cout << "  s1�ĳ���Ӧ����5��               ʵ���ǣ�" << tj_strlen(s1)     << endl;

        cout << "5.s1�����Ӧ����--��              ʵ���ǣ�-" << tj_strcpy(s1, s4) << '-' << endl;
        cout << "  s1�ĳ���Ӧ����0��               ʵ���ǣ�"  << tj_strlen(s1)     << endl;

        tj_strcpy(s0, s2);
        tj_strcat(s0, s3);
        cout << "6.s0�����Ӧ����abcdehelloUVWXYZ��ʵ���ǣ�" << tj_strcat(s0, &s3[6]) << endl;
        cout << "  s0�ĳ���Ӧ����16��              ʵ���ǣ�" << tj_strlen(s0)         << endl;

        cout << "7.s0�����Ӧ����--��              ʵ���ǣ�-" << tj_strcpy(s0, p5) << '-' << endl;
        cout << "  s0�ĳ���Ӧ����0��               ʵ���ǣ�"  << tj_strlen(s0)     << endl;

        cout << "8.p5�����Ӧ����<NULL>��          ʵ���ǣ�"  << (tj_strcpy(p5, s0)==NULL ? "<NULL>" : tj_strcpy(p5, s0)) << endl;
        cout << "  p5�ĳ���Ӧ����0��               ʵ���ǣ�"  << tj_strlen(p5)     << endl;

        cout << "9.p5�����Ӧ����<NULL>��          ʵ���ǣ�"  << (tj_strcpy(p5, p6)==NULL ? "<NULL>" : tj_strcpy(p5, p6)) << endl;
        cout << "  p5�ĳ���Ӧ����0��               ʵ���ǣ�"  << tj_strlen(p5)     << endl;

        press_key("tj_strcpy() �������");
        }

    if (1) {
        char  s0[80];
        char  s1[80]="abcdefghijklm";
        char  s2[]="abcde";
        char  s3[]="hello\0UVWXYZ";
        char  s4[]="";
        char *p5=NULL;
        char *p6=NULL;

        cout << "tj_strncpy()���Բ��֣�" << endl;
        cout << "1. s1�����Ӧ����abcdefghijklm��   ʵ���ǣ�" << s1            << endl;
        cout << "   s1�ĳ���Ӧ����13��              ʵ���ǣ�" << tj_strlen(s1) << endl;

        cout << "2. s1�����Ӧ����hellofghijklm��   ʵ���ǣ�" << tj_strncpy(s1, s3, 10) << endl;
        cout << "   s1�ĳ���Ӧ����13��              ʵ���ǣ�" << tj_strlen(s1)          << endl;

        tj_strcpy(s1, "abcdefghijklm");
        cout << "3. s1�����Ӧ����hellofghijklm��   ʵ���ǣ�" << tj_strncpy(s1, s3, 5) << endl;
        cout << "   s1�ĳ���Ӧ����13��              ʵ���ǣ�" << tj_strlen(s1)         << endl;

        tj_strcpy(s1, "abcdefghijklm");
        cout << "4. s1�����Ӧ����heldefghijklm��   ʵ���ǣ�" << tj_strncpy(s1, s3, 3) << endl;
        cout << "   s1�ĳ���Ӧ����13��              ʵ���ǣ�" << tj_strlen(s1)         << endl;

        tj_strcpy(s1, "abcdefghijklm");
        cout << "5. s1�����Ӧ����abcdefghijklm��   ʵ���ǣ�" << tj_strncpy(s1, s4, 2) << endl;
        cout << "   s1�ĳ���Ӧ����13��              ʵ���ǣ�" << tj_strlen(s1)         << endl;

        tj_strcpy(s1, "abcdefghijklm");
        tj_strncpy(&s1[4], s3, 10);
        cout << "6. s1�����Ӧ����abcdhellojklm��   ʵ���ǣ�" << s1            << endl;
        cout << "   s1�ĳ���Ӧ����13��              ʵ���ǣ�" << tj_strlen(s1) << endl;

        tj_strcpy(s1, "abcdefghijklm");
        tj_strncpy(&s1[4], s3, 5);
        cout << "7. s1�����Ӧ����abcdhellojklm��   ʵ���ǣ�" << s1            << endl;
        cout << "   s1�ĳ���Ӧ����13��              ʵ���ǣ�" << tj_strlen(s1) << endl;

        tj_strcpy(s1, "abcdefghijklm");
        tj_strncpy(&s1[4], s3, 3);
        cout << "8. s1�����Ӧ����abcdhelhijklm��   ʵ���ǣ�" << s1            << endl;
        cout << "   s1�ĳ���Ӧ����13��              ʵ���ǣ�" << tj_strlen(s1) << endl;

        tj_strcpy(s1, "abcdefghijklm");
        tj_strncpy(&s1[4], &s3[6], 10);
        cout << "9. s1�����Ӧ����abcdUVWXYZklm��   ʵ���ǣ�" << s1            << endl;
        cout << "   s1�ĳ���Ӧ����13��              ʵ���ǣ�" << tj_strlen(s1) << endl;

        press_key("tj_strncpy() ������ͣ");

        tj_strcpy(s1, "abcdefghijklm");
        tj_strncpy(&s1[4], &s3[6], 6);
        cout << "10.s1�����Ӧ����abcdUVWXYZklm��   ʵ���ǣ�" << s1            << endl;
        cout << "   s1�ĳ���Ӧ����13��              ʵ���ǣ�" << tj_strlen(s1) << endl;

        tj_strcpy(s1, "abcdefghijklm");
        tj_strncpy(&s1[4], &s3[6], 3);
        cout << "11.s1�����Ӧ����abcdUVWhijklm��   ʵ���ǣ�" << s1            << endl;
        cout << "   s1�ĳ���Ӧ����13��              ʵ���ǣ�" << tj_strlen(s1) << endl;

        tj_strncpy(s0, s2, tj_strlen(s2));
        s0[tj_strlen(s2)] = 0;
        cout << "12.s0�����Ӧ����abcde��           ʵ���ǣ�" << s0            << endl;
        cout << "   s0�ĳ���Ӧ����5��               ʵ���ǣ�" << tj_strlen(s0) << endl;

        cout << "13.s0�����Ӧ����abcdehello��      ʵ���ǣ�" << tj_strcat(s0, s3) << endl;
        cout << "   s0�ĳ���Ӧ����10��              ʵ���ǣ�" << tj_strlen(s0)     << endl;
        
        int old_len = tj_strlen(s0);
        tj_strncpy(&s0[10], &s3[6], tj_strlen(&s3[6]));
        s0[old_len + tj_strlen(&s3[6]) ] = 0;
        cout << "14.s0�����Ӧ����abcdehelloUVWXYZ��ʵ���ǣ�" << s0            << endl;
        cout << "   s0�ĳ���Ӧ����16��              ʵ���ǣ�" << tj_strlen(s0) << endl;

        cout << "15.s0�����Ӧ����abcdehelloUVWXYZ��ʵ���ǣ�"  << tj_strncpy(s0, p5, 2) << endl;
        cout << "   s0�ĳ���Ӧ����16��              ʵ���ǣ�"  << tj_strlen(s0)     << endl;

        cout << "16.p5�����Ӧ����<NULL>��          ʵ���ǣ�"  << (tj_strncpy(p5, s0, 2)==NULL ? "<NULL>" : tj_strncpy(p5, s0, 2)) << endl;
        cout << "   p5�ĳ���Ӧ����0��               ʵ���ǣ�"  << tj_strlen(p5)     << endl;

        cout << "17.p5�����Ӧ����<NULL>��          ʵ���ǣ�"  << (tj_strncpy(p5, p6, 2)==NULL ? "<NULL>" : tj_strncpy(p5, p6, 2)) << endl;
        cout << "   p5�ĳ���Ӧ����0��               ʵ���ǣ�"  << tj_strlen(p5)     << endl;

        press_key("tj_strncpy() �������");
        }

    if (1) {
        char  s1[]="horse";
        char  s2[]="house";
        char  s3[]="hell";
        char  s4[]="hello";
        char  s5[]="hello";
        char  s6[]="hell";
        char  s7[]="hello";
        char  s8[]="hello";
        char  s9[]="hello";
        char  s10[]="hello\0UVWXYZ";
        char  s11[]="HELLO";
        char  s12[]="hello";
        char  s13[]="HeLlO";
        char  s14[]="hElLo";
        char *p15 = NULL;
        char *p16 = NULL;

        cout << "tj_strcmp()���Բ��֣�" << endl;
        cout << "1.s1 ��s2 �����Ӧ����-3��  ʵ���ǣ�" << tj_strcmp(s1,  s2)  << endl;
        cout << "2.s3 ��s4 �����Ӧ����-111��ʵ���ǣ�" << tj_strcmp(s3,  s4)  << endl;
        cout << "3.s5 ��s6 �����Ӧ����111�� ʵ���ǣ�" << tj_strcmp(s5,  s6)  << endl;
        cout << "4.s7 ��s8 �����Ӧ����0��   ʵ���ǣ�" << tj_strcmp(s7,  s8)  << endl;
        cout << "5.s9 ��s10�����Ӧ����0��   ʵ���ǣ�" << tj_strcmp(s9,  s10) << endl;
        cout << "6.s11��s12�����Ӧ����-32�� ʵ���ǣ�" << tj_strcmp(s11, s12) << endl;
        cout << "7.s13��s14�����Ӧ����-32�� ʵ���ǣ�" << tj_strcmp(s13, s14) << endl;
        cout << "8.p15��s1 �����Ӧ����-1��  ʵ���ǣ�" << tj_strcmp(p15, s1)  << endl;
        cout << "  s1 ��p15�����Ӧ����1��   ʵ���ǣ�" << tj_strcmp(s1,  p15) << endl;
        cout << "  p15��p16�����Ӧ����0��   ʵ���ǣ�" << tj_strcmp(p15, p16) << endl;

        press_key("tj_strcmp() �������");
        }

    if (1) {
        char  s1[]="horse";
        char  s2[]="house";
        char  s3[]="hell";
        char  s4[]="hello";
        char  s5[]="hello";
        char  s6[]="hell";
        char  s7[]="hello";
        char  s8[]="hello";
        char  s9[]="hello";
        char  s10[]="hello\0UVWXYZ";
        char  s11[]="HELLO";
        char  s12[]="hello";
        char  s13[]="HeLlO";
        char  s14[]="hElLo";
        char *p15 = NULL;
        char *p16 = NULL;

        cout << "tj_strcasecmp()���Բ��֣�" << endl;
        cout << "1.s1 ��s2 �����Ӧ����-3��  ʵ���ǣ�" << tj_strcasecmp(s1,  s2)  << endl;
        cout << "2.s3 ��s4 �����Ӧ����-111��ʵ���ǣ�" << tj_strcasecmp(s3,  s4)  << endl;
        cout << "3.s5 ��s6 �����Ӧ����111�� ʵ���ǣ�" << tj_strcasecmp(s5,  s6)  << endl;
        cout << "4.s7 ��s8 �����Ӧ����0��   ʵ���ǣ�" << tj_strcasecmp(s7,  s8)  << endl;
        cout << "5.s9 ��s10�����Ӧ����0��   ʵ���ǣ�" << tj_strcasecmp(s9,  s10) << endl;
        cout << "6.s11��s12�����Ӧ����0��   ʵ���ǣ�" << tj_strcasecmp(s11, s12) << endl;
        cout << "7.s13��s14�����Ӧ����0��   ʵ���ǣ�" << tj_strcasecmp(s13, s14) << endl;
        cout << "8.p15��s1 �����Ӧ����-1��  ʵ���ǣ�" << tj_strcasecmp(p15, s1)  << endl;
        cout << "  s1 ��p15�����Ӧ����1��   ʵ���ǣ�" << tj_strcasecmp(s1,  p15) << endl;
        cout << "  p15��p16�����Ӧ����0��   ʵ���ǣ�" << tj_strcasecmp(p15, p16) << endl;

        press_key("tj_strcasecmp() �������");
        }

    if (1) {
        char  s1[]="horse";
        char  s2[]="house";
        char  s3[]="hell";
        char  s4[]="hello";
        char  s5[]="hello";
        char  s6[]="hell";
        char  s7[]="hello";
        char  s8[]="hello";
        char  s9[]="hello";
        char  s10[]="hello\0UVWXYZ";
        char  s11[]="HELLO";
        char  s12[]="hello";
        char  s13[]="HeLlO";
        char  s14[]="hElLo";
        char *p15 = NULL;
        char *p16 = NULL;

        cout << "tj_strncmp()���Բ��֣�" << endl;
        cout << "1.s1 ��s2 �Ƚ�ǰ10���ַ������Ӧ����-3��  ʵ���ǣ�" << tj_strncmp(s1,  s2,  10) << endl;
        cout << "  s1 ��s2 �Ƚ�ǰ5 ���ַ������Ӧ����-3��  ʵ���ǣ�" << tj_strncmp(s1,  s2,  5)  << endl;
        cout << "  s1 ��s2 �Ƚ�ǰ3 ���ַ������Ӧ����-3��  ʵ���ǣ�" << tj_strncmp(s1,  s2,  3)  << endl;
        cout << "  s1 ��s2 �Ƚ�ǰ2 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strncmp(s1,  s2,  2)  << endl;
        cout << "2.s3 ��s4 �Ƚ�ǰ10���ַ������Ӧ����-111��ʵ���ǣ�" << tj_strncmp(s3,  s4,  10) << endl;
        cout << "  s3 ��s4 �Ƚ�ǰ5 ���ַ������Ӧ����-111��ʵ���ǣ�" << tj_strncmp(s3,  s4,  5)  << endl;
        cout << "  s3 ��s4 �Ƚ�ǰ4 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strncmp(s3,  s4,  4)  << endl;
        cout << "3.s5 ��s6 �Ƚ�ǰ10���ַ������Ӧ����111 ��ʵ���ǣ�" << tj_strncmp(s5,  s6,  10) << endl;
        cout << "  s5 ��s6 �Ƚ�ǰ5 ���ַ������Ӧ����111�� ʵ���ǣ�" << tj_strncmp(s5,  s6,  5)  << endl;
        cout << "  s5 ��s6 �Ƚ�ǰ4 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strncmp(s5,  s6,  4)  << endl;
        cout << "4.s7 ��s8 �Ƚ�ǰ10���ַ������Ӧ����0 ��  ʵ���ǣ�" << tj_strncmp(s7,  s8,  10) << endl;
        cout << "  s7 ��s8 �Ƚ�ǰ5 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strncmp(s7,  s8,  5)  << endl;
        cout << "  s7 ��s8 �Ƚ�ǰ4 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strncmp(s7,  s8,  4)  << endl;
        cout << "5.s9 ��s10�Ƚ�ǰ10���ַ������Ӧ����0 ��  ʵ���ǣ�" << tj_strncmp(s9,  s10, 10) << endl;
        cout << "  s9 ��s10�Ƚ�ǰ5 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strncmp(s9,  s10, 5)  << endl;
        cout << "  s9 ��s10�Ƚ�ǰ4 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strncmp(s9,  s10, 4)  << endl;
        press_key("tj_strncmp() ������ͣ");

        cout << "6.s11��s12�Ƚ�ǰ10���ַ������Ӧ����-32�� ʵ���ǣ�" << tj_strncmp(s11, s12, 10) << endl;
        cout << "  s11��s12�Ƚ�ǰ5 ���ַ������Ӧ����-32�� ʵ���ǣ�" << tj_strncmp(s11, s12, 5)  << endl;
        cout << "  s11��s12�Ƚ�ǰ2 ���ַ������Ӧ����-32�� ʵ���ǣ�" << tj_strncmp(s11, s12, 2)  << endl;
        cout << "7.s13��s14�Ƚ�ǰ10���ַ������Ӧ����-32�� ʵ���ǣ�" << tj_strncmp(s13, s14, 10) << endl;
        cout << "  s13��s14�Ƚ�ǰ5 ���ַ������Ӧ����-32�� ʵ���ǣ�" << tj_strncmp(s13, s14, 5)  << endl;
        cout << "  s13��s14�Ƚ�ǰ2 ���ַ������Ӧ����-32�� ʵ���ǣ�" << tj_strncmp(s13, s14, 2)  << endl;
        cout << "8.p15��s1 �Ƚ�ǰ2 ���ַ������Ӧ����-1��  ʵ���ǣ�" << tj_strncmp(p15, s1,  2) << endl;
        cout << "  s1 ��p15�Ƚ�ǰ2 ���ַ������Ӧ����1��   ʵ���ǣ�" << tj_strncmp(s1,  p15, 5)  << endl;
        cout << "  p15��p16�Ƚ�ǰ2 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strncmp(p15, p16, 2)  << endl;

        press_key("tj_strncmp() ���Խ���");
        }

    if (1) {
        char  s1[]="horse";
        char  s2[]="house";
        char  s3[]="hell";
        char  s4[]="hello";
        char  s5[]="hello";
        char  s6[]="hell";
        char  s7[]="hello";
        char  s8[]="hello";
        char  s9[]="hello";
        char  s10[]="hello\0UVWXYZ";
        char  s11[]="HELLO";
        char  s12[]="hello";
        char  s13[]="HeLlO";
        char  s14[]="hElLo";
        char *p15 = NULL;
        char *p16 = NULL;

        cout << "tj_strcasencmp()���Բ��֣�" << endl;
        cout << "1.s1 ��s2 �Ƚ�ǰ10���ַ������Ӧ����-3��  ʵ���ǣ�" << tj_strcasencmp(s1,  s2,  10) << endl;
        cout << "  s1 ��s2 �Ƚ�ǰ5 ���ַ������Ӧ����-3��  ʵ���ǣ�" << tj_strcasencmp(s1,  s2,  5)  << endl;
        cout << "  s1 ��s2 �Ƚ�ǰ3 ���ַ������Ӧ����-3��  ʵ���ǣ�" << tj_strcasencmp(s1,  s2,  3)  << endl;
        cout << "  s1 ��s2 �Ƚ�ǰ2 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strcasencmp(s1,  s2,  2)  << endl;
        cout << "2.s3 ��s4 �Ƚ�ǰ10���ַ������Ӧ����-111��ʵ���ǣ�" << tj_strcasencmp(s3,  s4,  10) << endl;
        cout << "  s3 ��s4 �Ƚ�ǰ5 ���ַ������Ӧ����-111��ʵ���ǣ�" << tj_strcasencmp(s3,  s4,  5)  << endl;
        cout << "  s3 ��s4 �Ƚ�ǰ4 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strcasencmp(s3,  s4,  4)  << endl;
        cout << "3.s5 ��s6 �Ƚ�ǰ10���ַ������Ӧ����111 ��ʵ���ǣ�" << tj_strcasencmp(s5,  s6,  10) << endl;
        cout << "  s5 ��s6 �Ƚ�ǰ5 ���ַ������Ӧ����111�� ʵ���ǣ�" << tj_strcasencmp(s5,  s6,  5)  << endl;
        cout << "  s5 ��s6 �Ƚ�ǰ4 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strcasencmp(s5,  s6,  4)  << endl;
        cout << "4.s7 ��s8 �Ƚ�ǰ10���ַ������Ӧ����0 ��  ʵ���ǣ�" << tj_strcasencmp(s7,  s8,  10) << endl;
        cout << "  s7 ��s8 �Ƚ�ǰ5 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strcasencmp(s7,  s8,  5)  << endl;
        cout << "  s7 ��s8 �Ƚ�ǰ4 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strcasencmp(s7,  s8,  4)  << endl;
        cout << "5.s9 ��s10�Ƚ�ǰ10���ַ������Ӧ����0 ��  ʵ���ǣ�" << tj_strcasencmp(s9,  s10, 10) << endl;
        cout << "  s9 ��s10�Ƚ�ǰ5 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strcasencmp(s9,  s10, 5)  << endl;
        cout << "  s9 ��s10�Ƚ�ǰ4 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strcasencmp(s9,  s10, 4)  << endl;
        press_key("tj_strcasencmp() ������ͣ");

        cout << "6.s11��s12�Ƚ�ǰ10���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strcasencmp(s11, s12, 10) << endl;
        cout << "  s11��s12�Ƚ�ǰ5 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strcasencmp(s11, s12, 5)  << endl;
        cout << "  s11��s12�Ƚ�ǰ2 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strcasencmp(s11, s12, 2)  << endl;
        cout << "7.s13��s14�Ƚ�ǰ10���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strcasencmp(s13, s14, 10) << endl;
        cout << "  s13��s14�Ƚ�ǰ5 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strcasencmp(s13, s14, 5)  << endl;
        cout << "  s13��s14�Ƚ�ǰ2 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strcasencmp(s13, s14, 2)  << endl;
        cout << "8.p15��s1 �Ƚ�ǰ2 ���ַ������Ӧ����-1��  ʵ���ǣ�" << tj_strcasencmp(p15, s1,  2) << endl;
        cout << "  s1 ��p15�Ƚ�ǰ2 ���ַ������Ӧ����1��   ʵ���ǣ�" << tj_strcasencmp(s1,  p15, 5)  << endl;
        cout << "  p15��p16�Ƚ�ǰ2 ���ַ������Ӧ����0��   ʵ���ǣ�" << tj_strcasencmp(p15, p16, 2)  << endl;

        press_key("tj_strcasencmp() �������");
        }

     if (1) {
        char  s1[]="123horseHELLO*#@";
        char  s2[]="1A2b3C*d#E@f";
        char *p3 = NULL;

        cout << "tj_strupr()���Բ��֣�" << endl;
        cout << "1.s1 �����Ӧ����123HORSEHELLO*#@��ʵ���ǣ�" << tj_strupr(s1) << endl;
        cout << "2.s2 �����Ӧ����1A2B3C*D#E@F��    ʵ���ǣ�" << tj_strupr(s2) << endl;
        cout << "3.p3 �����Ӧ����<NULL>��          ʵ���ǣ�" << (tj_strupr(p3)==NULL ? "<NULL>":tj_strupr(p3)) << endl;

        press_key("tj_strupr() �������");
        }

     if (1) {
        char  s1[]="123horseHELLO*#@";
        char  s2[]="1A2b3C*d#E@f";
        char *p3 = NULL;

        cout << "tj_strlwr()���Բ��֣�" << endl;
        cout << "1.s1 �����Ӧ����123horsehello*#@��ʵ���ǣ�" << tj_strlwr(s1) << endl;
        cout << "2.s2 �����Ӧ����1a2b3c*d#e@f��    ʵ���ǣ�" << tj_strlwr(s2) << endl;
        cout << "3.p3 �����Ӧ����<NULL>��          ʵ���ǣ�" << (tj_strlwr(p3)==NULL ? "<NULL>":tj_strlwr(p3)) << endl;

        press_key("tj_strlwr() �������");
        }

     if (1) {
        char  s1[]="This is a pencil.";
        char *p2 = NULL;

        cout << "tj_strchr()���Բ��֣�" << endl;
        cout << "1.s1 �����Ӧ����1��ʵ���ǣ�" << tj_strchr(s1, 'T') << endl;
        cout << "2.s1 �����Ӧ����3��ʵ���ǣ�" << tj_strchr(s1, 'i') << endl;
        cout << "3.s1 �����Ӧ����5��ʵ���ǣ�" << tj_strchr(s1, ' ') << endl;
        cout << "4.s1 �����Ӧ����0��ʵ���ǣ�" << tj_strchr(s1, 'x') << endl;
        cout << "5.p2 �����Ӧ����0��ʵ���ǣ�" << tj_strchr(p2, 'a') << endl;

        press_key("tj_strchr() �������");
        }

     if (1) {
        char  s1[]="This is a pencil.";
        char  s2[]="aabbbceddbbbceeeff";
        char  s3[]="abcde";
        char *p4 = NULL;

        cout << "tj_strstr()���Բ��֣�" << endl;
        cout << "1.s1 �����Ӧ����1�� ʵ���ǣ�" << tj_strstr(s1, "T")      << endl;
        cout << "  s1 �����Ӧ����3�� ʵ���ǣ�" << tj_strstr(s1, "is")     << endl;
        cout << "  s1 �����Ӧ����11��ʵ���ǣ�" << tj_strstr(s1, "pencil") << endl;
        cout << "  s1 �����Ӧ����0�� ʵ���ǣ�" << tj_strstr(s1, "Pencil") << endl;
        cout << "2.s2 �����Ӧ����3�� ʵ���ǣ�" << tj_strstr(s2, "bb")     << endl;
        cout << "  s2 �����Ӧ����3�� ʵ���ǣ�" << tj_strstr(s2, "bbb")    << endl;
        cout << "  s2 �����Ӧ����4�� ʵ���ǣ�" << tj_strstr(s2, "bbc")    << endl;
        cout << "  s2 �����Ӧ����0�� ʵ���ǣ�" << tj_strstr(s2, "bbbb")   << endl;
        cout << "  s2 �����Ӧ����6�� ʵ���ǣ�" << tj_strstr(s2, "ce")     << endl;
        cout << "  s2 �����Ӧ����13��ʵ���ǣ�" << tj_strstr(s2, "cee")    << endl;
        cout << "3.s3 �����Ӧ����1�� ʵ���ǣ�" << tj_strstr(s3, "abcde")  << endl;
        cout << "  s3 �����Ӧ����0�� ʵ���ǣ�" << tj_strstr(s3, "abcdef") << endl;
        cout << "  s3 �����Ӧ����0�� ʵ���ǣ�" << tj_strstr(s3, NULL)     << endl;
        cout << "4.p4 �����Ӧ����0�� ʵ���ǣ�" << tj_strstr(p4, "abc")    << endl;
        cout << "  p4 �����Ӧ����0�� ʵ���ǣ�" << tj_strstr(p4, NULL)     << endl;

        press_key("tj_strstr() �������");
        }

     if (1) {
        char  s1[]="This is a pencil.";
        char *p2  = NULL;

        cout << "tj_strrchr()���Բ��֣�" << endl;
        cout << "1.s1 �����Ӧ����1�� ʵ���ǣ�" << tj_strrchr(s1, 'T') << endl;
        cout << "2.s1 �����Ӧ����15��ʵ���ǣ�" << tj_strrchr(s1, 'i') << endl;
        cout << "3.s1 �����Ӧ����10��ʵ���ǣ�" << tj_strrchr(s1, ' ') << endl;
        cout << "4.s1 �����Ӧ����0�� ʵ���ǣ�" << tj_strrchr(s1, 'x') << endl;
        cout << "5.p2 �����Ӧ����0�� ʵ���ǣ�" << tj_strrchr(p2, 'a') << endl;

        press_key("tj_strrchr() �������");
        }

     if (1) {
        char  s1[]="This is a pencil.";
        char  s2[]="aabbbceddbbbceeeff";
        char  s3[]="abcde";
        char *p4 = NULL;

        cout << "tj_strrstr()���Բ��֣�" << endl;
        cout << "1.s1 �����Ӧ����1�� ʵ���ǣ�" << tj_strrstr(s1, "T")      << endl;
        cout << "  s1 �����Ӧ����6�� ʵ���ǣ�" << tj_strrstr(s1, "is")     << endl;
        cout << "  s1 �����Ӧ����11��ʵ���ǣ�" << tj_strrstr(s1, "pencil") << endl;
        cout << "  s1 �����Ӧ����0�� ʵ���ǣ�" << tj_strrstr(s1, "Pencil") << endl;
        cout << "2.s2 �����Ӧ����11��ʵ���ǣ�" << tj_strrstr(s2, "bb")     << endl;
        cout << "  s2 �����Ӧ����10��ʵ���ǣ�" << tj_strrstr(s2, "bbb")    << endl;
        cout << "  s2 �����Ӧ����11��ʵ���ǣ�" << tj_strrstr(s2, "bbc")    << endl;
        cout << "  s2 �����Ӧ����0�� ʵ���ǣ�" << tj_strrstr(s2, "bbbb")   << endl;
        cout << "  s2 �����Ӧ����13��ʵ���ǣ�" << tj_strrstr(s2, "ce")     << endl;
        cout << "  s2 �����Ӧ����13��ʵ���ǣ�" << tj_strrstr(s2, "cee")    << endl;
        cout << "3.s3 �����Ӧ����1�� ʵ���ǣ�" << tj_strrstr(s3, "abcde")  << endl;
        cout << "  s3 �����Ӧ����0�� ʵ���ǣ�" << tj_strrstr(s3, "abcdef") << endl;
        cout << "  s3 �����Ӧ����0�� ʵ���ǣ�" << tj_strrstr(s3, NULL)     << endl;
        cout << "4.p4 �����Ӧ����0�� ʵ���ǣ�" << tj_strrstr(p4, "abc")    << endl;
        cout << "  p4 �����Ӧ����0�� ʵ���ǣ�" << tj_strrstr(p4, NULL)     << endl;

        press_key("tj_strrstr() �������");
        }

     if (1) {
        char  s1[]="This is a pencil.";
        char  s2[]="aabbbceddbbbceeeff";
        char  s3[]="";
        char *p4 = NULL;

        cout << "tj_strrev()���Բ��֣�" << endl;
        cout << "1.s1 �����Ӧ����This is a pencil.��  ʵ���ǣ�" << s1 << endl;
        cout << "  s1 �����Ӧ����.licnep a si sihT��  ʵ���ǣ�" << tj_strrev(s1) << endl;

        cout << "2.s2 �����Ӧ����aabbbceddbbbceeeff�� ʵ���ǣ�" << s2 << endl;
        cout << "  s2 �����Ӧ����ffeeecbbbddecbbbaa�� ʵ���ǣ�" << tj_strrev(s2) << endl;

        cout << "3.s3 �����Ӧ����--�� ʵ���ǣ�-" << s3            << "-" << endl;
        cout << "  s3 �����Ӧ����--�� ʵ���ǣ�-" << tj_strrev(s3) << "-" << endl;

        cout << "4.p4 �����Ӧ����<NULL>�� ʵ���ǣ�" << (p4==NULL ? "<NULL>" : p4) << endl;
        cout << "  p4 �����Ӧ����<NULL>�� ʵ���ǣ�" << (tj_strrev(p4)==NULL ? "<NULL>" : tj_strrev(s3)) << endl;

        press_key("tj_strrev() �������");
        }

    return 0;
}