#include <stdio.h>
#include <math.h>
struct complex
{
    double real;
    double imag;
};
struct complex add(struct complex a,struct complex b)
{
    struct complex temp;
    temp.real=a.real+b.real;
    temp.imag=a.imag+b.imag;
    return temp;
}

struct complex sub(struct complex a,struct complex b)
{
    struct complex temp;
    temp.real=a.real-b.real;
    temp.imag=a.imag-b.imag;
    return temp;
}

struct complex mul(struct complex a,struct complex b)
{
    struct complex temp;
    temp.real=a.real*b.real-a.imag*b.imag;
    temp.imag=a.real*b.imag+a.imag*b.real;
    return temp;
}

int main()
{
    struct complex a, b;
    scanf("%lf%lf%lf%lf", &a.real, &a.imag, &b.real, &b.imag);
    if(add(a,b).imag==0.0)
    {
        printf("%.2lf    ", add(a, b).real);
    }
    else if(add(a,b).imag>0.0)
    {
        printf("%.2lf+%.2lfi    ", add(a, b).real, add(a, b).imag);
    }
    else
    {
        printf("%.2lf-%.2lfi    ", add(a, b).real, fabs(add(a, b).imag));
    }
    if(sub(a,b).imag==0.0)
    {
        printf("%.2lf    ", sub(a, b).real);
    }
    else if(sub(a,b).imag>0.0)
    {
    printf("%.2lf+%.2lfi    ", sub(a, b).real, sub(a, b).imag);
    }
    else
    {
        printf("%.2lf-%.2lfi    ", sub(a, b).real, fabs(sub(a, b).imag));
    }
    if(mul(a,b).imag==0.0)
    {
        printf("%.2lf", mul(a, b).real);
    }
    else if(mul(a,b).imag>0.0)
    {
        printf("%.2lf+%.2lfi", mul(a, b).real, mul(a, b).imag);
    }
    else
    {
        printf("%.2lf-%.2lfi", mul(a, b).real, fabs(mul(a, b).imag));
    }
    return 0;
}