#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<bool> visit;
//반례
/*
5 5
1 2
2 4
2 3
3 4
4 5
*/

int dfs(int x, int depth)
{
    if (depth == 4)
    {
        return depth;
    }
    visit[x] = true;
    int ret = 0;
    for (int i = 0; i < adj[x].size(); i++)
    {
        int next = adj[x][i];
        if (visit[next])
            continue;
        ret = max(ret, dfs(next, depth + 1));
        if (ret >= 4)
            return ret;
    }
    visit[x] = false; //사이클 고려(분기노드에서 재시도 하여 가능함)
    return depth;
}

int solve(int totalCount)
{
    int ret = 0;
    for (int i = 0; i < totalCount; i++)
    {
        visit = vector<bool>(totalCount);
        ret = max(ret, dfs(i, 0));
    }
    return ret;
}

int main()
{
    int totalCount, relationCount;
    cin >> totalCount >> relationCount;
    adj.resize(totalCount);
    for (int i = 0; i < relationCount; i++)
    {
        int f1, f2;
        cin >> f1 >> f2;
        adj[f1].push_back(f2);
        adj[f2].push_back(f1);
    }
    int ret = solve(totalCount);
    cout << (ret >= 4 ? 1 : 0) << "\n";
    return 0;
}