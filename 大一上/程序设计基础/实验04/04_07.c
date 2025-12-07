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
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            int temp=pp[i][j];
            for(int m=i;m<n;m++)
            {
                for(int v=j+1;v<n;v++)
                {
                    if(temp==pp[m][v])
                    {
                        printf("YES");
                        return 0;
                    }
                }
            }
        }
    }
    printf("NO");
    return 0;
}