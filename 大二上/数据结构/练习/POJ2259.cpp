#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int num = 1;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t != 0)
    {
        cout << "Scenario #" << num << '\n';
        num++;
        int cnt = 1;
        vector<int> arr(1000000);
        for (int i = 0; i < t; i++)
        {
            int temp;
            cin >> temp;
            for (int j = 0; j < temp; j++)
            {
                int temp2;
                cin >> temp2;
                arr[temp2] = i + 1;
            }
        }
        string temp3;
        cin >> temp3;
        queue<int> teamqueue;
        vector<queue<int>> teamqueues(t + 1);
        while (temp3 != "STOP")
        {
            if (temp3 == "ENQUEUE")
            {
                int temp4;
                cin >> temp4;
                int teamnum = arr[temp4];
                if(teamqueues[teamnum].empty())
                {
                    teamqueue.push(teamnum);
                }
                teamqueues[teamnum].push(temp4);
            }
            else if (temp3 == "DEQUEUE")
            {
                if(!teamqueues[teamqueue.front()].empty())
                {
                    cout << teamqueues[teamqueue.front()].front() << '\n';
                    teamqueues[teamqueue.front()].pop();
                }
                else
                {
                    teamqueue.pop();
                    cout<< teamqueues[teamqueue.front()].front() << '\n';
                    teamqueues[teamqueue.front()].pop();
                }
            }
            cin >> temp3;
        }
        cout << '\n';
        cin >> t;
    }
    return 0;
}