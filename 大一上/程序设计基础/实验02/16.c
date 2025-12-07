#include <stdio.h>
#include <stdlib.h>

int min(int a,int b)
{
    if(a<b)return a;
    else return b;
}
int gcd(int a,int b)
{
    int temp=min(a,b);
    int t=0;
    for(int i=1;i<=temp;i++)
    {
        if(a%i==0&&b%i==0)t=i;
    }
    return t;
}
int lcm(int a,int b)
{
    return a*b/gcd(a,b);
}
int main()
{
    int num;
    scanf("%d",&num);
    int a[num];
    for(int i=0;i<num;i++)
    {
        scanf("%d",&a[i]);
    }
    int res=1;
    for(int i=0;i<num;i++)
    {
        res=lcm(res,a[i]);
    }
    printf("%d",res);

    return 0;
}