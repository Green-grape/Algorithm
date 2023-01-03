#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

//각각의 좌표에 대해서 정렬->인접한 좌표는 서로 같은 좌표에 대해서는 가장 가까움을 이용하자.

class Coord{
public:
    int x,y,z;
    Coord(int _x, int _y, int _z){
        x=_x;
        y=_y;
        z=_z;
    }
};

bool cmpX(pair<Coord*,int>c1, pair<Coord*,int> c2){
    return (c1.first)->x<(c2.first)->x;
}

bool cmpY(pair<Coord*,int>c1, pair<Coord*,int> c2){
    return (c1.first)->y<(c2.first)->y;
}

bool cmpZ(pair<Coord*,int>c1, pair<Coord*,int> c2){
    return (c1.first)->z<(c2.first)->z;
}


int getDistance(Coord* c1, Coord* c2){
    return min(min(abs(c1->x-c2->x),abs(c1->y-c2->y)),abs(c1->z-c2->z));
}

void addEdges(char pivot, vector<pair<Coord*,int>>& planets, vector<pair<int,pair<int,int>>>& edges){
    if(pivot=='x') sort(planets.begin(), planets.end(), cmpX);
    else if(pivot=='y') sort(planets.begin(), planets.end(), cmpY);
    else if(pivot=='z') sort(planets.begin(), planets.end(), cmpZ);
    for(int i=1;i<planets.size();i++){
        edges.push_back({getDistance(planets[i-1].first, planets[i].first),{planets[i-1].second, planets[i].second}});
    }
}

int getParent(int cur, vector<int>& parent){
    if(cur==parent[cur]) return cur;
    return parent[cur]=getParent(parent[cur],parent);
}

int unify(int p1, int p2, vector<int>& parent){
    int parent1=getParent(p1,parent);
    int parent2=getParent(p2,parent);
    if(parent1==parent2) return false;
    if(parent1<parent2){
        parent[parent2]=parent1;
    }else if(parent1>parent2){
        parent[parent1]=parent2;
    }
    return true;
}

long long solve(vector<pair<Coord*,int>>& planets){
    vector<pair<int,pair<int,int>>> edges; //{cost, {planet1, planet2}}
    edges.reserve(planets.size()*3);
    addEdges('x',planets,edges);
    addEdges('y',planets,edges);
    addEdges('z',planets,edges);
    vector<int> parent(planets.size());
    for(int i=0;i<parent.size();i++) parent[i]=i;
    long long ret=0;
    sort(edges.begin(), edges.end());
    for(int i=0;i<edges.size();i++){
        int cost=edges[i].first, v1=edges[i].second.first, v2=edges[i].second.second;
        if(unify(v1,v2,parent)){
            ret=ret+cost;
        }
    }
    return ret;
}

int main(){
    int planetCnt;
    cin >> planetCnt;
    vector<pair<Coord*,int>> planets(planetCnt);
    for(int i=0;i<planetCnt;i++){
        int x, y, z;
        scanf("%d %d %d",&x, &y ,&z);
        planets[i]={new Coord(x,y,z),i};
    }
    long long ret=solve(planets);
    cout << ret <<"\n";
    return 0;
}

