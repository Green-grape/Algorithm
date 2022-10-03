#include <iostream>
#include <vector>

using namespace std;

const int INF = 987654321;

int solve(const vector<int> &reward, vector<vector<int>> &graph, const int range)
{
    for (int i = 0; i < graph.size(); i++)
        graph[i][i] = 0;
    int n = graph.size();
    for (int k = 1; k < n; k++)
    {
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < n; j++)
            {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
    int ret = 0;
    for (int start = 1; start < n; start++)
    {
        int temp = 0;
        for (int end = 1; end < n; end++)
        {
            if (graph[start][end] <= range)
                temp += reward[end];
        }
        ret = max(ret, temp);
    }
    return ret;
}

int main()
{
    int nodeCount, range, edgeCount;
    cin >> nodeCount >> range >> edgeCount;
    vector<int> reward(nodeCount + 1);
    vector<vector<int>> graph(nodeCount + 1, vector<int>(nodeCount + 1, INF));
    for (int i = 1; i <= nodeCount; i++)
    {
        cin >> reward[i];
    }
    for (int i = 0; i < edgeCount; i++)
    {
        int v1, v2, cost;
        cin >> v1 >> v2 >> cost;
        graph[v1][v2] = cost;
        graph[v2][v1] = cost;
    }
    cout << solve(reward, graph, range) << "\n";
    return 0;
}