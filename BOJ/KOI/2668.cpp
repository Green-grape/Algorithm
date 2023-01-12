#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//dfs 사이클 복습

vector<vector<int>> adj;

void makeCycle(vector<int>& cycle, vector<int>& discovered, int start, int end){
    int startSeq=discovered[start], endSeq=discovered[end];
    for(int i=1;i<discovered.size();i++){
        if(startSeq<=discovered[i] && discovered[i]<=endSeq) cycle.push_back(i);
    }
}

void dfs(int node, int& nodeSeq,vector<int>& cycle, vector<int>& discovered,vector<bool>& isFinished){
    discovered[node]=nodeSeq++;
    for(int i=0;i<adj[node].size();i++){
        int next=adj[node][i];
        if(discovered[next]==0) dfs(next, nodeSeq, cycle, discovered, isFinished);
        else if(!isFinished[next]){ //cycle
            makeCycle(cycle, discovered, next, node);
        }
    }
    isFinished[node]=true;
}

vector<int> solve(int n){
    vector<bool> isVisit(n+1);
    vector<int> discovered(n+1);
    vector<int> cycle;
    int nodeSeq=1;
    for(int i=1;i<=n;i++){
        if(!isVisit[i]){
            dfs(i, nodeSeq, cycle, discovered, isVisit);
        }
    }
    sort(cycle.begin(), cycle.end());
    return cycle;
}

int main(){
    int n;
    cin >> n;
    adj.resize(n+1);
    for(int i=1;i<=n;i++){
        int next;
        cin >> next;
        adj[i].push_back(next);
    }
    vector<int> ret=solve(n);
    cout << ret.size() <<"\n";
    for(int i=0;i<ret.size();i++){
        cout << ret[i] <<"\n";
    }
    return 0;
}