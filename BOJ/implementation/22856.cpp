#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

struct Node{
    int val;
    Node* parent;
    Node* left;
    Node* right;
};

vector<Node*> tree;
vector<bool> isVisit;
vector<int> ret;
int endPoint;
bool isEnd=false;

Node* makeNode(int val){
    Node* node=new Node;
    node->val=val;
    node->parent=NULL;
    node->left=NULL;
    node->right=NULL;
    return node;
}

void inOrder(Node* root){ //중위 순회 끝 찾기
    if(root->left!=NULL) inOrder(root->left);
    endPoint=root->val;
    if(root->right!=NULL) inOrder(root->right);
}

void inOrderPath(Node* root){
    if(isEnd) return;
    isVisit[root->val]=true;
    ret.push_back(root->val);
    if(root->left!=NULL && !isVisit[root->left->val] && !isEnd){
        inOrderPath(root->left);
        if(!isEnd) ret.push_back(root->val);
    }
    if(root->right!=NULL && !isVisit[root->right->val] && !isEnd){
        inOrderPath(root->right);
        if(!isEnd) ret.push_back(root->val);
    }
    if(root->val==endPoint){
        isEnd=true;
    }
    if(root->parent!=NULL && !isEnd) inOrderPath(root->parent);
}

int main(){
    int nodeCount;
    cin >>nodeCount;
    tree.resize(nodeCount+1);
    isVisit.resize(nodeCount+1);
    for(int i=0;i<=nodeCount;i++){
        tree[i]=makeNode(i);
    }
    for(int i=0;i<nodeCount;i++){
        int parent,left,right;
        scanf("%d %d %d", &parent, &left, &right);
        if(left!=-1){
            tree[left]->parent=tree[parent];
            tree[parent]->left=tree[left];
        }
        if(right!=-1){
            tree[right]->parent=tree[parent];
            tree[parent]->right=tree[right];
        }
    }
    inOrder(tree[1]);
    inOrderPath(tree[1]);
    cout << ret.size()-1<<"\n";
    return 0;
}