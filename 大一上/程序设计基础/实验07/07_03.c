#include <stdio.h>

long long ackerman(int m, int n)
{
    if(m==0)return n+1;
    if(n==0)return ackerman(m-1,1);
    return ackerman(m-1,ackerman(m,n-1));
}

int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    long long result = ackerman(m, n);
    printf("%lld", result);
    return 0;
}