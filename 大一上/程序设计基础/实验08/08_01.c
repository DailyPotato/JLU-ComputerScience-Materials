#include <stdio.h>

// 碎碎念：没学过dfs，纯自己摸索，全题没问过一次ai，难死我了wc，这一题做了两个小时，终于搞出来了，爽！！！，差点就“绝望的一批，真该留在数学”了

int min(int a, int b);
void mydfs(int num, int *arr, int i, int max, int *total, int *index, int remaining);

int main()
{
    int num;
    scanf("%d", &num);
    int arr[num + 1], index = 0;
    for (int i = num - 1; i > 0; i--)
    {
        int total = 0,remaining = num - i;
        arr[0] = i;
        arr[1] = 0;
        mydfs(num, arr, i, min(i, num - i), &total, &index, remaining);
    }
    return 0;
}

int min(int a, int b)
{
    if (a < b)return a;
    else return b;
}
// num是要分解的数，arr是存放分解结果的数组
// i是当前要分解的数的第一位，
// max是当前最大的数，保证arr后续数字不能大于它，在每个i变动后max=i
// total是当前已经分解的数的和，index是arr的索引，使递归时可以找到位置，count是arr的长度
// remaining是num-i，表示还需要分配的数
void mydfs(int num, int *arr, int i, int max, int *total, int *index, int remaining)
{
    if (max <= 0 || *index == -1)return;
    // 功能 确定当前索引的最大值，记录total
    arr[++(*index)] = max;
    *total += max;
    // 功能 判断一条支路走完，打印结果，回溯
    if (*total == remaining)
    {
        // 递归出口
        if (arr[1] == 1)
        {
            printf("%d=%d", num, arr[0]);
            for (int j = 1; j < remaining + 1; j++)printf("+1");
            printf("\n");
            *total = 0;
            *index = 0;
            return;
        }
        printf("%d=%d", num, arr[0]);
        for (int j = 1; j < *index + 1; j++)printf("+%d", arr[j]);
        printf("\n");
        while (arr[*index] == 1)
        {
            *total -= 1;
            (*index)--;
        }
        *total -= 1;
        arr[*index]--;
        mydfs(num, arr, i, min(arr[*index], remaining - *total), total, index, remaining);
    }
    // 递归调用
    else mydfs(num, arr, i, min(max, remaining - *total), total, index, remaining);
}
