/*
증가하는 정수 수열을 이용해서 트리를 만드는 방법은 다음과 같다.

1. 첫 번째 정수는 트리의 루트 노드이다.
2. 다음에 등장하는 연속된 수의 집합은 루트의 자식을 나타낸다. 이 집합에 포함되는 수의 첫 번째 수는 항상 루트 노드+1보다 크다.
3. 그 다음부터는 모든 연속된 수의 집합은 아직 자식이 없는 노드의 자식이 된다. 그러한 노드가 여러 가지 인 경우에는 가장 작은 수를 가지는 노드의 자식이 된다.
4. 집합은 수가 연속하지 않는 곳에서 구분된다.

이때 특정 노드의 번호가 주어질때 해당 노드의 사촌 노드의 수는?
(사촌 노드=두 노드의 부모는 다르지만 두 노드의 부모가 형제관계인 노드)
*/

#include <iostream>
#include <stdio.h>
#include <vector>

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

vector<int> arr;
vector<vector<int>> sibling;

// Node* makeTree(){

// }

void makeSibling(){
    sibling.resize(0);
    vector<int> temp;
    for(int i=0;i<arr.size()-1;i++){
        temp.push_back(i);
        if(arr[i]+1!=arr[i+1]){
            sibling.push_back(temp);
            temp.resize(0);
        }
    }
    temp.push_back(arr.size()-1);
    sibling.push_back(temp);
}

Node* findNode(Node* root, int target){
    if(root==NULL) return NULL;
    if(root->val==target) return root;
    Node* ret=NULL;
    for(int i=0;i<root->children.size();i++){
        if(ret==NULL) ret=findNode(root->children[i],target);
    }
    return ret;
}

int solve(int target){
    makeSibling();
    vector<Node*> nodes(arr.size());
    for(int i=0;i<nodes.size();i++) nodes[i]=makeNode(arr[i]);
    int i=0,j=1;
    while(i<arr.size() && j<sibling.size()){
        for(int s=0;s<sibling[j].size();s++){
            int child=sibling[j][s];
            nodes[i]->children.push_back(nodes[child]);
            nodes[child]->parent=nodes[i];
        }
        i++;
        j++;
    }
    Node* targetNode=findNode(nodes[0],target);
    int ret=0;
    for(int i=0;i<arr.size();i++){
        if(arr[i]!=target){
            Node* node=nodes[i];
            //cout << arr[i]<<" "<<node <<"\n";
            if(node->parent!=NULL && targetNode->parent!=NULL && node->parent!=targetNode->parent){
                if(node->parent->parent!=NULL && targetNode->parent->parent!=NULL){
                    if(node->parent->parent==targetNode->parent->parent) ret++;
                }
            }
        }
    }
    return ret;
}

int main(){
    int nodeCount, target;
    while(true){
        cin >> nodeCount >> target;
        if(nodeCount==0 && target==0) break;
        arr.resize(nodeCount);
        for(int i=0;i<arr.size();i++) scanf("%d", &arr[i]);
        cout << solve(target) <<"\n";
        arr.resize(0);
    }
    return 0l;
}
