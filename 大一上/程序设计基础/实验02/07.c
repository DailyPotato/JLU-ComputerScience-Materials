#include <stdio.h>

int main()
{
    int num;
    scanf("%d", &num);
    int judge[3]={0,0,0};
    if(num%3==0)judge[0]=1;
    if(num%5==0)judge[1]=1;
    if(num%7==0)judge[2]=1;
    if(judge[0]&&(judge[1]||judge[2]))printf("3,");
    else if(judge[0])printf("3");
    if(judge[1]&&judge[2])printf("5,");
    else if(judge[1])printf("5");
    if(judge[2])printf("7");
    if(!(judge[0]||judge[1]||judge[2]))printf("NULL");
    return 0;
}