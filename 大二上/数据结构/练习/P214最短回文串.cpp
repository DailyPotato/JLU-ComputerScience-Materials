#include <iostream>
#include <string>
#include<algorithm>
using namespace std;
class Solution
{
public:
    int next[50001];
    void buildNext(string s)
    {
        int k = next[0] = -1;
        int m = s.size();
        for (int i = 0; i < m - 1; i++)
        {
            while (k >= 0 &&s[k] != s[i])
            {
                k = next[k];
            }
            next[i + 1] = ++k;
        }
    }
    string shortestPalindrome(string s)
    {
        int m = s.size();
        if(m<=1)return s;
        string rs = s;
        reverse(rs.begin(), rs.end());
        buildNext(s);
        int j=0;
        for (int i = 0; i < m; i++)
        {
            while (j >= 0 && s[j] != rs[i])
            {
                j = next[j];
            }
            j++;
        }
        return rs.substr(0, m - j - 1) + s;
    }
};

int main()
{
    Solution solution;
    string s;
    cin >> s;
    cout << solution.shortestPalindrome(s) << endl;
    return 0;
}