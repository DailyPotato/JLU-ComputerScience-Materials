#include <stdio.h>

int main()
{
    int time;
    scanf("%d", &time);
    time%=86400;
    int hour=time/3600;
    int minute=(time%3600)/60;
    int second=time%60;
    printf("%02d:%02d:%02d",hour,minute,second);
    return 0;
}