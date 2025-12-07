#include <stdio.h>

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    int a[n][m];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    int *p=a[0];
    int max=n*m;
    while(max>1)
    {
        if(*p>*(p+1))
        {
            int temp=*p;
            *p=*(p+1);
            *(p+1)=temp;
        }
        p++;
        if(p==&a[n-1][m-1])
        {
            max--;
            p=a[0];
        }
    }
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<m-1;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("%d",a[i][m-1]);
        printf("\n");
    }
    for(int j=0;j<m-1;j++)
        {
            printf("%d ",a[n-1][j]);
        }
        printf("%d",a[n-1][m-1]);

    return 0;
}