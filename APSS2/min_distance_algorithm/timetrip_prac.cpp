#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int INF=987654321;

int getMinDistance(vector<vector<pair<int,int>>>& adj, vector<vector<bool>>& isReachable, int start, int end){
    int n=adj.size();
    vector<int> upper(n,INF);
    upper[start]=0;
    //벨만-포드 알고리즘
    bool isUpdated;
    for(int iter=0;iter<n-1;iter++){ //(n-1)번 순회
        isUpdated=false;
        for(int v=0;v<n;v++){
            for(int i=0;i<adj[v].size();i++){
                int next=adj[v][i].first, w=adj[v][i].second;
                if(upper[next]>upper[v]+w){
                    upper[next]=upper[v]+w;
                    isUpdated=true;
                }
            }
        }
        //cout << "iter: "<<iter<<"\n";
        if(!isUpdated) break;
    }
    for(int inner=0;inner<n;inner++){ //음수 사이클 찾기(start~end를 지나는 음수 사이클 이여야 의미가 있다.)
        for(int i=0;i<adj[inner].size();i++){
            int next=adj[inner][i].first, w=adj[inner][i].second;
            if(upper[next]>upper[inner]+w){ //완화가능
                if(isReachable[start][inner] && isReachable[next][end]){ //음의 사이클 존재
                    return -INF;
                }
            }
        }
        //cout << "inner: "<<inner<<"\n";
    }
    return upper[end];
}

vector<vector<bool>> getReachable(vector<vector<pair<int,int>>>& adj){
    int n=adj.size();
    vector<vector<bool>> ret(n, vector<bool>(n));
    for(int i=0;i<n;i++){
        ret[i][i]=true;
        for(int j=0;j<adj[i].size();j++){
            int next=adj[i][j].first;
            ret[i][next]=true;
        }
    }
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                ret[i][j]=ret[i][j] || (ret[i][k] && ret[k][j]);
            }
        }
    }
    return ret;
}

void solve(vector<vector<pair<int,int>>>& adj){
    int start=0,end=1;
    auto reachable=getReachable(adj);
    if(!reachable[start][end]){
        cout << "UNREACHABLE"<<"\n";
        return;
    }
    int retMin=getMinDistance(adj,reachable,start,end);
    for(int i=0;i<adj.size();i++){
        for(int j=0;j<adj[i].size();j++){
            adj[i][j].second=adj[i][j].second*-1;
        }
    }
    int retMax=getMinDistance(adj,reachable,start,end)*-1;
    if(retMin==-INF) cout<<"INFINITY"<<" ";
    else cout <<retMin<<" ";
    if(retMax==INF) cout<<"INFINITY"<<" ";
    else cout <<retMax<<" ";
    cout <<"\n";
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        int nodeCnt, edgeCnt;
        cin >> nodeCnt >> edgeCnt;
        vector<vector<pair<int,int>>> adj(nodeCnt);
        for(int i=0;i<edgeCnt;i++){
            int v1,v2,w;
            scanf("%d %d %d", &v1, &v2, &w);
            adj[v1].push_back({v2,w});
        }
        solve(adj);
    }
    return 0;
}