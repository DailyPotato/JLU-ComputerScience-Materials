#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> visited(6, vector<int>(6, 0));
int n,m,t,fx,fy;
int x,y;
int cnt=0;
pair<int,int> dir[4] = {{0,1},{0,-1},{1,0},{-1,0}};
void func(int t,int sx,int sy,int x,int y)
{
    if(x==fx && y==fy)
    {
        cnt++;
        return;
    }
    for(int i=0;i<4;i++)
    {
        int dx=x+dir[i].first;
        int dy=y+dir[i].second;
        if(dx>0&&dx<=n&&dy>0&&dy<=m&&visited[dx][dy]==0)
        {
            visited[dx][dy] = 1;
            func(t, sx, sy, dx, dy);
            visited[dx][dy] = 0;
        }
        else    continue;
    }
    
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>n>>m>>t;
    int sx,sy;
    cin>>sx>>sy>>fx>>fy;
    for(int i=0;i<t;i++)
    {
        int tempx,tempy;
        cin>>tempx>>tempy;
        visited[tempx][tempy] = 1;
    }
    x=sx,y=sy;
    visited[sx][sy]=1;
    func(t, sx, sy, x, y);
    cout<<cnt<<endl;
    return 0;
}