#include <stdio.h>

int func(int a, int b, int n)
{
    return (a >= b) ? (b * n == a) : (a * n == b);
}

int main()
{
    int n, res = 0;
    scanf("%d", &n);
    int a[20][110];
    int count[20] = {0};
    int i = 0, j = 0;
    int temp;
    scanf("%d", &temp);
    while (temp != -1)
    {
        while (temp != 0)
        {
            a[i][j++] = temp;
            scanf("%d", &temp);
        }
        a[i][j] = 0;
        count[i] = j;
        j = 0;
        i++;
        scanf("%d", &temp);
    }


    for (int k = 0; k < i; k++)
    {
        for (int l = 0; l < count[k]; l++)
        {
            for (int m = l + 1; m < count[k]; m++)
            {
                if (func(a[k][l], a[k][m], n))
                {
                    res++;
                }
            }
        }
        printf("%d\n", res);
        res = 0;
    }
    return 0;
}