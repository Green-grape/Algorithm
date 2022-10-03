#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <set>

using namespace std;

vector<int> getSequence(vector<set<int>> &prevs, vector<set<int>> &nexts)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> visit(prevs.size());
    for (int node = 1; node < prevs.size(); node++)
    {
        if (prevs[node].size() == 0)
        {
            pq.push(node);
            visit[node] = 1;
        }
    }
    vector<int> ret;
    while (!pq.empty())
    {
        int cur = pq.top();
        pq.pop();
        ret.push_back(cur);
        for (set<int>::iterator it = nexts[cur].begin(); it != nexts[cur].end(); it++)
        {
            int next = (*it);
            prevs[next].erase(cur);
            if (prevs[next].size() == 0 && !visit[next])
            {
                visit[next] = 1;
                pq.push(next);
            }
        }
    }
    return ret;
}

int main()
{
    int nodeCount, edgeCount;
    cin >> nodeCount >> edgeCount;
    vector<set<int>> prevs(nodeCount + 1);
    vector<set<int>> nexts(nodeCount + 1);
    for (int i = 0; i < edgeCount; i++)
    {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        prevs[v2].insert(v1);
        nexts[v1].insert(v2);
    }
    vector<int> ret = getSequence(prevs, nexts);
    for (int i = 0; i < ret.size(); i++)
    {
        cout << ret[i] << " ";
    }
    return 0;
}