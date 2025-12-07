#include <stdio.h>
#include <string.h>
void count(char *str,int *upper,int *lower,int *space,int *num,int *other);
int main()
{
    char str[300];
    fgets(str,256,stdin);
    int upper=0,lower=0,space=0,num=0,other=0;
    count(str,&upper,&lower,&space,&num,&other);
    printf("%d %d %d %d %d",upper,lower,space,num,other);
    return 0;
}

void count(char *str,int *upper,int *lower,int *space,int *num,int *other)
{
    while(*str!='\0')//bdz学习通测试的时候有没有换行符，开放的时候测试一下
    {
        if(*str>='A'&&*str<='Z')
        {
            (*upper)++;
        }
        else if(*str>='a'&&*str<='z')
        {
            (*lower)++;
        }
        else if(*str==' ')
        {
            (*space)++;
        }
        else if(*str>='0'&&*str<='9')
        {
            (*num)++;
        }
        else
        {
            (*other)++;
        }
        str++;
    }
}