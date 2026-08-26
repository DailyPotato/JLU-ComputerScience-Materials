#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int r, c;
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
vector<vector<bool>> map(50, vector<bool>(50));
vector<vector<int>>dist(50, vector<int>(50, -1));
int bfs()
{
    queue<pair<int, int>> Q;
    Q.push({ 1,1 });
    map[1][1] = 0;
    dist[1][1] = 1;
    while (!Q.empty())
    {
        pair<int, int>temp = Q.front();
        Q.pop();
        if (temp.first == r  && temp.second == c )return dist[temp.first][temp.second];
        for (int i = 0; i < 4; i++)
        {
            int nx = temp.first + dx[i];
            int ny = temp.second + dy[i];
            if (!(nx >= 1 && nx <= r && ny >= 1 && ny <= c))continue;
            if (map[nx][ny] == 1)
            {
                map[nx][ny] = 0;
                dist[nx][ny] = dist[temp.first][temp.second] + 1;
                Q.push({ nx, ny });
            }
        }
    }
}

int main()
{

    cin >> r >> c;
    for (int i = 1; i <= r; i++)
    {
        string temp;
        cin >> temp;
        for (int j = 1; j <= c; j++)
        {
            if (temp[j - 1] == '.')
                map[i][j] = 1;
            else
                map[i][j] = 0;
        }
    }
    cout << bfs() << endl;
    return 0;
}