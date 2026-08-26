#include<iostream>
#include<vector>
using namespace std;



class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int sizem = obstacleGrid.size();
        int sizen = obstacleGrid[0].size();
        vector<vector<int>> dp(sizem,vector<int>(sizen,0));
        if(obstacleGrid[0][0]==1)
        {
            return 0;
        }
        dp[0][0]=1;
        for(int i=1;i<sizen;i++)
        {
            dp[0][i]=dp[0][i-1]*(1-obstacleGrid[0][i]);
        }
        for(int i=1;i<sizem;i++)
        {
            dp[i][0]=dp[i-1][0]*(1-obstacleGrid[i][0]);
        }
        for(int i=1;i<sizem;i++)
        {
            for(int j=1;j<sizen;j++)
            {
                dp[i][j]=(dp[i-1][j]+dp[i][j-1])*(1-obstacleGrid[i][j]);
            }
        }
        return dp[sizem-1][sizen-1];
    }
};

int main()
{
    vector<vector<int>> obstacleGrid={{0,0,0},{0,1,0},{0,0,0}};
    Solution s;
    cout<<s.uniquePathsWithObstacles(obstacleGrid)<<endl;
    return 0;
}