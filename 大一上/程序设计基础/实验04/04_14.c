#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int arr[5][5];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<3;j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    int yu_total=0,shu_total=0,ying_total=0;
    for(int i=0;i<n;i++)
    {
        yu_total+=arr[i][0];
        shu_total+=arr[i][1];
        ying_total+=arr[i][2];
    }
    printf("%d %d %d \n%d %d %d ", yu_total, shu_total, ying_total,yu_total/n, shu_total/n, ying_total/n);
}