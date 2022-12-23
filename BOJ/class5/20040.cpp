#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> parent;

int getParent(int x){
    if(parent[x]==x) return x;
    return parent[x]=getParent(parent[x]);
}

bool unionSet(int v1, int v2){
    int p1=getParent(v1), p2=getParent(v2);
    if(p1==p2) return false; //fail
    if(p1<p2){
        parent[p2]=p1;
    }else{
        parent[p2]=p1;
    }
    return true;
}

int main(){
    int vertexCnt, turnCnt;
    cin >> vertexCnt >> turnCnt;
    parent.resize(vertexCnt);
    for(int i=0;i<parent.size();i++){
        parent[i]=i;
    }
    int ret=0;
    for(int i=0;i<turnCnt;i++){
        int v1,v2;
        scanf("%d %d", &v1, &v2);
        if(!unionSet(v1,v2)){
            ret=i+1;
            break;
        }
    }
    cout << ret <<"\n";
    return 0;
}