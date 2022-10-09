#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<pair<int,int>> vertex;
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

double edgeLength(int v1, int v2){
    return sqrt(pow(vertex[v1].first-vertex[v2].first,2)+pow(vertex[v1].second-vertex[v2].second,2));
}

vector<pair<double, pair<int,int>>> makeEdge(){
    vector<pair<double, pair<int,int>>> ret;
    for(int i=1;i<vertex.size();i++){
        for(int j=i+1;j<vertex.size();j++){
            if(getParent(i)!=getParent(j)) ret.push_back(make_pair(edgeLength(i,j),make_pair(i,j)));
        }
    }
    return ret;
}

double solve(){
    vector<pair<double, pair<int,int>>> edge=makeEdge();
    sort(edge.begin(),edge.end());
    double ret=0;
    for(int i=0;i<edge.size();i++){
        double w=edge[i].first;
        int v1=edge[i].second.first;
        int v2=edge[i].second.second;
        if(getParent(v1)==getParent(v2)) continue;
        unify(v1,v2);
        ret+=w;
    }
    return ret;
}

int main(){
    int vertexCount, edgeCount;
    cin >> vertexCount >> edgeCount;
    vertex.resize(vertexCount+1);
    parent.resize(vertexCount+1);
    for(int i=1;i<parent.size();i++){
        parent[i]=i;
    }
    for(int i=1;i<vertex.size();i++){
        int x, y;
        cin >> x >> y;
        vertex[i]=make_pair(x,y);
    }
    for(int i=0;i<edgeCount;i++){
        int v1, v2;
        cin >> v1 >> v2;
        unify(v1,v2);
    }
    cout << fixed;
    cout.precision(2);
    cout << solve() <<"\n";
    return 0;
}