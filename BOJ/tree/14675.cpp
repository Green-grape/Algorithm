/*
그래프 이론에서 단절점(cut nth)과 단절선(bridge)은 다음과 같이 정의 된다.

단절점(cut nth) : 해당 정점을 제거하였을 때, 그 정점이 포함된 그래프가 2개 이상으로 나뉘는 경우, 이 정점을 단절점이라 한다.
단절선(bridge) : 해당 간선을 제거하였을 때, 그 간선이 포함된 그래프가 2개 이상으로 나뉘는 경우, 이 간선을 단절선이라 한다.
이 단절점과 단절선을 우리는 트리(tree)에서 구하려고 한다. 그래프 이론에서 트리(tree)의 정의는 다음과 같다.

트리(tree) : 사이클이 존재하지 않으며, 모든 정점이 연결되어 있는 그래프

이때 해당 점과 간선이 각각 단절점과 단절선인지 판단하시오
*/

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

struct Node{
    int val;
    vector<Node*> next;
};

Node* makeNode(int val){
    Node* node=new Node;
    node->val=val;
    node->next=vector<Node*>();
    return node;
}

void makeTree(vector<Node*>& nodes, vector<pair<int,int>> edge){
    for(int i=0;i<edge.size();i++){
        int v1=edge[i].first, v2=edge[i].second;
        nodes[v1]->next.push_back(nodes[v2]);
        nodes[v2]->next.push_back(nodes[v1]);
    }
}

int main(){
    int nodeCount;
    cin >> nodeCount;
    vector<pair<int,int>> edge;
    for(int i=0;i<nodeCount-1;i++){
        int start,end;
        scanf("%d %d", &start, &end);
        edge.push_back(make_pair(start,end));
    }
    vector<Node*> nodes(nodeCount+1);
    for(int i=1;i<nodes.size();i++) nodes[i]=makeNode(i);
    makeTree(nodes,edge);
    int questionCount;
    cin >> questionCount;
    for(int i=0;i<questionCount;i++){
        int question,nth;
        scanf("%d %d", &question, &nth);
        if(question==1){
            Node* node=nodes[nth];
            if(node->next.size()==1) cout <<"no"<<"\n";
            else cout << "yes"<<"\n";
        }else{
            cout << "yes" <<"\n";
        }
    }
    return 0;
}




