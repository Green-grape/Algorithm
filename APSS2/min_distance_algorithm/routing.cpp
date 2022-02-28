/*
경로를 지날때 마다 노이즈가 증폭되는데 경로와 노이즈가 주어질때 노이즈의 증폭을 최소화하는 경로는?
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>

using namespace std;

struct cmp{
    bool operator()(pair<int,double> p1, pair<int,double> p2){
        return p1.second<p2.second;
    }
};

double dijstra(int start);

vector<vector<pair<int,double>>> adj;

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int nodeCount, edgeCount;
        cin >> nodeCount >> edgeCount;
        adj=vector<vector<pair<int,double>>>(nodeCount, vector<pair<int,double>>());
        for(int j=0;j<edgeCount;j++){
            int start, end;
            double val;
            cin >> start >> end >> val;
            adj[start].push_back(make_pair(end,val));
            adj[end].push_back(make_pair(start,val));
        }
        cout << showpoint <<setprecision(11)<< dijstra(0) <<"\n";
    }
    return 0;
}

const int INF=987654321;

double dijstra(int start){
    vector<double> minDistance(adj.size(),INF);
    priority_queue<pair<int,double>, vector<pair<int,double>>, cmp> pq;
    minDistance[start]=log10(1.0);
    pq.push(make_pair(start, minDistance[start]));
    while(!pq.empty()){
        pair<int,double> cur=pq.top();
        pq.pop();
        if(cur.second>minDistance[cur.first]) continue;
        for(int i=0;i<adj[cur.first].size();i++){
            pair<int,double> next=adj[cur.first][i];
            if(minDistance[next.first]>minDistance[cur.first]+log10(next.second)){
                minDistance[next.first]=minDistance[cur.first]+log10(next.second);
                pq.push(make_pair(next.first,minDistance[next.first]));
            }
        }
    }
    return pow(10,minDistance[adj.size()-1]);
}