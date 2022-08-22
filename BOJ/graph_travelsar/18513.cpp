#include <iostream>
#include <queue>
#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

long long getMinUnhappines(vector<int> &shelter, const int houseCount)
{
    queue<int> q;
    set<int> visit;
    int dx[] = {-1, 1};
    for (int i = 0; i < shelter.size(); i++)
    {
        q.push(shelter[i]);
        visit.insert(shelter[i]);
    }
    int buildCount = 0;
    int curBad = 1;
    long long ret = 0;
    while (!q.empty())
    {
        int q_size = q.size();
        while (q_size--)
        {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < 2; i++)
            {
                int next = cur + dx[i];
                if (visit.find(next) == visit.end())
                {
                    visit.insert(next);
                    q.push(next);
                    buildCount++;
                    ret += curBad;
                    if (buildCount == houseCount)
                        return ret;
                }
            }
        }
        curBad++;
    }
    return ret;
}

int main()
{
    int shelterCount, houseCount;
    vector<int> shelter;
    cin >> shelterCount >> houseCount;
    shelter.resize(shelterCount);
    for (int i = 0; i < shelterCount; i++)
    {
        scanf("%d", &shelter[i]);
    }
    cout << getMinUnhappines(shelter, houseCount) << "\n";
    return 0;
}