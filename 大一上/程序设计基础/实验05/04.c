#include <stdio.h>
#include <string.h>
char *str_delete(char *str,int v,int w)
{
    int i=v+w-1;
    while(str[i]!='\0')
    {
        str[i-w]=str[i];
        i++;
    }
    str[i-w]='\0';
    return str;
}

int main()
{
    int v,w;
    scanf("%d%d",&v,&w);
    getchar();
    char str[300];
    gets(str);
    char *p=str_delete(str,v,w);
    printf("%s",p);
    return 0;
}