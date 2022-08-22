/*
노드 u에서 노드 v로 가는 간선이 존재하면 간선을 u에 대해서는 '나가는 간선', 
v에 대해서는 '들어오는 간선'이라고 하자.

트리라면 다음의 조건들을 만족해야한다.

1. 들어오는 간선이 하나도 없는 단 하나의 노드가 존재한다. 이를 루트(root) 노드라고 부른다.
2. 루트 노드를 제외한 모든 노드는 반드시 단 하나의 들어오는 간선이 존재한다.
3. 루트에서 다른 노드로 가는 경로는 반드시 가능하며, 유일하다. 이는 루트를 제외한 모든 노드에 성립해야 한다.

간선 정보가 주어질때 그 간선 정보들이 트리인지 판단하여라
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct Node{
    int val;
    Node* parent;
    vector<Node*> children;
};

Node* makeNode(int val){
    Node* node=new Node;
    node->val=val;
    node->parent=NULL;
    node->children=vector<Node*>();
    return node;
}

int findCount;
Node* findNode(Node* root, int val){
    if(!root) return NULL;
    Node* ret=NULL;
    if(root->val==val){
        findCount++;
        return root;
    } 
    for(int i=0;i<root->children.size();i++){
        ret=findNode(root->children[i],val);
    }
    return ret;
}

bool isTree(vector<pair<int,int>> edge){
    if(edge.size()==0) return true; //아무것도 없어도 트리이다!
    map<int, Node*> nodes;
    for(int i=0;i<edge.size();i++){
        int start=edge[i].first, end=edge[i].second;
        Node* parent=nodes[start];
        Node* child=nodes[end];
        if(parent==NULL) parent=makeNode(start);
        if(child==NULL) child=makeNode(end);
        parent->children.push_back(child);
        if(child->parent!=NULL) return false;
        child->parent=parent;
        nodes[start]=parent;
        nodes[end]=child;
    }
    Node* root=NULL;
    for(map<int,Node*>::iterator it=nodes.begin();it!=nodes.end();it++){
        if(it->second->parent==NULL){
            if(root!=NULL) return false; //root가 두개 이상
            root=it->second;
        }
    }
    if(root==NULL) return false;
    for(map<int,Node*>::iterator it=nodes.begin();it!=nodes.end();it++){
        findCount=0;
        Node* node=findNode(root,it->first);
        if(findCount!=1) return false;
    }
    return true;
}

int main(){
    int testCase=1;
    int start,end;
    vector<pair<int,int>> edge;
    while(true){
        cin >> start >> end;
        if(start==0 && end==0){
            if(isTree(edge)) cout << "Case "+to_string(testCase)+" is a tree."<<"\n";
            else cout << "Case "+to_string(testCase)+" is not a tree."<<"\n";
            edge.resize(0);
            testCase++;
        }
        else if(start==-1 && end==-1) break;
        else edge.push_back(make_pair(start,end));
    }
    return 0;
}