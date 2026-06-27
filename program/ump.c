#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH "/Users/ljx/Desktop/P/github/ump"

FILE *file;
char str[10000];
char new_str[10000] = "cd "PATH"; ";

int main()
{
	file = fopen(PATH"/ReadMe.txt", "r");
	while (fgets(str, 10000, file) != NULL)
	{
		printf("%s", str);
		if (str[0] == 'g' && str[1] == 'c' && str[2] == 'c')
		{
			strcpy(new_str + 36, str);
			system(new_str);
		}
	}
	fclose(file);
	return 0;
}

