#include <stdio.h>

int strlen(char *str)
{
    int count=0;
    while(*str!='\0')
    {
        count++;
        str++;
    }
    return count;
}

int main()
{
    char str[300];
    fgets(str,256,stdin);
    char *p=str;
    printf("%d",strlen(p));
    return 0;
}