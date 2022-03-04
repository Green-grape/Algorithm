/*
정점들 사이에 간선을 추가하려고 하는데 조건이 있다.
1. 두 간선이 연결되지 않은 경우
2. 최단 거리를 갱신할 수 있는 경우
이외의 경우는 의미 없는 간선으로 본다.
간선을 추가하는 순서가 주어질때 그 중 몇 개의 간선이 추가하는 것이 의미가 없는가?
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Edge{
    int start, end, val;
    Edge(int _start, int _end,int _val) : start(_start), end(_end), val(_val) {};
};

const int MAX_VERTEX=200;
const int MAX_EDGE=1000;
const int INF=987654321;
vector<vector<int>> adj(MAX_VERTEX, vector<int>(MAX_VERTEX,INF));
vector<Edge*> e;
vector<Edge*> fe;
int vertexCount, edgeCount, futureEdgeCount;

int floyd();
void init();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        cin >> vertexCount >> edgeCount >> futureEdgeCount;
        for(int j=0;j<edgeCount;j++){
            int start, end, val;
            cin >> start >> end >> val;
            e.push_back(new Edge(start,end,val));
            adj[start][end]=val;
            adj[end][start]=val;
        }
        for(int j=0;j<futureEdgeCount;j++){
            int start, end, val;
            cin >> start >> end >> val;
            fe.push_back(new Edge(start, end, val));
        }
        cout << floyd() <<"\n";
        init();
    }
}

void init(){
    adj=vector<vector<int>>(MAX_VERTEX, vector<int>(MAX_VERTEX, INF));
    e.resize(0);
    fe.resize(0);
}

int floyd(){
    int ret=0;
    //기존 경로로 플로이드 연산
    for(int i=0;i<vertexCount;i++){
        for(int j=0;j<vertexCount;j++){
            if(i==j) adj[i][j]=0;
        }
    }
    for(int k=0;k<vertexCount;k++){
        for(int i=0;i<vertexCount;i++){
            if(adj[i][k]==INF) continue;
            for(int j=0;j<vertexCount;j++){
                adj[i][j]=min(adj[i][j], adj[i][k]+adj[k][j]);
            }
        }
    }
    //경로 추가하면서 의미있는 간선인지 테스트
    for(int k=0;k<fe.size();k++){
        Edge* curEdge=fe[k];
        bool isUseLess=true;
        for(int i=0;i<vertexCount;i++){
            if(adj[i][curEdge->start]==INF && adj[i][curEdge->end]==INF) continue;
            for(int j=0;j<vertexCount;j++){
                if(adj[i][j]>adj[i][curEdge->start]+curEdge->val+adj[curEdge->end][j] || adj[i][j]>adj[i][curEdge->end]+curEdge->val+adj[curEdge->start][j]){
                    adj[i][j]=min(adj[i][curEdge->start]+curEdge->val+adj[curEdge->end][j],adj[i][curEdge->end]+curEdge->val+adj[curEdge->start][j]);
                    isUseLess=false;
                }
            }
        }
        if(isUseLess) ret++;
    }
    return ret;
}