#include <stdio.h>
#include <string.h>

FILE *file, *out;
char str[1000001], *str_;
int new_line = 1;

int main(int argc, char *argv[])
{
	printf("\033[92m该文件用于清除文件左端的空格和制表符\n使用应将要修改的文件依次填写在该指令右端\n注意: 不要同时运行多个该程序，否则导致混乱\n作者: ljx 日期: 2025年3月22日\n\033[91m用法: \033[92m%s file ...\033[0m\n", argv[0]);
	if (argc == 1)
	{
		return 0;
	}
	for (int i = 1; i < argc; i++)
	{
		file = fopen(argv[i], "r");
		if (file == NULL)
		{
			printf("\033[91merror\033[0m: no such file or directory: '%s'\n", argv[i]);
			continue;
		}

		out = fopen("/Users/ljx/useful_mini_program/temp/lrs", "w");
		while (fgets(str, 1000000, file) != NULL)
		{
			if (*str != 0)
			{
				if (new_line == 0)
				{
					fputs(str, out);
					if (str[strlen(str)-1]==10) new_line = 1;
					continue;
				}
				str_ = str;
				if (str[strlen(str)-1] != 10) new_line = 0;
				else new_line = 1;
				str[strlen(str)-1] = 0;
				for (int j = 0; j <= strlen(str)-1; j++)
				{
					if (str[j] == ' ' || str[j] == '\t')
						str_++;
					else
						break;
				}
				fputs(str_, out);
				fputc(10, out);
			}
		}
		fclose(file), fclose(out);

		file = fopen("/Users/ljx/useful_mini_program/temp/lrs", "r");
		out = fopen(argv[i], "w");
		while (fgets(str, 1000000, file))
			fputs(str, out);
		fclose(file), fclose(out);

		printf("\033[93m已完成: %s\n", argv[i]);
	}
	puts("\033[92m已全部完成\033[0m");
	return 0;
}
