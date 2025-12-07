#include <stdio.h>
#include <stdbool.h>

struct student
{
    char name[20];
    unsigned int score;
};


int main()
{
    int n;
    scanf("%d",&n);
    struct student s[n];
    bool judge[10]={false};
    for(int i=0;i<n;i++)
    {
        scanf("%s%d",s[i].name,&s[i].score);
        if(s[i].score<60)judge[i]=true;
    }
    for(int i=0;i<n;i++)
    {
        if(judge[i])
        {
            printf("%s %d ",s[i].name,s[i].score);
        }
    }
    return 0;
}