#include <stdio.h>
#include <math.h>

int main() 
{
    int n;
    scanf("%d", &n);
    double x[10], y[10];
    for (int i = 0; i < n; i++)
    {
        scanf("%lf%lf", &x[i], &y[i]);
    }
    double res = 0;
    for (int i = 0; i < n-1; i++)
    {
        double tempx=x[i+1]-x[i];
        double tempy=y[i+1]-y[i];
        res+=sqrt(tempx*tempx+tempy*tempy);
    }
    if(n>2)res+=sqrt((x[0]-x[n-1])*(x[0]-x[n-1])+(y[0]-y[n-1])*(y[0]-y[n-1]));
    printf("%.2lf", res);
    return 0;
}