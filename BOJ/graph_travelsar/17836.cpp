#include <iostream>
#include <vector>
#include <queue>

//복습

using namespace std;

vector<vector<int>> board;
vector<vector<int>> dis;
vector<vector<bool>> visit;
int adj[][2] = {
    {-1, 0}, {1, 0}, {0, 1}, {0, -1}};
const int INF = 987654321;
int height, width;
int sHeight, sWidth;

bool isInRange(int y, int x)
{
    return (0 <= y && y < height && 0 <= x && x < width);
}

void bfs(int startY, int startX)
{
    queue<pair<int, int>> q;
    q.push(make_pair(startY, startX));
    visit[startY][startX] = true;
    dis[startY][startX] = 0;
    int ret = 0;
    while (!q.empty())
    {
        pair<int, int> cur = q.front();
        int curY = cur.first;
        int curX = cur.second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nextY = curY + adj[i][0], nextX = curX + adj[i][1];
            if (isInRange(nextY, nextX) && board[nextY][nextX] != 1 && !visit[nextY][nextX])
            {
                visit[nextY][nextX] = true;
                dis[nextY][nextX] = dis[curY][curX] + 1;
                q.push(make_pair(nextY, nextX));
            }
        }
    }
}

int getMinTime()
{
    dis = vector<vector<int>>(height, vector<int>(width));
    visit = vector<vector<bool>>(height, vector<bool>(width));
    bfs(0, 0);
    int noSwordTime = dis[height - 1][width - 1];
    // cout << noSwordTime << "\n";
    if (noSwordTime == 0)
    {
        if (height != 1 || width != 1)
            noSwordTime = INF;
    }
    int swordTime = dis[sHeight][sWidth];
    if (swordTime == 0)
    {
        if (!(sHeight == 0 && sWidth == 0))
            swordTime = INF;
    }
    swordTime += (height - 1 - sHeight + width - 1 - sWidth);
    return min(noSwordTime, swordTime);
}

int main()
{
    int timeLimit;
    cin >> height >> width >> timeLimit;
    board.resize(height);
    for (int y = 0; y < height; y++)
    {
        board[y].resize(width);
        for (int x = 0; x < width; x++)
        {
            cin >> board[y][x];
            if (board[y][x] == 2)
            {
                sHeight = y;
                sWidth = x;
            }
        }
    }
    int minTime = getMinTime();
    if (minTime <= timeLimit)
        cout << minTime << "\n";
    else
        cout << "Fail"
             << "\n";
    return 0;
}