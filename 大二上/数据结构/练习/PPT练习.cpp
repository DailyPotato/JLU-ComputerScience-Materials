#include <iostream>
#include <vector>
using namespace std;
vector<char> ans;
vector<char>temp;
char s[28] = {'{', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
void print(vector<char> ans)
{
    cout << '{';
    for (int i = 0; i < ans.size()-1; i++)
    {
        cout << ans[i]<<',';
    }
    cout << ans[ans.size() - 1];
    cout << '}' << endl;
}
void set(int index, int max,vector<char>&ans)
{
    if (index == max)
    {
        return;
    }
    for (int i = index+1; i < max; i++)
    {
        ans.push_back(s[i]);
        print(ans);
        set(i, max, ans);
        ans.pop_back();
    }
}

int main()
{
    int n;
    cin >> n;
    set(0, n+1,ans);
    return 0;
}