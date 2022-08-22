/*
입력으로 루트가 있는 트리를 가중치가 있는 간선들로 줄 때, 트리의 지름(트리의 모든 경로 중에 가장 긴것)을 구해서 출력하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>
#include <stdio.h>

const int INF=987654321;

using namespace std;

struct Node{
    int val;
    vector<pair<int,int>> next;
};

vector<Node*> nodes;

Node* makeNode(int val){
    Node* node=new Node;
    node->val=val;
    node->next=vector<pair<int,int>>();
    return node;
}

void makeTree(vector<pair<pair<int,int>,int>>& edge){
    for(int i=0;i<edge.size();i++){
        int v1=edge[i].first.first, v2=edge[i].first.second, cost=edge[i].second;
        nodes[v1]->next.push_back(make_pair(v2,cost));
        nodes[v2]->next.push_back(make_pair(v1,cost));
    }
}

vector<int> lengthFrom; //lengthFrom[i]=i번째 노드로 부터의 경로중 가장 긴것의 길이
vector<int> isVisit;

int dfs(int cur){
    if(isVisit[cur]) return -INF;
    isVisit[cur]=true;
    lengthFrom[cur]=0;
    for(int i=0;i<nodes[cur]->next.size();i++){
        int next=nodes[cur]->next[i].first;
        int cost=nodes[cur]->next[i].second;
        lengthFrom[cur]=max(lengthFrom[cur],cost+dfs(next));
    }
    return lengthFrom[cur];
}

int solve(int nodeCount, vector<pair<pair<int,int>,int>>& edge){
    nodes.resize(nodeCount+1);
    for(int i=1;i<nodeCount+1;i++) nodes[i]=makeNode(i);
    makeTree(edge);
    int ret=0;
    for(int i=1;i<nodes.size();i++){
        if(nodes[i]->next.size()==1){
            isVisit=vector<int>(nodeCount+1,false);
            lengthFrom=vector<int>(nodeCount+1,0);
            ret=max(ret,dfs(i));
        }
    }
    return ret;
}

int main(){
    int nodeCount;
    cin >> nodeCount;
    vector<pair<pair<int,int>,int>> edge;
    for(int i=0;i<nodeCount-1;i++){
        int v1,v2,cost;
        scanf("%d %d %d", &v1,&v2, &cost);
        edge.push_back(make_pair(make_pair(v1,v2),cost));
    }
    cout << solve(nodeCount,edge)<<"\n";
    return 0;
}