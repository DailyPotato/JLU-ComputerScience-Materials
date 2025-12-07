#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    int **pp = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        pp[i] = (int *)malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &pp[i][j]);
        }
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (pp[i][j] != pp[j][i])
            {
                printf("NO");
                return 0;
            }
        }
    }
    printf("YES");
    return 0;
}