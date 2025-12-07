#include <stdio.h>

double hermite(int n, double x)
{
    if (n == 0) return 1;
    if(n==1)return 2*x;
    return 2*x*hermite(n-1,x)-2*(n-1)*hermite(n-2,x);
}

int main()
{
    int n;
    double x;
    scanf("%d%lf", &n, &x);
    double result = hermite(n, x);
    printf("%.2lf", result);
    return 0;
}