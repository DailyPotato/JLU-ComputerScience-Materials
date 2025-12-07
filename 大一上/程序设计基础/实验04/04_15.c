#include <stdio.h>

int main()
{
    int n,k;
    scanf("%d%d", &n, &k);
    int arr[40];
    int index=0;
    if(n==0)
    {
        printf("0");
        return 0;
    }
    while(n>0)
    {
        int temp=n%k;
        arr[index++]=temp;
        n/=k;
    }

    for(int i=index-1;i>=0;i--)
    {
        printf("%d", arr[i]);
    }
}