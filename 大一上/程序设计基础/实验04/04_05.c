#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d",&n);
    int *arr=(int *)malloc(n*sizeof(int));
    int i=0,j=n-1;
    int temp;
    while(j-i!=-1)
    {
        scanf("%d",&temp);
        if(temp==0)
        {
            arr[j]=temp;
            j--;
        }
        else
        {
            arr[i]=temp;
            i++;
        }
    }
    for(int k=0;k<n;k++)
    {
        printf("%d ",arr[k]);
    }
    free(arr);
    return 0;
}