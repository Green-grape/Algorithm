#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> board;
vector<vector<bool>> isVisit;
int adjEven[][2] = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {-1, 1}, {1, 1}};
int adjOdd[][2] = {
    {-1, -1}, {1, -1}, {0, -1}, {0, 1}, {-1, 0}, {1, 0}};
int height, width;

bool isInRange(int y, int x)
{
    if (0 <= y && y < height && 0 <= x && x < width)
        return true;
    return false;
}

void findOuter(int y, int x) //건물 외부를 찾음
{
    board[y][x] = 2;
    for (int i = 0; i < 6; i++)
    {
        int nextY = y + (y % 2 ? adjOdd[i][0] : adjEven[i][0]), nextX = x + (y % 2 ? adjOdd[i][1] : adjEven[i][1]);
        if (isInRange(nextY, nextX) && board[nextY][nextX] != 1 && !isVisit[nextY][nextX])
        {
            isVisit[nextY][nextX] = true;
            findOuter(nextY, nextX);
        }
    }
}

int getTotalLength(int startY, int startX) // startY, startX부터 시작하는 건물의 조명길이 반환
{
    int ret = 0;
    if (isVisit[startY][startX])
        return ret;
    isVisit[startY][startX] = true;
    //cout << startY << " " << startX << "\n";
    for (int i = 0; i < 6; i++)
    {
        int nextY = startY + ((startY % 2 == 1) ? adjOdd[i][0] : adjEven[i][0]), nextX = startX + ((startY % 2 == 1) ? adjOdd[i][1] : adjEven[i][1]);
        if ((!isInRange(nextY, nextX)) || (board[nextY][nextX] == 2))
        {
            ret++; //외부
            continue;
        }
        if (isInRange(nextY, nextX) && (board[nextY][nextX] == 1))
        {
            ret += getTotalLength(nextY, nextX);
        }
    }
    return ret;
}

int main()
{
    cin >> width >> height;
    board = vector<vector<int>>(height, vector<int>(width));
    isVisit = vector<vector<bool>>(height, vector<bool>(width, false));
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            cin >> board[j][i];
        }
    }
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            if (board[j][i] == 1)
                continue;
            if (i == 0 || j == 0 || j == height - 1 || i == width - 1)//확실히 밖인 부분 부터 검색
                findOuter(j, i);
        }
    }
    // for (int j = 0; j < height; j++)
    // {
    //     for (int i = 0; i < width; i++)
    //     {
    //         cout << isInternal[j][i] << " ";
    //     }
    //     cout << "\n";
    // }
    isVisit = vector<vector<bool>>(height, vector<bool>(width));
    int ret = 0;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            if ((board[j][i] == 1) && !isVisit[j][i])
            {
                ret += getTotalLength(j, i);
            }
        }
    }
    cout << ret << "\n";
    return 0;
}