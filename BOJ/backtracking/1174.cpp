#include <iostream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

vector<string> decreaseNums;

void makeDecreaseNums()
{
    vector<vector<string>> before(10);
    for (int i = 0; i < before.size(); i++)
    {
        before[i] = vector<string>(1, string(1, i + '0'));
        decreaseNums.push_back(before[i][0]);
    }
    int curDigit = 1;
    while (curDigit <= 10)
    {
        vector<vector<string>> cur(10);
        for (int i = curDigit; i <= 9; i++)
        {
            for (int j = curDigit-1; j < i; j++)
            {
                for (int k = 0; k < before[j].size(); k++)
                {
                    string newString = string(1, i + '0') + before[j][k];
                    cur[i].push_back(newString);
                    decreaseNums.push_back(newString);
                }
            }
        }
        before = cur;
        curDigit++;
    }
}

int main()
{
    int n;
    cin >> n;
    makeDecreaseNums();
    if (n > decreaseNums.size())
        cout << -1 << "\n";
    else
        cout << decreaseNums[n - 1] << "\n";
    return 0;
}