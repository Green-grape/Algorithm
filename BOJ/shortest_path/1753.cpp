#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int INF = 987654321;

vector<int> shortestPathFrom(vector<vector<pair<int, int>>> &graph, int start)
{
    vector<int> path(graph.size(), INF);
    priority_queue<pair<int, int>> pq;
    path[start] = 0;
    pq.push(make_pair(0, start));
    while (!pq.empty())
    {
        int curDis = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();
        if (path[cur] < curDis)
            continue;
        for (int i = 0; i < graph[cur].size(); i++)
        {
            int next = graph[cur][i].first;
            int cost = graph[cur][i].second;
            if (path[next] > curDis + cost)
            {
                path[next] = curDis + cost;
                pq.push(make_pair(-path[next], next));
            }
        }
    }
    return path;
}

int main()
{
    int vertexCount, edgeCount, start;
    cin >> vertexCount >> edgeCount >> start;
    vector<vector<pair<int, int>>> graph(vertexCount + 1);
    graph[start].push_back(make_pair(start, 0));
    for (int i = 0; i < edgeCount; i++)
    {
        int start, end, weight;
        scanf("%d %d %d", &start, &end, &weight);
        graph[start].push_back(make_pair(end, weight));
    }
    vector<int> ret = shortestPathFrom(graph, start);
    for (int v = 1; v < ret.size(); v++)
    {
        if (ret[v] == INF)
            printf("INF\n");
        else
            printf("%d\n", ret[v]);
    }
    return 0;
}