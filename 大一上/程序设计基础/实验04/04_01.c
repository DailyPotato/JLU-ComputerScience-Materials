#include <stdio.h>
#include <stdlib.h>

char stack[1001];
char temp;
int top = -1;

char pop(void)
{
    if(top == -1)
    {
        printf("NO");
        exit(0);
    }
    return stack[top--];
}

void check(char c,char ch)
{
    if(c!= ch)
    {
        printf("NO");
        exit(0);
    }
}


int main()
{
    while((temp=getchar())!='@')
    {
        switch (temp)
        {
            case '(':
            case '[':
            case '{':
                top++;
                stack[top] = temp;
                break;
            case ')':check(pop(),'(');break;
            case ']':check(pop(),'[');break;
            case '}':check(pop(),'{');break;
        }
    }
    if(top == -1)printf("YES");
    else printf("NO");
    return 0;
}