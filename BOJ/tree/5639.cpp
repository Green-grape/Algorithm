/*
이진 검색 트리는 다음과 같은 세 가지 조건을 만족하는 이진 트리이다. (노드 개수 <=10000)

1. 노드의 왼쪽 서브트리에 있는 모든 노드의 키는 노드의 키보다 작다.
2 .노드의 오른쪽 서브트리에 있는 모든 노드의 키는 노드의 키보다 크다.
3. 왼쪽, 오른쪽 서브트리도 이진 검색 트리이다.

이진 검색 트리를 전위 순회한 결과가 주어졌을 때, 이 트리를 후위 순회한 결과를 구하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> preOrder;

struct Node{
    int val;
    Node* leftChild;
    Node* rightChild;
};

Node* makeNode(int val){
    Node* node=new Node;
    node->val=val;
    node->leftChild=NULL;
    node->rightChild=NULL;
    return node;
}

Node* makeTree(int start, int end){
    if(start>end) return NULL;
    Node* root=makeNode(preOrder[start]);
    if(start==end) return root;

    int leftStart=start+1,rightStart=start+1;
    while(rightStart<=end && preOrder[start]>preOrder[rightStart]) rightStart++;

    //vector<int> left(preOrder.begin()+leftStart,preOrder.begin()+rightStart);
    //vector<int> right(preOrder.begin()+rightStart,preOrder.end());
    root->leftChild=makeTree(leftStart,rightStart-1);
    root->rightChild=makeTree(rightStart,end);
    return root;
}

void postOrder(Node* root){
    if(root->leftChild) postOrder(root->leftChild);
    if(root->rightChild) postOrder(root->rightChild);
    cout << root->val<<"\n";
}

void solve(vector<int>& preOrder){
    Node* root=makeTree(0,preOrder.size()-1);
    postOrder(root);
}

int main(){
    int val;;
    while(cin >> val){
        preOrder.push_back(val);
    }
    solve(preOrder);
    return 0;
}