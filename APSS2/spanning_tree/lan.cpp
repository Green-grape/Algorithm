#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

const int INF=987654321;

double distance(pair<int,int> p1, pair<int,int> p2){
    return sqrt(pow(p1.first-p2.first,2)+pow(p1.second-p2.second,2));
}

int getParent(vector<int>& parent, int cur){
    if(parent[cur]==cur) return cur;
    return parent[cur]=getParent(parent,parent[cur]);
}

bool unify(vector<int>& parent,int v1, int v2){
    int p1=getParent(parent, v1), p2=getParent(parent, v2);
    if(p1==p2) return false;
    if(p1>p2) parent[p1]=p2;
    else parent[p2]=p1;
    return true;
}

//현재 그래프가 adj(인접 행렬)이고, 각각의 위치가 pos일때 모든 위치를 연결하기 위한 최소한의 거리는?
//adj: 연결되어 있으면 0, 연결되어 있지 않으면 INF
double getMinConnectDis(vector<vector<int>>& adj, vector<pair<int,int>>& pos){
    int n=adj.size();
    vector<int> parent(n);
    for(int i=0;i<n;i++) parent[i]=i;
    vector<pair<double, pair<int,int>>> edges;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(adj[i][j]==INF){
                edges.push_back({distance(pos[i],pos[j]),{i,j}});
            }else if(adj[i][j]==0){
                edges.push_back({0,{i,j}});
            }
        }
    }
    sort(edges.begin(),edges.end());
    double ret=0;
    for(int i=0;i<edges.size();i++){
        int v1=edges[i].second.first, v2=edges[i].second.second;
        double w=edges[i].first;
        if(!unify(parent,v1,v2)) continue;
        ret+=w;
    }
    return ret;
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        int nodeCnt, edgeCnt;
        cin >> nodeCnt >> edgeCnt;
        vector<vector<int>> adj(nodeCnt, vector<int>(nodeCnt,INF));
        vector<pair<int,int>> pos(nodeCnt);
        for(int i=0;i<nodeCnt;i++){
            int x;
            scanf("%d", &x);
            pos[i].first=x;
            adj[i][i]=0;
        }
         for(int i=0;i<nodeCnt;i++){
            int y;
            scanf("%d", &y);
            pos[i].second=y;
        }
        for(int i=0;i<edgeCnt;i++){
            int v1, v2;
            scanf("%d %d", &v1, &v2);
            adj[v1][v2]=0;
            adj[v2][v1]=0;
        }
        cout << fixed << setprecision(8) << getMinConnectDis(adj,pos) <<"\n";
    }
    return 0;
}