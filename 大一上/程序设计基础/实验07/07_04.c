#include <stdio.h>

int gcd(int a, int b)
{
    int temp=a%b;
    if(temp==0)return b;
    else return gcd(b,temp);
}

int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    int result = gcd(a,b);
    printf("%d",result);
    return 0;
}