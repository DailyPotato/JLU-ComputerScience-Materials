#include <stdio.h>

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    if(n==1)
    {
        if(m>65)
        {
            if(m>70)
            {
                printf("70");
            }
            else printf("50");
        }
        else printf("NULL");
    }
    else if(n==2)
    {
        if(m>60)
        {
            if(m>65)
            {
                printf("70");
            }
            else printf("45");
        }
        else printf("NULL");
    }
}