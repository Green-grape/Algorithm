#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

const int INF = 987654321;

vector<vector<int>> board;
vector<vector<int>> sumTo;

void makeSumTo(int n, int m)
{
    sumTo = board;
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < m; x++)
        {
            if (y > 0)
                sumTo[y][x] += sumTo[y - 1][x];
            if (x > 0)
                sumTo[y][x] += sumTo[y][x - 1];
            if (x > 0 && y > 0)
                sumTo[y][x] -= sumTo[y - 1][x - 1];
        }
    }
}

int getSum(int y1, int x1, int y2, int x2)
{
    int ret = sumTo[y2][x2];
    if (y1 >= 1)
        ret -= sumTo[y1 - 1][x2];
    if (x1 >= 1)
        ret -= sumTo[y2][x1 - 1];
    if (y1 >= 1 && x1 >= 1)
        ret += sumTo[y1 - 1][x1 - 1];
    return ret;
}

int getMaxSubMatrix(int n, int m)
{
    makeSumTo(n, m);
    int ret = -INF;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int startY = 0; startY <= i; startY++)
            {
                for (int startX = 0; startX <= j; startX++)
                {
                    ret = max(ret, getSum(startY, startX, i, j));
                }
            }
        }
    }
    return ret;
}

int main()
{
    int n, m;
    cin >> n >> m;
    board.resize(n);
    for (int i = 0; i < n; i++)
    {
        board[i].resize(m);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }
    cout << getMaxSubMatrix(n, m) << "\n";
    return 0;
}