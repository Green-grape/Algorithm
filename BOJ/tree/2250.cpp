/*
노드의 레벨=노드의 깊이+1
트리의 레벨별 너비=같은 레벨에서의 노드에서 position차이의 최대값
*/

#include <stdio.h>
#include <vector>
#include <iostream>

const int MAXN=10000;
const int INF=987654321;

using namespace std;

struct Node{
    int val;
    int level;
    Node* parent;
    Node* left;
    Node* right;
};

vector<pair<int,int>> children;
vector<int> inorder;

void makeInorder(Node* cur){
    if(cur==NULL) return;
    makeInorder(cur->left);
    inorder.push_back(cur->val);
    makeInorder(cur->right);
}

Node* makeNode(int val){
    Node* node=new Node;
    node->val=val;
    node->parent=NULL;
    node->left=NULL;
    node->right=NULL;
    return node;
}

Node* makeTree(vector<Node*>& nodes){
    for(int i=1;i<nodes.size();i++){
        int left=children[i].first,right=children[i].second;
        if(left!=-1){
            nodes[i]->left=nodes[left];
            nodes[left]->parent=nodes[i];
        }
        if(right!=-1){
            nodes[i]->right=nodes[right];
            nodes[right]->parent=nodes[i];
        }
    }
    Node* root=NULL;
    for(int i=1;i<nodes.size();i++){
        if(nodes[i]->parent==NULL){
            root=nodes[i];
            break;
        }
    }
    return root;
}

int nodeLevel(Node* cur){
    if(cur->parent==NULL) return 1;
    return 1+nodeLevel(cur->parent);
}

pair<int,int> solve(int nodeCount){
    vector<Node*> nodes(nodeCount+1);
    for(int i=1;i<nodes.size();i++) nodes[i]=makeNode(i);
    Node* root=makeTree(nodes);
    makeInorder(root);
    vector<int> pos(nodeCount+1);
    for(int i=0;i<inorder.size();i++){
        pos[inorder[i]]=i+1;
    }
    vector<int> posMin(MAXN+2,INF); //posMin[i]=i레벨에서 pos가 가장 작은 노드
    vector<int> posMax(MAXN+2,0);
    int maxWidth=1,targetlevel=1;
    for(int i=1;i<nodes.size();i++){
        int level=nodeLevel(nodes[i]);
        int p=pos[nodes[i]->val];
        if(posMin[level]==INF){
            posMin[level]=p;
        }
        if(posMax[level]==0){
            posMax[level]=p;
        }
        if(posMin[level]>p) posMin[level]=p;
        if(posMax[level]<p) posMax[level]=p;
    }
    for(int i=1;i<MAXN+2;i++){
        int width=posMax[i]-posMin[i]+1;
        if(maxWidth<width){
            maxWidth=width;
            targetlevel=i;
        }
    }
    return make_pair(targetlevel,maxWidth);
}

int main(){
    int nodeCount;
    scanf("%d", &nodeCount);
    children.resize(nodeCount+1);
    for(int i=1;i<children.size();i++){
        int node,left,right;
        scanf("%d %d %d", &node, &left, &right);
        children[node]=make_pair(left,right);
    }
    pair<int,int> ret=solve(nodeCount);
    cout << ret.first <<" "<< ret.second<<"\n";
    return 0;
}