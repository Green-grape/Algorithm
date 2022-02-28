/*
다익스트라 알고리즘을 BFS+priority_queue로 구현
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_VERTEX=10;
const int INF=987654321;

struct cmp{
    bool operator()(pair<int,int> p1, pair<int,int> p2){
        return p1.second<p2.second;
    }
};

vector<pair<int,int>> adj[MAX_VERTEX];
//O(ElgE) (E:간선의 수(모든 간선에 대해서 큐에 삽입)) E<V^2 이므로 (대부분) =O(ElgV)
vector<int> dijkstra(int start){
    vector<int> minDistance(MAX_VERTEX,INF); //minDistance[i]=start~i까지의 최단거리
    vector<int> parent(MAX_VERTEX);
    for(int i=0;i<parent.size();i++) parent[i]=i;
    minDistance[start]=0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> pq;
    pq.push(make_pair(start, minDistance[start]));
    while(!pq.empty()){
        pair<int,int> cur=pq.top();
        pq.pop();
        if(minDistance[cur.first]<cur.second) continue;
        for(int i=0;i<adj[cur.first].size();i++){
            pair<int,int> next=adj[cur.first][i];
            if(minDistance[next.first]>minDistance[cur.first]+next.second){
                minDistance[next.first]=minDistance[cur.first]+next.second;
                parent[next.first]=cur.first;
                pq.push(make_pair(next.first,minDistance[next.first]));
            }
        }
    }
    return minDistance;
}


//간선의 수가 정점의 수에 비해 매우 많은 경우 우선 순위큐로 구현하는 것이 매우 느릴수 있다.
vector<int> dijkstraWithOutPriorityQueue(int start){
    vector<int> minDistance(MAX_VERTEX, INF);
    vector<bool> isVisited(MAX_VERTEX,false);
    minDistance[start]=0;
    while(true){
        pair<int,int> tempMin(-1,INF);
        for(int i=0;i<MAX_VERTEX;i++){
            if(!isVisited[i] && tempMin.second>minDistance[i]){
                tempMin=make_pair(i,minDistance[i]);
            }
        }
        if(tempMin.first==-1) break;
        isVisited[tempMin.first]=true;
        for(int i=0;i<adj[tempMin.first].size();i++){
            pair<int,int> next=adj[tempMin.first][i];
            if(isVisited[next.first]) continue;
            if(minDistance[next.first]>minDistance[tempMin.first]+next.second){
                minDistance[next.first]=minDistance[tempMin.first]+next.second;
            }
        }
    }
    return minDistance;
}