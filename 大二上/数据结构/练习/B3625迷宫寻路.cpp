#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, m;
pair<int,int>dir[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
vector<vector<char>> grid(101, vector<char>(101, '.'));
bool backtracking(int x, int y)
{
    if (x == n && y == m)return true;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dir[i].first;
        int ny = y + dir[i].second;
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && grid[nx][ny] == '.')
        {
            grid[nx][ny] = '#';
            if (backtracking(nx, ny))return true;
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        string temp;
        cin >> temp;
        for (int j = 1; j <= m; j++)
        {
            grid[i][j] = temp[j-1];
        }
    }
    grid[1][1] = '#';
    if (backtracking(1, 1)) cout << "Yes";
    else cout << "No";

    return 0;
}