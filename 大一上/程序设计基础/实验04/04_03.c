#include <stdio.h>
#include <stdbool.h>

int x1[15], x2[15], x3[15];
int cmp = 0, move = 0, swap_cnt = 0;
bool swapped;

void PrincipalSort(int a[], int n)
{
    for (int i = 1; i <= n - 1; ++i)
    {
        int minj = i;
        for (int j = i + 1; j <= n; ++j)
        {
            cmp++;
            if (a[j] < a[minj]) minj = j;
        }
        int temp = a[minj];
        a[minj] = a[i];
        a[i] = temp;
        swap_cnt++;
    }
    printf("%d %d ", cmp, swap_cnt);
    cmp = 0;
    swap_cnt = 0;
}

void BubbleSort(int a[], int n)
{
    for (int i = 1; i <= n; ++i)
    {
        swapped = 0;
        for (int j = 1; j <= n - 1; ++j)
        {
            cmp++;
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swap_cnt++;
                swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
    printf("%d %d ", cmp, swap_cnt);
    cmp = 0;
    swap_cnt = 0;
}

void InsertSort(int a[], int n)
{
    for (int i = 2; i <= n; ++i)
    {
        int key = a[i];
        int j = i - 1;
        bool moved = 0;
        while (j >= 1)
        {
            cmp++;
            if (a[j] > key)
            {
                a[j + 1] = a[j];
                moved = 1;
                move++;    
                j--;
            }
            else break;
        }
        if (moved) 
        {
            a[j + 1] = key; 
            move++;
        }
        if (j == 0) cmp++;
    }
    printf("%d %d", cmp, move);
    cmp = 0;
    move = 0;
}

int main()
{
    for (int i = 1; i <= 10; ++i)
    {
        scanf("%d", &x1[i]);
        x2[i] = x1[i];
        x3[i] = x1[i];
    }
    PrincipalSort(x1, 10);
    BubbleSort(x2, 10);
    InsertSort(x3, 10);
    return 0;
}