#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj; //adj[i] i->인 정점 배열
vector<vector<char>> edge; //edge[i][j]의 정점 종류 저장 t:tree, f:forward, b:back, c:cross 비어있으면:NULL

vector<int> discovered; //discoverd[i] i번째 간선이 발견된 순서
vector<bool> finished; //dfs2(i)가 끝났는지 확인 끝났으면 true 아니면 false

int counter; //지금까지 발견한 정점의 수

void initialize(const int vertexCount){
    edge=vector<vector<char>>(vertexCount,vector<char>(vertexCount,NULL));
    discoverd=vector<int>(vertexCount,-1);
    finished=vector<bool>(vertexCount,false);
    counter=0;
}

void dfs2(int i){
    discovered[i]=counter++;
    for(int j=0;j<adj[i].size();j++){
        int next=adj[i][j];
        if(discoverd[next]==-1){
            edge[i][next]='t';
            dfs2(next);
            continue;
        }
        if(discovered[i]<discovered[next]){
            edge[i][next]='f';
        }
        else{
            if(finished[next]) edge[i][next]='c';
            else edge[i][next]='b';
        }
    }
    finished[i]=true;
}