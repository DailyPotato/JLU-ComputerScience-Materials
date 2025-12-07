#include <stdio.h>

int main()
{
    int n,s,m;
    scanf("%d%d%d",&n,&s,&m);
    int num=n;
    int a[n+1];
    a[0]=0;
    for(int i=1;i<=n;i++)a[i]=1;
    int i=s;
    for(int m1=0;;i++)
    {
        if(i>num)i=1;
        if(n==1)
        {
            for(int j=1;j<=num;j++)
            {
                if(a[j]==1)
                {
                    printf("%d",j);
                    return 0;
                }
            }
        }
        if(a[i]==0)continue;
        m1++;
        if(m1==m)
        {
            a[i]=0;
            n--;
            printf("%d ",i);
            m1=0;
        }
    }
    return 0;
}