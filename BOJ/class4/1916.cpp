#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

const int INF=987654321;
int n;
vector<vector<pair<int,int>>> dis;

int getMinDis(int from, int to){
    priority_queue<pair<int,int>,vector<pair<int,int>>> pq;
    vector<int> ret(dis.size(),INF);
    ret[from]=0;
    pq.push({0, from});
    while(!pq.empty()){
        pair<int,int> cur=pq.top();
        pq.pop();
        int curDis=-cur.first;
        int curIdx=cur.second;
        if(curDis>ret[curIdx]) continue;
        for(int i=0;i<dis[curIdx].size();i++){
            int next=dis[curIdx][i].first;
            int nextDis=curDis+dis[curIdx][i].second;
            if(nextDis<ret[next]){
                ret[next]=nextDis;
                pq.push({-nextDis,next});
            }
        }
    }
    return ret[to];
}

int main(){
    cin >> n;
    int edgeCnt;
    cin >> edgeCnt;
    dis.resize(n+1);
    for(int i=0;i<edgeCnt;i++){
        int v1,v2,cost;
        scanf("%d %d %d", &v1, &v2, &cost);
        dis[v1].push_back({v2,cost});
    }
    int from, to;
    cin >> from >> to;
    cout << getMinDis(from,to) <<"\n";
    return 0;
}