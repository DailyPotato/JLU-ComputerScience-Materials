#include <stdio.h>
#include <ctype.h>

int index=0;
void f(long long a[], long long n,long long b)
{
    if(n==0)return;
    a[index++]=n%b;
    f(a,n/b,b);
}
/* 579 8   579/8=72...3 72/8=9...0 9/8=1...1 1/8=0...1*/

int main()
{
    long long N,b;
    scanf("%lld%lld",&N,&b);
    long long a[40];
    if(N==0)
    {
        printf("0");
        return 0;
    }
    f(a,N,b);
    // for(int i=0;i<index;i++)
    // {
    //     printf("%d",a[i]);
    // }
    for(int i=index-1;i>=0;i--)
    {
        if(isdigit(a[i]+'0'))printf("%d",a[i]);
        else printf("%c",a[i]-10+'A');
    }
    return 0;
}