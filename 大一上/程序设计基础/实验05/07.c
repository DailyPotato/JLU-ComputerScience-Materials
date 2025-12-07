#include <stdio.h>
#include <ctype.h>

int main()
{
    char str[100];
    gets(str);
    int i = 0;
    int count = 0;
    int judge = 0;
    while (str[i] != '\0')
    {
        if (isalpha(str[i]))
        {
            judge = 1;
        }
        if (!isalpha(str[i]) && judge == 1)
        {
            count++;
            judge = 0;
        }
        i++;
    }
    if (!isalpha(str[i]) && judge == 1)
    {
        count++;
    }
    printf("%d", count);
    return 0;
}