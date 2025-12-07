#include <stdio.h>

int cut(int n,int k)
{
    if(n<=k)return 1;
    return cut(2.0*n/5+0.5,k)+cut(n-(int)(2.0*n/5+0.5),k);
}

int main()
{
    int n,k;
    scanf("%d%d", &n,&k);
    printf("%d",cut(n,k));
    return 0;
}