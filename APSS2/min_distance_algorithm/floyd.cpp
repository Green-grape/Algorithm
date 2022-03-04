/*
플로이드 알고리즘 구현
*/

#include <vector>
#include <algorithm>

using namespace std;

int V;
const int MAX_VERTEX=10;
const int INF=987654321;
vector<vector<int>> adj(MAX_VERTEX, vector<int>(MAX_VERTEX, INF));
//minDistance[k][u][v]=0~k번까지의 정점을 경유점으로 하는 u->v의 최단거리
vector<vector<vector<int>>> minDistance(MAX_VERTEX, vector<vector<int>>(MAX_VERTEX, vector<int>(MAX_VERTEX, INF)));

//prototype
//문제 공간복잡도가 |v|^3
void floyd(){
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            minDistance[0][i][j]=min(adj[i][j], adj[i][0]+adj[0][j]);
        }
    }
    for(int k=1;k<V;k++){
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                minDistance[k][i][j]=min(minDistance[k-1][i][k]+minDistance[k-1][k][j], minDistance[k-1][i][j]);
            }
        }
    }
}

vector<vector<int>> stopovers(MAX_VERTEX,vector<int>(MAX_VERTEX,-1));

//minDistance[k][u][k]=minDistance[k-1][u][k], minDistance[k][k][v]=minDistance[k-1][k][v]임을 이용하자
//adj[i][k]가 실제로 존재하는가?를 확인하면 마지막 for문을 사용하지 않으므로 속도가 상승한다.
//공간 복잡도 O(|V|^2)
void floyd_memory_opt(){
    for(int k=0;k<V;k++){
        for(int i=0;i<V;i++){
            if(adj[i][k]==INF) continue;
            for(int j=0;j<V;j++){
                if(adj[i][j]>adj[i][k]+adj[k][j]){
                    adj[i][j]=adj[i][k]+adj[k][j];
                    stopovers[i][j]=k;
                }
            }
        }
    }
}

vector<int> addVector(vector<int> a, vector<int> b){
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

vector<int> getMindistancePath(int start, int end){
    if(stopovers[start][end]==-1){
        vector<int> ret;
        ret.push_back(start);
        if(start!=end) ret.push_back(end);
        return ret;
    }
    else{
        vector<int> ret=getMindistancePath(start, stopovers[start][end]);
        ret.push_back(stopovers[start][end]);
        return addVector(ret, getMindistancePath(stopovers[start][end],end));
    }
}






