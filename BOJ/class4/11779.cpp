#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF=987654321;

int n;
vector<vector<pair<int,int>>> adj;

void reconstruct(vector<int>& ret, vector<pair<int,int>>& minDis, int cur, int end){
    ret.push_back(cur);
    if(cur==end) return;
    reconstruct(ret, minDis, minDis[cur].first, end);
}

pair<int,vector<int>> getMinPath(int start, int end){
    priority_queue<pair<int,int>> pq; //가장 거리가 작은 것부터 갱신
    vector<pair<int,int>> minDis(n); //<beforeNode, distance>
    for(int i=0;i<minDis.size();i++){
        minDis[i].first=i;
        minDis[i].second=INF;
    }
    minDis[start].second=0;
    pq.push(make_pair(0,start));
    while(!pq.empty()){
        int cur=pq.top().second;
        int dis=-pq.top().first;
        pq.pop();
        if(dis>minDis[cur].second) continue;
        for(int i=0;i<adj[cur].size();i++){
            int next=adj[cur][i].first;
            int nextDis=adj[cur][i].second+dis;
            if(nextDis<minDis[next].second){
                minDis[next].second=nextDis;
                minDis[next].first=cur;
                pq.push(make_pair(-nextDis,next));
            }
        }
    }
    vector<int> path;
    reconstruct(path, minDis, end, start);
    reverse(path.begin(),path.end());
    return make_pair(minDis[end].second, path);
}

int main(){
    cin >> n;
    adj.resize(n);
    int edgeCount;
    cin >> edgeCount;
    for(int i=0;i<edgeCount;i++){
        int start, end , weight;
        scanf("%d %d %d", &start, &end, &weight);
        adj[start-1].push_back(make_pair(end-1, weight));
    }
    int start, end;
    cin >> start >> end;
    pair<int, vector<int>> ret=getMinPath(start-1, end-1);
    cout << ret.first <<"\n" << ret.second.size() <<"\n";
    for(int i=0;i<ret.second.size();i++){
        cout << ret.second[i]+1 <<" ";
    }
    return 0;
}