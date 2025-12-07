#include <stdio.h>
int str(void)
{
    if(getchar()==EOF)return 0;
    return 1+str();
}

int main()
{
    int n=str();
    printf("%d",n);
    return 0;
}