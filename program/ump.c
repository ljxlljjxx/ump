#include <stdio.h>
#include <stdlib.h>

FILE *file;
char str[10000];

int main()
{
	file = fopen("/Users/ljx/useful_mini_program/ReadMe.txt", "r");
	while (fgets(str, 10000, file) != NULL)
	{
		printf("%s", str);
		if (str[0] == 'g' && str[1] == 'c' && str[2] == 'c')
		{
			system(str);
		}
	}
	fclose(file);
	return 0;
}

