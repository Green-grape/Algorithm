#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 987654321;

vector<pair<char, char>> solve(vector<vector<int>> &adj) //O(V^3)
{
    for (int i = 0; i < adj.size(); i++)
    {
        adj[i][i] = 0;
    }
    for (int k = 0; k < adj.size(); k++) //순서 주의
    {
        for (int i = 0; i < adj[k].size(); i++)
        {
            for (int j = 0; j < adj[i].size(); j++)
            {
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
    vector<pair<char, char>> ret;
    for (int i = 0; i < adj.size(); i++)
    {
        for (int j = 0; j < adj[i].size(); j++)
        {
            if (adj[i][j] < INF && adj[i][j] > 0 && i != j)
            {
                char a, b;
                if (0 <= i && i < 26)
                    a = i + 'a';
                else if (26 <= i && i < 52)
                    a = i + ('A' - 26);
                if (0 <= j && j < 26)
                    b = j + 'a';
                else if (26 <= j && j < 52)
                    b = j + ('A' - 26);
                ret.push_back(make_pair(a, b));
            }
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

int main()
{
    int propositonCount;
    cin >> propositonCount;
    vector<vector<int>> adj(52, vector<int>(52, INF));
    for (int i = 0; i < propositonCount; i++)
    {
        int v1, v2;
        char start, end;
        char arrow[4];
        getchar();
        scanf("%c %s %c", &start, arrow, &end);
        if ('a' <= start && start <= 'z')
            v1 = start - 'a';
        else if ('A' <= start && start <= 'Z')
            v1 = start - 'A' + 26;
        if ('a' <= end && end <= 'z')
            v2 = end - 'a';
        else if ('A' <= end && end <= 'Z')
            v2 = end - 'A' + 26;
        adj[v1][v2] = 1;
    }
    vector<pair<char, char>> ret = solve(adj);
    cout << ret.size() << "\n";
    for (int i = 0; i < ret.size(); i++)
    {
        cout << ret[i].first << " => " << ret[i].second << "\n";
    }
    return 0;
}