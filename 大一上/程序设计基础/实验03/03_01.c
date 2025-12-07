#include <stdio.h>

int main() 
{
    int m,n;
    scanf("%d%d",&m,&n);
    if(m<=0 || n<=0)
    {
        printf("-1");
        return 0;
    }
    if(m<n)
    {
        printf("0");
        return 0;
    }
    if(m==n)
    {
        printf("1");
        return 0;
    }
    long long res=1;
    for(int i=m;i>=1;i--)res*=i;
    for(int i=n;i>=1;i--)res/=i;
    for(int i=m-n;i>=1;i--)res/=i;
    printf("%lld",res);
    return 0;
}