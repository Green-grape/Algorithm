#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <cmath>

using namespace std;


//시작점 0, 마지막점 adj.size()-1 사이에서 가장 적은 노이즈량
double getMinCost(vector<vector<pair<double,int>>>& adj){
    vector<double> minCost(adj.size(), 1e10);
    priority_queue<pair<double,int>> pq;
    pq.push({0.0,0});
    minCost[0]=0;
    while(!pq.empty()){
        pair<double,int> cur=pq.top();
        double curCost=-cur.first;
        int node=cur.second;
        pq.pop();
        if(minCost[node]<curCost) continue;
        for(int i=0;i<adj[node].size();i++){
            double nextCost=adj[node][i].first+curCost;
            int next=adj[node][i].second;
            if(nextCost<minCost[next]){
                minCost[next]=nextCost;
                pq.push({-nextCost, next});
            }
        }
    }
    double logCost=minCost[adj.size()-1]; //현재 구한 값은 배율에 log2를 해준값
    return pow(2,logCost);
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        int nodeCnt, edgeCnt;
        cin >> nodeCnt >> edgeCnt;
        vector<vector<pair<double,int>>> adj(nodeCnt);
        for(int i=0;i<edgeCnt;i++){
            int v1, v2; double mul;
            cin >> v1 >> v2 >> mul;
            adj[v1].push_back({log2(mul),v2});
            adj[v2].push_back({log2(mul),v1});
        }
        cout << fixed << setprecision(10) <<getMinCost(adj) <<"\n";
    }
    return 0;
}