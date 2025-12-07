#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int arr[100];
    int check[100];
    int num = 1;
    scanf("%d", &arr[0]);
    check[0] = arr[0];
    for (int i = 1; i < n; i++)
    {
        int judge = 0;
        scanf("%d", &arr[i]);
        for(int j = 0; j <num; j++)
        {
            if(arr[i] == check[j])
            {
                judge = 1;
                break;
            }  
        }
        if(judge == 0)
        {
            check[num++] = arr[i];
        }
    }
    for(int i = 0; i < num; i++)
    {
        printf("%d ", check[i]);
    }
    return 0;
}