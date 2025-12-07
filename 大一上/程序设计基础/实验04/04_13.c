#include <stdio.h>

int main()
{
    int n;
    int arr[30][30];
    scanf("%d", &n);
    int count = 1;
    int i = 0, j = 0;
    for (i = 0; i < n; i++)
    {
        int temp = i;
        for (j = i; j < n - temp; j++)
        {
            if (count == n * n + 1)
                break;
            arr[i][j] = count;
            count++;
        }
        j--;
        i++;
        for (; i < n - temp; i++)
        {
            if (count == n * n + 1)
                break;
            arr[i][j] = count;
            count++;
        }
        i--;
        j--;
        for (; j >= temp; j--)
        {
            if (count == n * n + 1)
                break;
            arr[i][j] = count;
            count++;
        }
        j++;
        i--;
        for (; i > temp; i--)
        {
            if (count == n * n + 1)
                break;
            arr[i][j] = count;
            count++;
        }
        if (count == n * n + 1)
            break;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%4d", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}