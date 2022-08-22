/*
루트가 있는 트리(rooted tree)가 주어지고, 그 트리 상의 두 정점이 주어질 때 그들의 가장 가까운 공통 조상(Nearest Common Anscestor)을 구하여라.
이때 두 노드의 가장 가까운 공통 조상은, 두 노드를 모두 자손으로 가지면서 깊이가 가장 깊은(즉 두 노드에 가장 가까운) 노드를 말합니다.
*/

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

struct Node{
    int val;
    Node* parent;
};

Node* makeNode(int val){
    Node* node=new Node;
    node->val=val;
    node->parent=NULL;
    return node;
}

void makeTree(vector<Node*>& nodes, vector<pair<int,int>>& edge){
    for(int i=0;i<edge.size();i++){
        int v1=edge[i].first, v2=edge[i].second;
        nodes[v2]->parent=nodes[v1];
    }
}

void getAncestors(vector<int>& ancestor, Node* cur){
    if(cur==NULL) return;
    if(cur->parent!=NULL){
        ancestor.push_back(cur->parent->val);
        getAncestors(ancestor,cur->parent);
    }
}

int solve(int v1, int v2, vector<pair<int,int>>& edge){
    int nodeCount=edge.size()+1;
    vector<Node*> nodes(nodeCount+1);
    for(int i=1;i<nodes.size();i++) nodes[i]=makeNode(i);
    makeTree(nodes,edge);
    vector<int> ancestorV1(1,v1),ancestorV2(1,v2);
    getAncestors(ancestorV1,nodes[v1]);
    getAncestors(ancestorV2,nodes[v2]);
    for(int i=0;i<ancestorV1.size();i++){
        for(int j=0;j<ancestorV2.size();j++){
            if(ancestorV1[i]==ancestorV2[j]) return ancestorV1[i];
        }
    }
    return -1;
}

int main(){
    int testCase;
    cin >> testCase;
    while(testCase--){
        int nodeCount;
        cin >> nodeCount;
        vector<pair<int,int>> edge(nodeCount-1);
        for(int i=0;i<edge.size();i++){
            int start, end;
            scanf("%d %d", &start, &end);
            edge[i]=make_pair(start,end);
        }
        int target1,target2;
        cin >> target1 >> target2;
        cout << solve(target1, target2, edge) <<"\n";
    }
    return 0;
}
