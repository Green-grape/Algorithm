#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int INF=987654321;

vector<vector<int>> floyd(vector<vector<pair<int,int>>>& adj){
    int n=adj.size();
    vector<vector<int>> ret(n, vector<int>(n,INF));
    for(int i=0;i<adj.size();i++){
        ret[i][i]=0;
        for(int j=0;j<adj[i].size();j++){
            int next=adj[i][j].first, cost=adj[i][j].second;
            ret[i][next]=min(ret[i][next],cost);
        }
    }
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            if(ret[i][k]==INF) continue;
            for(int j=0;j<n;j++){
                ret[i][j]=min(ret[i][j], ret[i][k]+ret[k][j]);
            }
        }
    }
    return ret;
}

// 양방향 주의
bool addEdge(vector<vector<int>>& dis, int start, int end, int cost){
    int n=dis.size();
    bool isUpdate=false;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(dis[i][j]>dis[i][start]+cost+dis[end][j]){
                isUpdate=true;
                dis[i][j]=dis[i][start]+cost+dis[end][j];
            }
            if(dis[i][j]>dis[i][end]+cost+dis[start][j]){
                isUpdate=true;
                dis[i][j]=dis[i][end]+cost+dis[start][j];
            }
        }
    }
    return isUpdate;
}

int main(){
    int testcase;
    cin >> testcase;
    while (testcase--){
        int nodeCnt, edgeCnt, conCnt;
        cin >> nodeCnt >> edgeCnt >> conCnt;
        vector<vector<pair<int,int>>> adj(nodeCnt);
        for(int i=0;i<edgeCnt;i++){
            int v1,v2,w;
            scanf("%d %d %d", &v1, &v2, &w);
            adj[v1].push_back({v2,w});
            adj[v2].push_back({v1,w});
        }
        auto dis=floyd(adj);
        int notNeed=0;
        for(int i=0;i<conCnt;i++){
            int v1,v2,w;
            scanf("%d %d %d", &v1, &v2, &w);
            if(!addEdge(dis,v1,v2,w)) notNeed++;
        }
        cout << notNeed <<"\n";
    }
    return 0;
}