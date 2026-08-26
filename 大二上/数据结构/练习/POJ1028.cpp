#include<iostream>
#include<vector>
#include<stack>
using namespace std;

int main()
{
    stack<string>backward,forward;
    string command;
    string now="http://www.acm.org/";
    cin>>command;
    while(command!="QUIT")
    {
        if(command=="VISIT")
        {
            backward.push(now);
            while(!forward.empty())
            {
                forward.pop();
            }
            cin>>now;
            cout<<now<<endl;
        }
        if(command=="BACK")
        {
            if(!backward.empty())
            {
                forward.push(now);
                now=backward.top();
                backward.pop();
                cout<<now<<endl;
            }
            else
            {
                cout<<"Ignored"<<endl;
            }
        }
        if(command=="FORWARD")
        {
            if(!forward.empty())
            {
                backward.push(now);
                now=forward.top();
                forward.pop();
                cout<<now<<endl;
            }
            else
            {
                cout<<"Ignored"<<endl;
            }
        }
        if(command=="QUIT")
        {
            break;
        }
        cin>>command;
    }
    return 0;
}