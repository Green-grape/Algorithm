#include <iostream>
#include <vector>

using namespace std;

int boardSize;

/** 지금 상황이 board이고 y부터 퀸을 놓을때 퀸이 서로 공격할수 없게 놓을수 있는 경우의 수는?*/
int countNQueen(vector<pair<int, int>> &queens, int y)
{
    int n = boardSize;
    if (y == n)
        return 1;
    int ret = 0;
    vector<int> row(n);
    for (int q = 0; q < queens.size(); q++)
    {
        int curY = queens[q].first, curX = queens[q].second;
        row[curX] = 1;
        if (0 <= curX + y - curY && curX + y - curY < n)
            row[curX + y - curY] = 1;
        if (0 <= curX - y + curY && curX - y + curY < n)
            row[curX - y + curY] = 1;
    }
    for (int i = 0; i < n; i++)
    {
        if (row[i] == 0)
        {
            queens.push_back(make_pair(y, i));
            ret += countNQueen(queens, y + 1);
            queens.pop_back();
        }
    }
    return ret;
}

int main()
{
    cin >> boardSize;
    vector<pair<int, int>> queens;
    cout << countNQueen(queens, 0) << "\n";
    return 0;
}