#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

const int INF=987654321;

int n;
vector<vector<pair<int,int>>> adj;
vector<bool> isVisit;

void dfs(int start){
    if(isVisit[start]) return;
    isVisit[start]=true;
    for(int i=0;i<adj[start].size();i++){
        dfs(adj[start][i].first);
    }
}

bool isHaveNegativeCycle(int start){
    vector<int> minPath(n,INF);
    minPath[start]=0;
    //최단거리 만들기
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<adj[j].size();k++){
                int next=adj[j][k].first;
                int w=adj[j][k].second;
                if(minPath[next]>minPath[j]+w){
                    minPath[next]=minPath[j]+w;
                }
            }
        }
    }
    //음수 사이클이 존재하는가
    for(int i=0;i<n;i++){
        for(int j=0;j<adj[i].size();j++){
            int next=adj[i][j].first;
            int w=adj[i][j].second;
            if(minPath[next]>minPath[i]+w){
                return true;
            }
        }
    }
    return minPath[start]<0;
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        int edgeCount, holeCount;
        cin >> n >> edgeCount >> holeCount;
        adj=vector<vector<pair<int,int>>>(n,vector<pair<int,int>>());
        for(int i=0;i<edgeCount;i++){
            int v1,v2,w;
            scanf("%d %d %d", &v1,&v2,&w);
            adj[v1-1].push_back({v2-1,w});
            adj[v2-1].push_back({v1-1,w});
        } 
        for(int i=0;i<holeCount;i++){
            int v1,v2,w;
            scanf("%d %d %d", &v1, &v2, &w);
            adj[v1-1].push_back({v2-1,-w});
        }
        bool flag=false;
        isVisit=vector<bool>(n);
        for(int i=0;i<n;i++){
            if(isVisit[i]) continue;
            dfs(i);
            if(isHaveNegativeCycle(i)) flag=true;
        }
        if(flag) cout <<"YES" <<"\n";
        else cout <<"NO" <<"\n";
    }
    return 0;
}