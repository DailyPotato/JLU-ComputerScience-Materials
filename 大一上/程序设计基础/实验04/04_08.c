#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n;
    scanf("%d",&n);
    int **pp=(int **)malloc(n*sizeof(int *));
    for(int i=0;i<n;i++)
    {
        pp[i]=(int *)malloc(n*sizeof(int));
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&pp[i][j]);
        }
    }
    for(int j=0;j<n-1;j++)
    {
        for(int i=0;i<n-1;i++)
        {
            printf("%d ",pp[i][j]);
        }
        printf("%d",pp[n-1][j]);
        printf("\n");
    }
    for(int i=0;i<n-1;i++)
    {
        printf("%d ",pp[i][n-1]);
    }
    printf("%d",pp[n-1][n-1]);
    

    return 0;
}