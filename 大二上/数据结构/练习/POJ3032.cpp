#include<iostream>
#include<vector>
#include<queue>

using namespace std;

queue<int> func(int n)
{
    queue<int> q;
    q.push(n);
    for(int i=n-1;i>0;i--)
    {
        q.push(i);
        for(int j=i;j>0;j--)
        {
            int temp=q.front();
            q.pop();
            q.push(temp);
        }
    }
    return q;
}

void print(queue<int>&q)
{
    if(q.empty())return;
    int temp=q.front();
    q.pop();
    print(q);
    cout<<temp<<" ";
}

int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        int m;
        cin>>m;
        queue<int> q=func(m);
        print(q);
        cout<<endl;
    }
    return 0;
}