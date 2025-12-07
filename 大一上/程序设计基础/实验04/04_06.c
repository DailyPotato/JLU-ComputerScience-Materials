#include <stdio.h>
#include <stdlib.h>

void reverse(int *arr,int begin,int k)
{
    for(int i=0;i<k/2;i++)
    {
        int temp=arr[i+begin];
        arr[i+begin]=arr[begin+k-i-1];
        arr[begin+k-i-1]=temp;
    }
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    k %= n;
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    reverse(arr,0,n); 
    reverse(arr,0,k);
    reverse(arr,k,n-k);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    free(arr);
    return 0;
}