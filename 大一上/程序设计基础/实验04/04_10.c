#include <stdio.h>
#include <string.h>

int main()
{
    char s[256];
    fgets(s, 256, stdin);
    for(int i=strlen(s)-1;i>=0;i--)printf("%c",s[i]);
    return 0;
}