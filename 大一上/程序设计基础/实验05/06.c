#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m,n;
    scanf("%d%d",&m,&n);
    int **p=(int **)malloc(m*sizeof(int *));
    int total=0;
    for(int i=0;i<m;i++)
    {
        p[i]=(int *)malloc(n*sizeof(int));
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",(*(p+i)+j));
            total+=*(*(p+i)+j);
        }
    }
    printf("%.2lf ",(double)total/m/n);
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ",*(*(p+i)+j));
        }
    }
    return 0;
}