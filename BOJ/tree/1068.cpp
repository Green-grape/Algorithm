/*
트리에서 리프 노드란, 자식의 개수가 0인 노드를 말한다.
트리가 주어졌을 때, 노드 하나를 지울 것이다. 
그 때, 남은 트리에서 리프 노드의 개수를 구하는 프로그램을 작성하시오. 
노드를 지우면 그 노드와 노드의 모든 자손이 트리에서 제거된다.
*/

#include <iostream>
#include <vector>

using namespace std;

struct Node{
    int val;
    vector<Node*> children;
};

Node* makeTree(vector<Node*> nodes, vector<int> parent){
    Node* root;
    for(int i=0;i<nodes.size();i++){
        if(parent[i]==-1) root=nodes[i];
        else{
            nodes[parent[i]]->children.push_back(nodes[i]);
        }
    }
    return root;
}

Node* findNode(Node* root, int val){
    if(!root) return NULL;
    Node* ret=NULL;
    if(root->val==val) return root;
    for(int i=0;i<root->children.size();i++){
        if(root->children[i]==NULL) continue;
        if(root->children[i]->val==val){
            ret=root->children[i];
            break;
        }
        else{
            if(ret==NULL) ret=findNode(root->children[i],val);
        }
    }
    return ret;
}

Node* makeNode(int val){
    Node* node=new Node;
    node->val=val;
    node->children=vector<Node*>();
    return node;
}

int solve(vector<int> parent,int target){
    vector<Node*> nodes;
    for(int i=0;i<parent.size();i++) nodes.push_back(makeNode(i));
    Node* root=makeTree(nodes,parent);
    if(parent[target]==-1) return 0;
    for(int i=0;i<nodes[parent[target]]->children.size();i++){
        if(nodes[parent[target]]->children[i]->val==target){
            vector<Node*> front(nodes[parent[target]]->children.begin(), nodes[parent[target]]->children.begin()+i);
            vector<Node*> back(nodes[parent[target]]->children.begin()+i+1, nodes[parent[target]]->children.end());
            nodes[parent[target]]->children=front;
            nodes[parent[target]]->children.insert(nodes[parent[target]]->children.end(), back.begin(),back.end());
            break;
        }
    }
    int ret=0;
    for(int i=0;i<nodes.size();i++){
        Node* node=findNode(root, i);
        if(node==NULL) continue;
        if(node->children.size()==0) ret++;
    }
    return ret;
}

int main(){
    int nodeCount,target;
    cin >> nodeCount;
    vector<int> parent(nodeCount);
    for(int i=0;i<nodeCount;i++){
        cin >> parent[i];
    }
    cin >> target;
    cout << solve(parent, target) <<"\n";
    return 0;
}