#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	FILE *fp;
	char buf[80] = "abc\x0A";

	fp = fopen("out.txt", "wb");
	int ret = fwrite(buf, 2, 15, fp);
	printf("ret=%d\n", ret);
	fclose(fp);

	return 0;
}
