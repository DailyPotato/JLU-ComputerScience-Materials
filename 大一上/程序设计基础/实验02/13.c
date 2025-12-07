#include <stdio.h>

int main()
{
    long long n;
    scanf("%lld", &n);
    double res=2;
    for(int i=1;i<=n;i++)
    {
        res*=4.0*i*i/(4.0*i*i-1);
    }
    printf("%.10lf", res);
    return 0;
}