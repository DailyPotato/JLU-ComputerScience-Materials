#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    char str[110][300];
    int t = 0, f = 0, judge = 0;
    for (int i = 0; i < n; i++)
    {
        gets(str[i]);
    }
    for (int i = 0; i < n; i++)
    {
        if (!((isalpha(str[i][0])) || str[i][0] == '_'))
        {
            f++;
            continue;
        }
        for (int j = 1; (size_t)j < strlen(str[i]); j++)
        {

            if (!(isalnum(str[i][j]) || str[i][j] == '_'))
            {
                judge = 1;
                f++;
                break;
            }
        }
        if (judge == 0)
        {
            t++;
        }
        judge = 0;
    }
    printf("Valid:%d\nInvalid:%d", t, f);
    return 0;
}