#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> board;
vector<vector<int>> visit;
vector<vector<vector<int>>> adj;
int open[][2] = {
    {1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n, l, r;

bool isInRange(int y, int x)
{
    return (0 <= y && y < n && 0 <= x && x < n);
}

int dfs(int y, int x, vector<pair<int, int>> &path)
{
    if (visit[y][x])
        return 0;
    visit[y][x] = 1;
    path.push_back(make_pair(y, x));
    int ret = board[y][x];
    for (int i = 0; i < adj[y][x].size(); i++)
    {
        int nextY = y + open[adj[y][x][i]][0], nextX = x + open[adj[y][x][i]][1];
        ret += dfs(nextY, nextX, path);
    }
    return ret;
}

int getMoveCount()
{
    int ret = 0;
    while (true)
    {
        bool isEnd = true;
        visit = vector<vector<int>>(n, vector<int>(n));
        adj = vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>()));
        for (int y = 0; y < n; y++)
        {
            for (int x = 0; x < n; x++)
            {
                for (int k = 0; k < 4; k++)
                {
                    int nextY = y + open[k][0], nextX = x + open[k][1];
                    if (isInRange(nextY, nextX) && l <= abs(board[nextY][nextX] - board[y][x]) && abs(board[nextY][nextX] - board[y][x]) <= r)
                    {
                        adj[y][x].push_back(k);
                        isEnd = false;
                    }
                }
            }
        }
        if (isEnd)
            break;
        for (int y = 0; y < n; y++)
        {
            for (int x = 0; x < n; x++)
            {
                if (!visit[y][x])
                {
                    vector<pair<int, int>> path;
                    int avr = dfs(y, x, path) / path.size();
                    for (int i = 0; i < path.size(); i++)
                    {
                        board[path[i].first][path[i].second] = avr;
                    }
                }
            }
        }
        // for (int y = 0; y < n; y++)
        // {
        //     for (int x = 0; x < n; x++)
        //     {
        //         cout << board[y][x] << " ";
        //     }
        //     cout << "\n";
        // }
        ret++;
    }
    return ret;
}

int main()
{
    cin >> n >> l >> r;
    board.resize(n);
    for (int i = 0; i < n; i++)
    {
        board[i].resize(n);
        for (int j = 0; j < n; j++)
        {
            cin >> board[i][j];
        }
    }
    int ret = getMoveCount();
    cout << ret << "\n";
    return 0;
}