#include <stdio.h>
#include <math.h>
int main()
{
    double x,y,z,A,B,C,D;
    scanf("%lf%lf%lf%lf%lf%lf%lf",&x,&y,&z,&A,&B,&C,&D);
    double monecule=fabs(A*x+B*y+C*z+D);
    double denominator=sqrt(A*A+B*B+C*C);
    double res=monecule/denominator;
    printf("%.3lf",res);
    return 0;
}