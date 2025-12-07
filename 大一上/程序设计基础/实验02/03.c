#include <stdio.h>

int main()
{
    int num[6];
    for(int i=0;i<6;i++)
    {
        scanf("%d",&num[i]);
    }
    int total=0;
    for(int i=1;i<6;i++)
    {
        if(num[i]%num[0]==0)
        total+=num[i];
    }
    printf("%d",total);
    return 0;
}