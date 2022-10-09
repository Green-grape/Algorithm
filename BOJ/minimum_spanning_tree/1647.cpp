#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int,pair<int,int>>> edge;
vector<int> parent;

int getParent(int child){
    if(parent[child]==child) return child;
    return parent[child]=getParent(parent[child]);
}

void unify(int v1, int v2){
    int p1=getParent(v1), p2=getParent(v2);
    if(p1<p2){
        parent[p2]=p1;
    }else if(p1>p2){
        parent[p1]=p2;
    }
}

int solve(){
    sort(edge.begin(), edge.end());
    int ret=0;
    int maxEdge=-1;
    for(int i=0;i<edge.size();i++){
        int v1=edge[i].second.first;
        int v2=edge[i].second.second;
        int w=edge[i].first;
        if(getParent(v1)==getParent(v2)) continue;
        maxEdge=w;
        unify(v1,v2);
        ret+=w;
    }
    return ret-maxEdge;
}

int main(){
    int vertexCount, edgeCount;
    cin >> vertexCount >> edgeCount;
    edge.resize(vertexCount+1);
    parent.resize(vertexCount+1);
    for(int i=1;i<parent.size();i++){
        parent[i]=i;
    }
    for(int i=0;i<edgeCount;i++){
        int v1, v2, w;
        scanf("%d %d %d", &v1, &v2, &w);
        edge.push_back(make_pair(w,make_pair(v1,v2)));
    }
    cout << solve() <<"\n";
    return 0;
}

