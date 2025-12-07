#include <stdio.h>

double func(double x,int n)
{
    if(n==0)return 1;
    if(n==1)return x;
    return (2*n-1)*x*func(x,n-1)/n-(n-1)*func(x,n-2)/n;
}

int main()
{
    double x;
    int n;
    scanf("%lf%d",&x,&n);
    double result=func(x,n);
    printf("%.2lf",result);

    return 0;
}