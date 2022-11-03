#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<vector<pair<int,int>>> adj;
vector<int> nextV;
vector<long long> cache;

long long dfs(int cur){
    if(cache[cur]!=-1) return cache[cur];
    cache[cur]=0;
    nextV[cur]=cur;
    for(int i=0;i<adj[cur].size();i++){
        int next=adj[cur][i].first;
        int w=adj[cur][i].second;
        if(cache[next]!=-1) continue;
        long long cand=w+dfs(next);
        if(cand>cache[cur]){
            cache[cur]=cand;
            nextV[cur]=next;
        }
    }
    return cache[cur];
}

int findEnd(int cur){
    if(nextV[cur]==cur) return cur;
    return findEnd(nextV[cur]);
}

long long solve(){
    nextV=vector<int>(adj.size());
    cache=vector<long long>(adj.size(),-1);
    dfs(1);
    int start=findEnd(1);
    nextV=vector<int>(adj.size());
    cache=vector<long long>(adj.size(),-1);
    dfs(start);
    return cache[start];
}

int main(){
    int vertexCnt;
    cin >> vertexCnt;
    adj.resize(vertexCnt+1);
    for(int i=1;i<=vertexCnt;i++){
        int start;
        cin >> start;
        while(true){
            int v1, w;
            scanf("%d", &v1);
            if(v1==-1) break;
            scanf("%d", &w);
            adj[start].push_back({v1,w});
        }
    }
    cout << solve() <<"\n";
    return 0;
}