/*
n개 지역에 동시에 화재가 발생하여 M개의 지역에 존재하는 소방서에서 소방차가 출발하려고 한다.
이때 각 지역에 소방차가 가장 빠르게 도달할 수 있는 소방서에서 소방차를 보내며 소방차의 개수는 무제한이다.
이때 모든 화재 장소까지 소방차가 도달하는 데 걸리는 시간의 합은?
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<pair<int,int>>> adj;
vector<int> firePlace;
vector<int> fireStation;

struct cmp{
    bool operator()(pair<int,int> p1, pair<int,int> p2){
        return p1.second<p2.second;
    }
};

int getSumOfMinDistance();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int nodeCount, edgeCount, n, m;
        cin >> nodeCount >> edgeCount >> n >>m;
        adj=vector<vector<pair<int,int>>>(nodeCount+1, vector<pair<int,int>>());
        for(int j=0;j<edgeCount;j++){
            int start, end, val;
            cin >> start >> end >> val;
            adj[start].push_back(make_pair(end,val));
            adj[end].push_back(make_pair(start, val));
        }
        for(int j=0;j<n;j++){
            int temp;
            cin >> temp;
            firePlace.push_back(temp);
        }
        for(int j=0;j<m;j++){
            int temp;
            cin >> temp;
            fireStation.push_back(temp);
        }
        cout << getSumOfMinDistance() <<"\n";
    }
    return 0;
}

const int INF=987654321;

vector<int> dijkstra(int start){
    vector<int> minDistance(adj.size(),INF); //minDistance[i]=start~i까지의 최단거리
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
                pq.push(make_pair(next.first,minDistance[next.first]));
            }
        }
    }
    return minDistance;
}

int getSumOfMinDistance(){
    //모든 정점에서 다익스트라를 하기 위해서 가상의 정점 0에 대해서 소방서까지의 거리를 0이라 하자
    const int virtualNode=0;
    int ret=0;
    for(int i=0;i<fireStation.size();i++){
        adj[virtualNode].push_back(make_pair(fireStation[i],0));
        adj[fireStation[i]].push_back(make_pair(virtualNode,0));
    }
    vector<int> minDistance=dijkstra(virtualNode);
    for(int i=0;i<firePlace.size();i++){
        ret+=minDistance[firePlace[i]];
    }
    return ret;
}