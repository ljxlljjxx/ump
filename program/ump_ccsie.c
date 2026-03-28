#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#define N 10000000

char str[N+3];
int a, size, temp;
FILE *file, *file_temp;
clock_t start, end;
struct stat file_stat;
unsigned long long cnt;
size_t len;
const char *const old[] = {"，", "：", "；", "【", "】", "（", "）", "？", "！", "…"};
const char *const new[] = {", ", ": ", "; ", "[" , "]" , "(" , ")" , "? ", "! ", "..."};

int my_strcmp(const char *a, const char *b)
{
	for (const char *c = b; *c != 0; c++)
	{
		if (*c != a[c-b]) return 0;
	}
	return 1;
}

int replace(const char *a, FILE *file)
{
	const int size = strlen(a);
	int cnt = 0;
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < sizeof(old)/sizeof(*old); i++)
		{
			if (my_strcmp(a+j, old[i]))
			{
				fputs(new[i], file);
				j += strlen(old[i]) - 1;
				cnt++;
				goto End;
			}
		}
		fputc(a[j], file);
End:;
	}
	return cnt;
}


int main(int argc, char *argv[])
{	
	printf("\033[92m该文件用于将中文的标点符号(，：；【】（）？！…)替换为相应的英文符号(,:;[]()?!...)\n使用应将要修改的文件依次填写在该指令右端\n\033[91m注意: \033[92m不要同时运行多个该程序，否则导致混乱\n作者: ljx 日期: 2025年3月22日\n\033[91m用法: \033[92m%s file ...\033[0m\n", argv[0]);
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
		
		for (size = 0; size < N; size++)
		{
			a = fgetc(file);
			if (a != EOF)
				str[size] = a;
			else
			{
				str[size] = 0;
				break;
			}
		}

		if (size != N)
		{
			fclose(file);
			file = fopen(argv[i], "w");
			replace(str, file);
			fclose(file);
		}
		else
		{
			file_temp = fopen("/Users/ljx/useful_mini_program/temp/ccsie", "w");
			stat(argv[i], &file_stat);
			len = 0;
			while (size == N)
			{
				start = clock();
				replace(str, file_temp);
				str[0] = str[N-3],
				str[1] = str[N-2],
				str[2] = str[N-1],
				str[3] = 0;

				for (size = 3; size < N; size++)
				{
					a = fgetc(file);
					if (a != EOF)
						str[size] = a;
					else
						break;
				}
				str[size] = 0;
				end = clock();
				cnt += size;
				temp = printf("\r%s step 1: %.6lfMB/s now, still need %.6lfs.", argv[i], (N/1048576.0)/((double)(end-start) / CLOCKS_PER_SEC), (file_stat.st_size-cnt)/(N/((double)(end-start) / CLOCKS_PER_SEC)));
				for (size_t space = temp; space < len; space++) putchar(32);
				len = temp;
				fflush(stdout);
			}
			replace(str, file_temp);
			fclose(file), fclose(file_temp);
			temp = printf("\r%s step 1: \033[92mfinished\033[0m", argv[i]);
			for (size_t space = temp; space < len+9; space++) putchar(32); putchar(10);
			file = fopen(argv[i], "w");
			file_temp=fopen("/Users/ljx/useful_mini_program/temp/ccsie", "r");
			len = 0; temp = 0; start = clock(); cnt += N;
			while ((a = fgetc(file_temp)) != EOF)
			{
				if (temp++ == N)
				{
					end = clock(); cnt -= N;
					temp = printf("\r%s step 2: %.6lfMB/s now, still need %.6lfs.", argv[i], (N/1048576.0)/((double)(end-start) / CLOCKS_PER_SEC), (cnt)/(N/((double)(end-start) / CLOCKS_PER_SEC)));
					for (size_t space = temp; space < len; space++) putchar(32);
					len = temp;
					fflush(stdout);
					start = clock();
				}
				fputc(a, file);
			}
			temp = printf("\r%s step 2: \033[92mfinished\033[0m", argv[i]); 
			for (size_t space = temp; space < len+9; space++) putchar(32); putchar(10);
			fclose(file), fclose(file_temp);
		}
		printf("\033[93m已完成: %s\n", argv[i]);
	}
	puts("\033[92m已全部完成\033[0m");
	return 0;
}

