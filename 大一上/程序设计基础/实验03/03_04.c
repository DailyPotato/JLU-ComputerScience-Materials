#include <stdio.h>
#include <math.h>

int judge(long long n)
{
    long long square=n*n;
    long long temp=n;
    while(temp>0)
    {
        if(square%10!=temp%10)return 0;
        temp/=10;
        square/=10;
    }
    return 1;
}

int main() 
{
    long long n;
    scanf("%lld", &n);
    for(long long i=1;i<=n;i++)
    {
        if(judge(i))
        {
            printf("%lld ",i);
        }
    }
}