#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int INF=987654321;
vector<vector<int>> adj;

vector<vector<int>> floyd(){
    int n=adj.size();
    vector<vector<int>> ret=adj;
    for(int k=1;k<n;k++){
        for(int i=1;i<n;i++){
            for(int j=1;j<n;j++){
                ret[i][j]=min(ret[i][j],ret[i][k]+ret[k][j]);
            }
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<n;j++){
            if(ret[i][j]==INF) ret[i][j]=0;
        }
    }
    return ret;
}

int main(){
    int vertexCnt, edgeCnt;
    cin >> vertexCnt >> edgeCnt;
    adj=vector<vector<int>>(vertexCnt+1,vector<int>(vertexCnt+1,INF));
    for(int i=1;i<adj.size();i++) adj[i][i]=0;
    for(int i=0;i<edgeCnt;i++){
        int v1,v2,w;
        scanf("%d %d %d", &v1, &v2, &w);
        adj[v1][v2]=min(adj[v1][v2],w);
    }
    vector<vector<int>> ret=floyd();
    for(int i=1;i<ret.size();i++){
        for(int j=1;j<ret[i].size();j++){
            cout << ret[i][j] <<" ";
        }
        cout <<"\n";
    }
    return 0;
}