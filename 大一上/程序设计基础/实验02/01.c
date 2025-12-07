#include <stdio.h>
#include <stdlib.h>
int cmp(const void *a,const void *b)
{
    if(*(double*)a>=*(double*)b)
        return 1;
    else return -1;
}



int main()
{
    double a[3];
    for(int i=0;i<3;i++)
    {
        scanf("%lf",&a[i]);
    }
    qsort(a,3,sizeof(double),cmp);
    for(int i=0;i<3;i++)
    {
        printf("%.1lf ",a[i]);
    }
    return 0;
}