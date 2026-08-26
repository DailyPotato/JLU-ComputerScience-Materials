#include<iostream>
#include<vector>
#include<stack>
using namespace std;

bool judge(int n,vector<int>&v)
{
    stack<int> s;
    int j=1;
    for(int i=0;i<n;i++)
    {
        while(s.empty() || s.top()!=v[i])
        {
            if(s.size()>=n) return false;
            s.push(j++);
        }
        s.pop();
    }
    return true;
}