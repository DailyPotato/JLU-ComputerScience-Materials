#include <stdio.h>

int findmax(int *p, int n)
{
    if (n <= 1)
        return 0;
    int temp=findmax(p, n - 1);
    return *(p+n)>=temp?*(p+n):temp;
}
int main()
{
    int n;
    scanf("%d", &n);
    int a[n];
    int *arr = a;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", arr + i);
    }
    printf("%d", findmax(arr, n-1));
    return 0;
}