#include <stdio.h>

long long function(int m,int n)
{
    if(n<0)return 0;
    if(n==0)return 1;
    if(n==1)return m;
    if(m<2*n)return function(m,m-n);
    return function(m-1,n-1)+function(m-1,n);
}


int main()
{
    int m,n;
    scanf("%d%d",&m,&n);
    long long result = function(m,n);
    printf("%lld",result);
    return 0;
}