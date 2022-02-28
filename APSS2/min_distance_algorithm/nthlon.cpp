/*
n개의 종목을 수행해서 두 선수의 종목 수행시간의 합계가 같으면서 최소인 경우를 구하라
구하지 못한다면 IMPOSSIBLE 반환
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct cmp{
    bool operator()(pair<int,int> p1, pair<int,int> p2){
        return p1.second<p2.second;
    }
};

vector<pair<int,int>> eventScore;
vector<vector<pair<int,int>>> adj;

int getMinDrawTime();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int eventCount;
        cin >> eventCount;
        eventScore=vector<pair<int,int>>(eventCount, pair<int,int>(0,0));
        for(int j=0;j<eventCount;j++){
            cin >> eventScore[j].first >> eventScore[j].second;
        }
        int ret=getMinDrawTime();
        if(ret==-1) cout <<"IMPOSSIBLE"<<"\n";
        else cout << ret <<"\n";
    }
    return 0;
}

vector<int> dijkstra(int start){
    const int MAX_VERTEX=401;
    const int INF=987654321;
    vector<int> minDistance(MAX_VERTEX,INF); //minDistance[i]=start~i까지의 최단거리
    vector<int> parent(MAX_VERTEX);
    for(int i=0;i<parent.size();i++) parent[i]=i;
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
                parent[next.first]=cur.first;
                pq.push(make_pair(next.first,minDistance[next.first]));
            }
        }
    }
    return minDistance;
}


int index(int idx){
    return idx+200;
}

int getMinDrawTime(){
    const int V=401;  //400:start, 0: end, 1~399:dif(-199~+199)
    const int start=400;
    int countPlus=0;
    int countMinus=0;
    int countZero=0;
    adj=vector<vector<pair<int,int>>>(V, vector<pair<int,int>>());
    for(int i=0;i<eventScore.size();i++){
        if(eventScore[i].first-eventScore[i].second>0) countPlus++;
        else if(eventScore[i].first-eventScore[i].second<0) countMinus++;
        else countZero++;
        int idx=index(eventScore[i].first-eventScore[i].second);
        adj[start].push_back(make_pair(idx,eventScore[i].first));
    }
    if(countZero==0 && (countPlus==0 || countMinus==0)) return -1;
    for(int delta=-199;delta<=199;delta++){
        for(int i=0;i<eventScore.size();i++){
            int next=delta+eventScore[i].first-eventScore[i].second;
            if(abs(next)>=200) continue;
            int nextIdx=index(next);
            adj[index(delta)].push_back(make_pair(nextIdx, eventScore[i].first));
        }
    }
    vector<int> minDistance=dijkstra(start);
    return minDistance[index(0)];
}