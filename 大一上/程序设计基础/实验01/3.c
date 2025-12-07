#include <stdio.h>

int main()
{
    double cin;
    double cout;
    scanf("%lf", &cin);
    cout=(cin*9/5)+32;
    printf("%.3lf", cout);
    return 0;
}