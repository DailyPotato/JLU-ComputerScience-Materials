#include <stdio.h>

int main()
{
    for(int i=1;i<=100000;i++)
    {
        int temp=7*i;
        if(temp%3==2&&temp%5==4&&temp%2==1)
        {
            printf("%d ",temp);
            break;
        }
    }
}