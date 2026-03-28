#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n, t, m;
char a[] = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_______________";
char b[] = "1234567890";
char c[] = "qwertyuiopasdfghjklzxcvbnm";
char d[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
char *e[] = {"source_code", "code", "source", "match", "level", "next"};
char *f[] = {".net", ".com.cn", ".cn", ".com", ".org", ".edu", ".gov", ".mil", ".int", ".info", ".biz", ".name", ".tv", ".dc", ".top"};

int main()
{
    printf("https://www.");
    srand(time(NULL));
    n = rand() % 10 + 3;
    for (int i = 0; i < n; i++)
    {
        putchar(a[rand()%sizeof(a)]);
    }
    printf("%s", f[rand()%(sizeof(f)/sizeof(*f))]);
    m = rand() % 5 + 2;
    for (int x = 0; x < m; x++)
    {
        putchar('/');
        switch (rand() % 10)
        {
            case 1:
                printf("%s", e[rand()%(sizeof(e)/sizeof(*e))]);
                putchar('=');
                for (int i = 0; i < 32; i++)
                    putchar(c[rand()%sizeof(c)]);
                    break;
            case 2:
                printf("%s", e[rand()%(sizeof(e)/sizeof(*e))]);
                putchar('=');
                for (int i = 0; i < 32; i++)
                    putchar(d[rand()%sizeof(d)]);
                break;
            case 3:
                printf("%s", e[rand()%(sizeof(e)/sizeof(*e))]);
                putchar('=');
                n = rand() % 10 + 10;
                for (int i = 0; i < n; i++)
                    putchar(b[rand()%sizeof(b)]);
                break;
            case 4:
                printf("%s", e[rand()%(sizeof(e)/sizeof(*e))]);
                putchar('=');
                n = rand() % 32 + 20;
                for (int i = 0; i < n; i++)
                    putchar(a[rand()%sizeof(a)]);
                break;
			case 5:
				printf("page=%u", rand());
				break;
            default:
                if (rand() % 2) putchar('?');
                n = rand() % 5 + 1;
                for (int i = 0; i < n; i++)
                    putchar(c[rand()%sizeof(c)]);
                if (rand() % 2) putchar('.');
                n = rand() % 5 + 1;
                for (int i = 0; i < n; i++)
                    putchar(c[rand()%sizeof(c)]);
                if (rand() % 2) putchar('.');
                n = rand() % 5 + 1;
                for (int i = 0; i < n; i++)
                    putchar(c[rand()%sizeof(c)]);
                if (rand() % 2) putchar('.');
                n = rand() % 5 + 1;
                for (int i = 0; i < n; i++)
                    putchar(c[rand()%sizeof(c)]);
        }
    }
	putchar(10);
    return 0;
}

