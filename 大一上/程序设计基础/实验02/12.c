#include <stdio.h>

double term(double x, int n)
{
    if(n==0)return 1;
    return x*term(x,n-1)/n;
}

int main()
{
    double x,res=0;
    scanf("%lf", &x);
    for(int i=0;i<100;i++)
    {
        res+=term(x,i);
    }
    printf("%.2lf", res);
    return 0;
}