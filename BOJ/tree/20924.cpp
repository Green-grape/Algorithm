/*
기가 노드: 루트 노드에서 순회를 시작했을때, 처음으로 자식 노드가 2개 이상인 노드
기둥의 길이=루트 노드~기가 노드까지의 길이
가지의 길이=기가 노드~임의의 리프노드까지의 길이
라고 할때 기둥의 길이와 가장 긴 가지의 길이를 구하시오
*/

#include <stdio.h>
#include <vector>
#include <iostream>

const int MAXN=200000;
const int INF=987654321;

using namespace std;

vector<int> maxBranchFrom(MAXN+1,0);
vector<int> column;
vector<vector<pair<int,int>>> edge(MAXN+1,vector<pair<int,int>>());
vector<bool> isVisit(MAXN+1,false);
int gigaNode=0;
int rootNode;

int dfs(int cur){ //cur->임의의 leaf노드까지 가장 긴 가지의 길이
    if(isVisit[cur]) return -INF;
    isVisit[cur]=true;
    if(gigaNode==0 && edge[cur].size()<=2){
        column.push_back(cur);
    }
    if(gigaNode==0 && (edge[cur].size()>2 || (cur==rootNode && edge[cur].size()>=2))){
        gigaNode=cur;
        if(edge[cur].size()>2) column.push_back(cur);
    }
    int &ret=maxBranchFrom[cur];
    for(int i=0;i<edge[cur].size();i++){
        int next=edge[cur][i].first;
        int cost=edge[cur][i].second;
        ret=max(ret,cost+dfs(next));
    }
    return ret;
}

pair<int,int> solve(){
    dfs(rootNode);
    int maxBranch=maxBranchFrom[gigaNode];
    int columnLength=0;
    for(int i=1;i<column.size();i++){
        int v1=column[i-1],v2=column[i];
        for(int j=0;j<edge[v1].size();j++){
            if(v2==edge[v1][j].first) columnLength+=edge[v1][j].second;
        }
    }
    return make_pair(columnLength,maxBranch);
}

int main(){
    int nodeCount;
    cin >> nodeCount >> rootNode;
    for(int i=0;i<nodeCount-1;i++){
        int start, end,cost;
        scanf("%d %d %d", &start, &end, &cost);
        edge[start].push_back(make_pair(end,cost));
        edge[end].push_back(make_pair(start,cost));
    }
    pair<int,int> ret=solve();
    cout << ret.first <<" "<<ret.second<<"\n";
    return 0;
}