#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, pair<int,int>>> edge;
vector<int> parent;

int getParent(int child){
    if(parent[child]==child) return child;
    return parent[child]=getParent(parent[child]);
}

void unify(int n1, int n2){
    int p1=getParent(n1), p2=getParent(n2);
    if(p1<p2){
        parent[p2]=p1;
    }else if(p1>p2){
        parent[p1]=p2;
    }
}

int solve(){
    int ret=0;
    for(int i=0;i<edge.size();i++){
        int w=edge[i].first;
        int n1=edge[i].second.first;
        int n2=edge[i].second.second;
        if(getParent(n1)==getParent(n2)) continue;
        unify(n1,n2);
        ret+=w;
    }
    return ret;
}

int main(){
    int nodeCount,edgeCount;
    cin >> nodeCount >> edgeCount;
    parent.resize(nodeCount+1);
    for(int i=1;i<parent.size();i++){
        parent[i]=i;
    }
    edge.resize(edgeCount);
    for(int i=0;i<edgeCount;i++){
        int v1,v2,w;
        cin >> v1 >> v2 >> w;
        edge.push_back(make_pair(w,make_pair(v1,v2)));
    }
    sort(edge.begin(), edge.end());
    cout << solve() <<"\n";
    return 0;
}