#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

int evalRPN(vector<string> &tokens)
{
    stack<int> stk;
    for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++)
    {
        if (((*it)[0] >= '0' && (*it)[0] <= '9') || ((*it)[0] == '-' && (*it).length() > 1))
        {
            stk.push(stoi(*it));
        }
        else if (*it == "+")
        {
            int temp = stk.top();
            stk.pop();
            temp += stk.top();
            stk.pop();
            stk.push(temp);
        }
        else if (*it == "-")
        {
            int temp = stk.top();
            stk.pop();
            temp = stk.top() - temp;
            stk.pop();
            stk.push(temp);
        }
        else if (*it == "*")
        {
            int temp = stk.top();
            stk.pop();
            temp *= stk.top();
            stk.pop();
            stk.push(temp);
        }
        else if (*it == "/")
        {
            int temp = stk.top();
            stk.pop();
            temp = stk.top() / temp;
            stk.pop();
            stk.push(temp);
        }
    }
    return stk.top();
}

int main()
{
    vector<string> tokens;
    string s;
    cin>>s;
    int temp=0;
    for(int i=0;i<s.size();i++)
    {
        if(s[i] == '+')
        {
            tokens.push_back("+");
        }
        else if(s[i] == '-')
        {
            tokens.push_back("-");
        }
        else if(s[i] == '*')
        {
            tokens.push_back("*");
        }
        else if(s[i] == '/')
        {
            tokens.push_back("/");
        }
        else if(s[i] == '.')
        {
            tokens.push_back(to_string(temp));
            temp = 0;
        }
        else if(s[i] == '@')break;
        else
        {
            temp = temp * 10 + (s[i] - '0');
        }
    }
    cout<<evalRPN(tokens)<<endl;
    return 0;
}