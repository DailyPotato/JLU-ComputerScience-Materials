#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char str[100];
    gets(str);
    for(int i=0;i<strlen(str);i++)
    {
        if(!isdigit(str[i]))
        {
            printf("NULL");
            return 0;
        }
    }
    if (strlen(str) == 1)
    {
        printf("%c", str[0]);
        return 0;
    }
    if (str[0] == '0')
    {
        printf("NULL");
        return 0;
    }
    int flag = 0;
    for (int i = strlen(str) - 1; i >= 0; i--)
    {
        if (str[i] == '0' && flag == 0)
            continue;
        flag = 1;
        printf("%c", str[i]);
    }
    return 0;
}