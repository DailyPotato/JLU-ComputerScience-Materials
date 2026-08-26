#include<iostream>
#include<vector>
using namespace std;
unsigned long long func(int n,int k)
{
    unsigned long long ans=1;
    if(k==0||k==n)return 1;
    if(k>n/2)k=n-k;
    for(int i=n-k+1,j=1;i<=n;i++,j++)
    {
        ans=ans*i/j;
    }
    return ans;
}

int main()
{
    int n,k;
    cin>>n>>k;
    while(!(n==0&&k==0))
    {
        cout<<func(n,k)<<endl;
        cin>>n>>k;
    }
    return 0;
}