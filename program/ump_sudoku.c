#include <stdio.h>
#include <stdbool.h>

int A[9][9];
bool vis1[9][9];
bool vis2[9][9];

void dfs(int xy)
{
    if (xy >= 81)
    {
        putchar(10);
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (vis1[i][j]) printf("\033[91m");
                printf("%d ", A[i][j]);
                if (vis1[i][j]) printf("\033[0m");
            }
                
            putchar(10);
        }
        return;
    }
    int x = xy/9, y = xy%9;
    if (vis2[x][y])
    {
        dfs(xy+1);
        return;
    }
    bool kn[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int cnt;
    for (int i = 0; i < 9; i++) if (vis2[x][i]) kn[A[x][i]] = 0;
    for (int i = 0; i < 9; i++) if (vis2[i][y]) kn[A[i][y]] = 0;
    for (int i = x-x%3; i < x-x%3+3; i++) for (int j = y-y%3; j < y-y%3+3; j++) if (vis2[i][j]) kn[A[i][j]] = 0;
    for (int i = 1; i <= 9; i++) if (kn[i]) cnt++;
    if (cnt == 0) return;
    else
    {
        for (int i = 1; i <= 9; i++) if (kn[i])
        {
            A[x][y] = i;
            vis2[x][y] = 1;
            dfs(xy+1);
            A[x][y] = 0;
            vis2[x][y] = 0;
        }
    }
}

int main()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            scanf("%1d", A[i]+j);
            vis1[i][j] = vis2[i][j] = A[i][j];
        }
    }
    dfs(0);
    return 0;
}
