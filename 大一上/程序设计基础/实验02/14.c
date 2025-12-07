#include <stdio.h>

void print(int count, int total)
{
    if(count==0)return;
    for(int i=1;i<count;i++)
    {
        printf("  ");
    }
    for(int i=1;i<=total-count+1;i++)
    {
        printf("%2d",i%10);
    }
    for(int i=total-count;i>=1;i--)
    {
        printf("%2d",i%10);
    }
    printf("\n");
    print(count-1,total);
}

int main()
{
    int n;
    scanf("%d", &n);
    print(n,n);
    return 0;
}