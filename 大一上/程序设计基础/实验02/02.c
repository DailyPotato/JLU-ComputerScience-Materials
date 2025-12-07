#include <stdio.h>

int main()
{
    char str[100];
    int cou[5];
    for(int i=0;i<5;i++)
    {
        cou[i]=0;
    }
    char temp;
    temp=getchar();
    int count=0;
    while(temp!='@')
    {
        str[count++]=temp;

        switch (temp)
        {
        case 123:
            cou[0]++;
            break;
        case 125:
            cou[1]++;
            break;
        case 91:
            cou[2]++;
            break;
        case 93:
            cou[3]++;
            break;
        case 40:
            cou[4]++;
            break;
        case 41:
            cou[5]++;
            break;
        default:
            break;
        }
        temp=getchar();
    }
    if(cou[0]!=cou[1])printf("{}");
    if(cou[2]!=cou[3])printf("[]");
    if(cou[4]!=cou[5])printf("()");
    if(cou[0]==cou[1]&&cou[0]==cou[2]&&cou[0]==cou[3]&&cou[0]==cou[4]&&cou[0]==cou[5])printf("NULL");

    return 0;
}