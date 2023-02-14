#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

const int INF=987654321;

//주어진 그래프에 대해서 최소 스패닝 트리의 구성요소를 selected에 넣고
//가중합을 반환한다. 
int prim(vector<vector<pair<int,int>>>& adj, vector<pair<int,int>>& selected){
    int n=adj.size();
    priority_queue<pair<int,int>> pq;
    vector<int> parent(n,-1);
    vector<bool> added(n);
    pq.push({0,0});
    parent[0]=0;
    int ret=0;
    //O(ElogV) E:edge, V:vertex
    for(int iter=0;iter<n;iter++){
        int cur=-1,minDis=INF;
        while(!pq.empty()){
            cur=pq.top().second;
            if(!added[cur]){
                minDis=-pq.top().first;
                added[cur]=true;
                break;
            }
            pq.pop();
        }
        if(minDis==INF) return INF;
        ret+=minDis;
        for(int i=0;i<adj[cur].size();i++){ //가능한 간선 삽입
            pq.push({-adj[cur][i].first, adj[cur][i].second});
        }
    }
    return ret;
}

int main(){

}