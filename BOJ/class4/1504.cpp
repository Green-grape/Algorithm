#include <cstdio>
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

const int INF=987654321;

vector<vector<pair<int,int>>> adj;

int getMinDis(int start, int end){
    vector<int> minDis(adj.size(),INF);
    minDis[start]=0;
    priority_queue<pair<int,int>> pq;
    pq.push({0,start});
    while(!pq.empty()){
        int cur=pq.top().second;
        int dis=-pq.top().first;
        pq.pop();
        if(dis>minDis[cur]) continue;
        for(int i=0;i<adj[cur].size();i++){
            int next=adj[cur][i].first;
            int nextDis=adj[cur][i].second+dis;
            if(nextDis<minDis[next]){
                minDis[next]=nextDis;
                pq.push({-nextDis, next});
            }
        }
    }
    return minDis[end];
}

int solve(int pass1, int pass2){
    int dis1=getMinDis(1,pass1);
    if(dis1==INF) return -1;
    int dis2=getMinDis(pass1,pass2);
    if(dis2==INF) return -1;
    int dis3=getMinDis(pass2,adj.size()-1);
    if(dis3==INF) return -1;
    int cand=dis1+dis2+dis3;
    dis1=getMinDis(1,pass2);
    if(dis1==INF) return cand;
    dis2=getMinDis(pass2,pass1);
    if(dis2==INF) return cand;
    dis3=getMinDis(pass1,adj.size()-1);
    if(dis3==INF) return cand;
    return min(cand, dis1+dis2+dis3);
}

int main(){
    int nodeCount , edgeCount;
    cin >> nodeCount >> edgeCount;
    adj.resize(nodeCount+1);
    for(int i=0;i<edgeCount;i++){
        int v1, v2, w;
        scanf("%d %d %d", &v1, &v2, &w);
        adj[v1].push_back({v2,w});
        adj[v2].push_back({v1,w});
    }
    int pass1, pass2;
    cin >> pass1 >> pass2;
    cout << solve(pass1, pass2) <<"\n";
    return 0;
}