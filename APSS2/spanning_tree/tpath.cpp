#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_VELOCITY=1000;
const int INF=987654321;

//애매한 최대 잡기 X

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

//경로의 가중치가 minV이상인 경로로만 start와 end사이의 경로를 완성한다.
//성공: 경로의 최고 가중치, 실패: INF
//가정: edges는 정렬되어 있음
int kruskal(vector<pair<int,pair<int,int>>>& edges, int start, int end, int lower, int n){
    vector<int> parent(n);
    for(int i=0;i<n;i++) parent[i]=i;
    for(int i=0;i<edges.size();i++){
        int v1=edges[i].second.first, v2=edges[i].second.second, w=edges[i].first;
        if(w<lower) continue;
        if(!unify(parent,v1,v2)) continue;
        if(getParent(parent, start)==getParent(parent, end)){ //경로 존재
            return w;
        }
    }
    return INF;
}

//현재 그래프가 adj(edge:속도)이고 시작점이 0, 도착점이 adj.size()-1일때 시작점부터 도착점까지의 경로 중에서 최고속도와 최저속도 차이가 
//가장 적게 나는 경로의 최고속도와 최저속도의 차는?
int solve(vector<vector<pair<int,int>>>& adj){
    vector<pair<int,pair<int,int>>> edges;
    for(int i=0;i<adj.size();i++){
        for(int j=0;j<adj[i].size();j++){
            edges.push_back({adj[i][j].second, {i,adj[i][j].first}});
        }
    }
    sort(edges.begin(), edges.end());
    int ret=MAX_VELOCITY;
    for(int i=0;i<edges.size();i++){
        int maxV=kruskal(edges,0,adj.size()-1,edges[i].first,adj.size());
        ret=min(ret, maxV-edges[i].first);
    }
    return ret;
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        int nodeCnt, edgeCnt;
        cin >> nodeCnt >> edgeCnt;
        vector<vector<pair<int,int>>> adj(nodeCnt);
        for(int i=0;i<edgeCnt;i++){
            int v1, v2, w;
            scanf("%d %d %d", &v1, &v2, &w);
            adj[v1].push_back({v2,w});
        }
        cout << solve(adj) <<"\n";
    }
    return 0;
}