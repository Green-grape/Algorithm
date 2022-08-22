/*
리의 1번 정점에는 W만큼의 물이 고여 있다. 1번 정점을 제외한 모든 정점에는 아직 물이 고여 있지 않은 상태이다.

이제 매초마다 모든 정점은 아래의 작업을 순서대로 반복한다.

물을 가지고 있으며, 자식 정점이 있다면 자식 정점 중 하나를 골라 물을 1 준다. 자식 정점이 여러 개라면 동일한 확률로 그 중 하나를 고른다.
만약 부모 정점이 자신에게 물을 흘려보냈다면 받아서 쌓아 둔다.
이때, 위 작업은 순서대로 진행되므로 부모 정점에게 받은 물을 즉시 자식 정점에게 줄 수는 없다.

영훈이는 나무를 바라보면서 더 이상 물이 움직이지 않는 상태가 되었을 때 각 정점에 어느 정도의 물이 있게 될지 궁금해졌다. 
더 이상 물이 움직이지 않을 때, i번 정점에 쌓인 물의 양의 기댓값을 Pi라 하자. 이때, Pi가 0보다 큰 정점들에 대해서 Pi들의 평균은 어느 정도가 될까?
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <stdio.h>


using namespace std;

struct Node{
    int val;
    vector<Node*> next;
};

vector<Node*> nodes; //nodes[i]=i번째 노드와 연결된 노드

Node* makeNode(int val){
    Node* node=new Node;
    node->val=val;
    node->next=vector<Node*>();
    return node;
}

void makeTree(vector<Node*> node, vector<pair<int,int>>& edge){
    for(int i=0;i<edge.size();i++){
        int v1=edge[i].first, v2=edge[i].second;
        nodes[v1]->next.push_back(nodes[v2]);
        nodes[v2]->next.push_back(nodes[v1]);
    }
}

void init(int nodeCount){
    nodes.resize(nodeCount+1);
    for(int i=1;i<nodes.size();i++) nodes[i]=makeNode(i);
}

double solve(int nodeCount,double totalWeight,vector<pair<int,int>>& edge){
    init(nodeCount);
    makeTree(nodes,edge);
    int leafCount=0;double weightSum=0;
    for(int i=2;i<nodes.size();i++){
        if(nodes[i]->next.size()==1){
            leafCount++;
        }
    }
    return totalWeight/leafCount;
}

int main(){
    int nodeCount;double totalWeight;
    cin >> nodeCount >> totalWeight;
    vector<pair<int,int>> edge;
    for(int i=0;i<nodeCount-1;i++){
        int v1,v2;
        scanf("%d %d",&v1,&v2);
        edge.push_back(make_pair(v1,v2));
    }
    cout << fixed;
    cout.precision(6);
    cout << solve(nodeCount, totalWeight, edge) <<"\n";
    return 0;
}   



