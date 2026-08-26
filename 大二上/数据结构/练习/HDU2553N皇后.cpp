#include <iostream>
using namespace std;
bool isValid(int ans[], int n, int k, int i)
{
    for (int j = 1; j < k; j++)
    {
        if (ans[j] == i || abs(ans[j] - i) == abs(j - k))
            return false;
    }
    return true;
}
int cnt = 0;
int ultimateans[11] = {0};
bool ultimate[11] = {false};
int ans[11] = {0};
void Nqueens(int ans[], int n, int k)
{
    if (k > n)
    {
        cnt++;
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if (isValid(ans, n, k, i))
        {
            ans[k] = i;
            Nqueens(ans, n, k + 1);
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    while (n != 0)
    {
        if (ultimate[n])
        {
            cnt = ultimateans[n];
        }
        else
        {
            Nqueens(ans, n, 1);
            ultimate[n] = true;
            ultimateans[n] = cnt;
        }
        cout << cnt << '\n';
        cnt = 0;
        cin >> n;
        for(int i = 1; i <= n; i++)
        {
            ans[i] = 0;
        }
    }
    return 0;
}