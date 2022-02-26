/*
간단한 BFS 알고리즘을 이용한 시작점으로 부터 최단 거리 구하기
간선하나당 거리 1로 가정
*/

#include <vector>
#include <queue>

using namespace std;

void bfsWithMinDistance(int start, vector<vector<int>>& adj, vector<int>& distance, vector<int>& parent){
    distance=vector<int>(adj.size(),-1); //distance[i]=start~i까지 최단 거리
    parent=vector<int>(adj.size(),-1); //parent[i]=BFS 스패닝 트리에서 i의 부모, 루트는 자기 자신   

    queue<int> q;
    distance[start]=0;
    parent[start]=start;
    q.push(start);
    while(!q.empty()){
        int here=q.front();
        q.pop();
        for(int i=0;i<adj[here].size();i++){
            int next=adj[here][i];
            if(distance[next]==-1){
                q.push(next);
                distance[next]=distance[here]+1;
                parent[next]=here;
            }
        }
    }
}