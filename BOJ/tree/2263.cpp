/*
n개의 정점을 갖는 이진 트리의 정점에 1부터 n까지의 번호가 중복 없이 매겨져 있다. 
이와 같은 이진 트리의 인오더와 포스트오더가 주어졌을 때, 프리오더를 구하는 프로그램을 작성하시오.
*/

#include <stdio.h>
#include <vector>

using namespace std;

vector<int> inorder;
vector<int> postorder;

struct Node{
    int val;
    Node* left;
    Node* right;
};

Node* makeNode(int val){
    Node* node=new Node;
    node->val=val;
    node->left=NULL;
    node->right=NULL;
    return node;
}

Node* makeTree(int inorderStart, int inorderEnd, int postOrderStart, int postOrderEnd){
    Node* root=makeNode(postorder[postOrderEnd]);
    if(inorderStart>=inorderEnd || postOrderStart>=postOrderEnd) return root;
    //makeInorder
    int leftInorderStart=inorderStart,rightInorderStart=inorderStart;
    while(rightInorderStart<=inorderEnd && inorder[rightInorderStart]!=root->val) rightInorderStart++;
    rightInorderStart++;
    int leftInorderEnd=rightInorderStart-2,rightInorderEnd=inorderEnd;    
    //makePostOrder
    int leftPostorderStart=postOrderStart,rightPostorderStart=leftPostorderStart+(leftInorderEnd-leftInorderStart+1);
    int leftPostOrderEnd=max(rightPostorderStart-1,leftPostorderStart),rightPostorderEnd=postOrderEnd-1;
    if(leftInorderStart<=leftInorderEnd && leftPostorderStart<=leftPostOrderEnd) root->left=makeTree(leftInorderStart,leftInorderEnd,leftPostorderStart,leftPostOrderEnd);
    if(rightInorderStart<=rightInorderEnd && rightPostorderStart<=rightPostorderEnd) root->right=makeTree(rightInorderStart,rightInorderEnd,rightPostorderStart,rightPostorderEnd);
    return root;
}

void preOrder(Node* root){
    if(root==NULL) return;
    printf("%d ", root->val);
    preOrder(root->left);
    preOrder(root->right);
}

int main(){
    int nodeCount;
    scanf("%d", &nodeCount);
    inorder.resize(nodeCount);postorder.resize(nodeCount);
    for(int i=0;i<nodeCount;i++) scanf("%d", &inorder[i]);
    for(int i=0;i<nodeCount;i++) scanf("%d", &postorder[i]);
    Node* root=makeTree(0,nodeCount-1,0,nodeCount-1);
    preOrder(root);
    return 0;
}