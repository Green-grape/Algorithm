#include <iostream>
#include <vector>

using namespace std;

const int INF = 987654321;

vector<vector<int>> count;

void precal(string s)
{
    count = vector<vector<int>>(26, vector<int>());
    for (int i = 0; i < s.size(); i++)
    {
        count[s[i] - 'a'].push_back(i);
    }
}

pair<int, int> solve(string s, int include)
{
    int includeN = INF, includeNWithSameEnd = -1;
    for (int i = 0; i < count.size(); i++)
    {
        for (int j = 0; j + include - 1 < count[i].size(); j++)
        {
            includeN = min(includeN, count[i][j + include - 1] - count[i][j] + 1);
            includeNWithSameEnd = max(includeNWithSameEnd, count[i][j + include - 1] - count[i][j] + 1);
        }
    }
    return make_pair(includeN, includeNWithSameEnd);
}

int main()
{
    int testCase;
    cin >> testCase;
    while (testCase--)
    {
        string s;
        int include;
        cin >> s >> include;
        precal(s);
        pair<int, int> ret = solve(s, include);
        if (ret.second == -1)
            cout << -1 << "\n";
        else
            cout << ret.first << " " << ret.second << "\n";
    }
    return 0;
}