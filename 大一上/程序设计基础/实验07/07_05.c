#include <stdio.h>
#include <stdlib.h>

int find(int *arr, int n, int x,int index)
{
    if(index==n)
    {
        printf("NULL");
        exit(0);
    }
    if(arr[index]==x)return index;
    return find(arr,n,x,index+1);
}

int main()
{
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    int x;
    scanf("%d", &x);
    int *arr = a;
    int result = find(arr, n, x, 0);
    printf("%d", result);
    return 0;
}