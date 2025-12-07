#include <stdio.h>

struct teacher
{
    char name[20];
    int gender;
    int age;
};

void print_teacher(struct teacher *t,int n)
{
    int temp=n/2;
    printf("%s ",t[temp].name);
    if(t[temp].gender==0)printf("Female");
    else printf("Male");
    printf(" %d",t[temp].age);
}

int main()
{
    struct teacher t[100];
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%s%d%d",t[i].name,&t[i].gender,&t[i].age);
    }
    print_teacher(t,n);
    return 0;
}