#include <stdio.h>

int IsPrime(int n)
{
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)return 0;
    }
    return 1;
}

int main()
{
    int num;
    scanf("%d",&num);
    if(IsPrime(num))printf("Y");
    else printf("N");
    return 0;
}