#include <stdio.h>

void putqueen(int row, int column, int queen_pos[16][16], int attack[16][16], int n)
{
    static const int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    static const int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};
    
    queen_pos[row][column] = 1;
    
    // 标记皇后的攻击范围
    for (int i = 0; i < 8; i++)
    {
        for (int j = 1; j < n; j++)  // j从1开始，因为当前位置已经有皇后了
        {
            int nx = row + j * dx[i];
            int ny = column + j * dy[i];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < n)
            {
                attack[nx][ny] = 1;
            }
            else
            {
                break;  // 超出边界，这个方向不需要继续
            }
        }
    }
}

void backtrack(int row, int queen_pos[16][16], int attack[16][16], int *count, int n)
{
    if (row == n)
    {
        (*count)++;
        return;
    }

    for (int column = 0; column < n; column++)
    {
        if (attack[row][column] == 0)
        {
            // 保存当前状态
            int temp_queen[16][16];
            int temp_attack[16][16];
            
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    temp_queen[i][j] = queen_pos[i][j];
                    temp_attack[i][j] = attack[i][j];
                }
            }
            
            // 放置皇后并递归
            putqueen(row, column, queen_pos, attack, n);
            backtrack(row + 1, queen_pos, attack, count, n);
            
            // 恢复状态
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    queen_pos[i][j] = temp_queen[i][j];
                    attack[i][j] = temp_attack[i][j];
                }
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int attack[16][16];
    int queen_pos[16][16];
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            attack[i][j] = 0;
            queen_pos[i][j] = 0;
        }
    }
    
    int count = 0;
    backtrack(0, queen_pos, attack, &count, n);
    printf("%d", count);
    return 0;
}