#include <stdio.h>

int main()
{
    long long fibonacci[100];
    fibonacci[0] = 1;
    fibonacci[1] = 1;
    for(int i=2;i<100;i++)
    {
        fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
    }
    int n;
    scanf("%d", &n);
    printf("%lld", fibonacci[n]);
    return 0;
}