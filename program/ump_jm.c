#include <stdio.h>
#include <string.h>

char *password = NULL;
char *filename = NULL;
FILE *file = NULL, *temp = NULL;
size_t password_len = 0;

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fputs("参数个数太少(指令+密码+文件)\n", stderr);
        return -1;
    }
    password = argv[1];
    password_len = strlen(password);
    for (int i = 2; i < argc; i++)
    {
        filename = argv[i];
        file = fopen(filename, "rb");
        if (file == NULL)
        {
            fprintf(stderr, "第%d份文件(%s)无法打开!\n", i-1, filename);
            continue;
        }
        temp = tmpfile();
        for (int j = 0, now = fgetc(file); now != EOF; now = fgetc(file), j++)
        {
            fputc(now ^ ~(password[j % password_len]), temp);
        }
        fclose(file);
        file = fopen(filename, "wb");
        if (file == NULL)
        {
            fprintf(stderr, "第%d份文件(%s)无法打开!\n", i-1, filename);
            continue;
        }
        rewind(temp);
        for (int now = fgetc(temp); now != EOF; now = fgetc(temp))
        {
            fputc(now, file);
        }
        fclose(temp);
        fclose(file);
    }
    return 0;
}
