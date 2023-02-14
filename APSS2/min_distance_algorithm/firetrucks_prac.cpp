#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

int getTotalCost(vector<vector<pair<int,int>>>& adj, vector<int>& from, vector<int>& to){
    vector<int> minCost(adj.size(), INT32_MAX);
    priority_queue<pair<int,int>> pq;
    for(int i=0;i<from.size();i++){ //모든 시작점에 대해서 다익스트라 적용(시작점이 중요한것이 아님),
        pq.push({0, from[i]});
        minCost[from[i]]=0;
    }
    while(!pq.empty()){
        pair<int,int> cur=pq.top();
        int curCost=-cur.first, curNode=cur.second;
        pq.pop();
        if(minCost[curNode]<curCost) continue;
        for(int i=0;i<adj[curNode].size();i++){
            int nextCost=adj[curNode][i].first+curCost;
            int next=adj[curNode][i].second;
            if(nextCost<minCost[next]){
                minCost[next]=nextCost;
                pq.push({-nextCost, next});
            }
        }
    }
    int ret=0;
    for(int i=0;i<to.size();i++){
        ret+=minCost[to[i]];
    }
    return ret;
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        int nodeCnt, edgeCnt, toCnt, fromCnt;
        cin >> nodeCnt >> edgeCnt >> toCnt >> fromCnt;
        vector<vector<pair<int,int>>> adj(nodeCnt+1);
        vector<int> from(fromCnt), to(toCnt);
        for(int i=0;i<edgeCnt;i++){
            int v1,v2,cost;
            scanf("%d %d %d", &v1, &v2, &cost);
            adj[v1].push_back({cost,v2});
            adj[v2].push_back({cost,v1});
        }
        for(int i=0;i<to.size();i++) scanf("%d", &to[i]);
        for(int i=0;i<from.size();i++) scanf("%d", &from[i]);
        cout << getTotalCost(adj,from, to)<<"\n";
    }
    return 0;
}