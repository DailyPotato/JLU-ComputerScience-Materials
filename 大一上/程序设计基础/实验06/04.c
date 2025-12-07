#include <stdio.h>

struct student
{
    char name[20];
    unsigned int score1;
    unsigned int score2;
};

int main()
{
    int n;
    scanf("%d",&n);
    struct student s[n];
    for(int i=0;i<n;i++)
    {
        scanf("%s%d%d",s[i].name,&s[i].score1,&s[i].score2);
    }
    for(int i=0;i<n;i++)
    {
        printf("%s %d ",s[i].name,s[i].score1+s[i].score2);
    }
    return 0;
}