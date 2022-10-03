#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

vector<int> takenTimes;
vector<vector<int>> prevs;
vector<long long> cache;

long long getTime(int target)
{
    if (cache[target] != -1)
        return cache[target];
    long long &ret = cache[target];
    ret = takenTimes[target];
    for (int i = 0; i < prevs[target].size(); i++)
    {
        int before = prevs[target][i];
        ret = max(ret, takenTimes[target] + getTime(before));
    }
    return ret;
}

int main()
{
    int testCase;
    cin >> testCase;
    while (testCase)
    {
        int nodeCount, prevCount, target;
        cin >> nodeCount >> prevCount;
        takenTimes = vector<int>(nodeCount + 1);
        prevs = vector<vector<int>>(nodeCount + 1, vector<int>());
        cache = vector<long long>(nodeCount + 1, -1);
        for (int i = 1; i <= nodeCount; i++)
        {
            scanf("%d", &takenTimes[i]);
        }
        for (int i = 0; i < prevCount; i++)
        {
            int v1, v2;
            scanf("%d %d", &v1, &v2);
            prevs[v2].push_back(v1);
        }
        cin >> target;
        cout << getTime(target) << "\n";
        testCase--;
    }
    return 0;
}