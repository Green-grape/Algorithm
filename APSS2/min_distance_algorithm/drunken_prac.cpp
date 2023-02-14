#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const int INF=987654321;

//현재 경로가 adj이고 정점v에서 대기가 발생할 경우 딜레이가 delay[v]라고 할때
//임의의 한 정점에서만 딜레이가 발생한다고 한다. 이때 정점 사이의 최악의 예상시간이 가장 작은 경로의 길이는?
//플로이드 결과를 따로 관리하는것 주의
vector<vector<int>> getMinDisWithDelay(vector<vector<pair<int,int>>>& adj, vector<int>& delay){
    int n=adj.size();
    vector<vector<int>> ret(n, vector<int>(n,INF));
    vector<vector<int>> noDelayDis(n,vector<int>(n,INF));
    for(int i=1;i<n;i++){
        ret[i][i]=noDelayDis[i][i]=0;
        for(int j=0;j<adj[i].size();j++){
            ret[i][adj[i][j].first]=noDelayDis[i][adj[i][j].first]=min(ret[i][adj[i][j].first], adj[i][j].second);
        }
    }
    vector<pair<int,int>> order(delay.size());
    for(int i=0;i<order.size();i++) order[i]={delay[i],i};
    sort(order.begin(), order.end());
    for(int k=1;k<order.size();k++){
        int via=order[k].second;
        for(int i=1;i<n;i++){
            if(noDelayDis[i][via]==INF) continue;
            for(int j=1;j<n;j++){
                noDelayDis[i][j]=min(noDelayDis[i][j], noDelayDis[i][via]+noDelayDis[via][j]);
                ret[i][j]=min(ret[i][j], noDelayDis[i][j]+order[k].first); //경유점에서 딜레이가 발생한 경우
            }
        }
    }
    return ret;
}

int main(){
    int nodeCnt, edgeCnt;
    cin >> nodeCnt >> edgeCnt;
    vector<int> delayTime(nodeCnt+1,0);
    vector<vector<pair<int,int>>> adj(nodeCnt+1);
    for(int i=1;i<=nodeCnt;i++) scanf("%d", &delayTime[i]);
    for(int i=0;i<edgeCnt;i++){
        int v1, v2, w;
        scanf("%d %d %d", &v1, &v2, &w);
        adj[v1].push_back({v2,w});
        adj[v2].push_back({v1,w});
    }
    auto dis=getMinDisWithDelay(adj,delayTime);
    int testcase;
    cin >> testcase;
    while(testcase--){
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        cout << dis[v1][v2]<<"\n";
    }
    return 0;
}