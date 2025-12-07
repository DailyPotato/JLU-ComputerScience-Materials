#include <stdio.h>

int main()
{
    char a;
    scanf("%c", &a);
    printf("%c%c%c", (a-1),a,(a+1));
    return 0;
}