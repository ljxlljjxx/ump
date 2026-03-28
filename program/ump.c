#include <stdio.h>

FILE *file;
char str[10000];

int main()
{
	file = fopen("/Users/ljx/useful_mini_program/ReadMe.txt", "r");
	while (fgets(str, 10000, file) != NULL)
		printf("%s", str);
	fclose(file);
	return 0;
}

