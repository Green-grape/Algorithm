#include <iostream>
#include <stdio.h>

#define MAX_ALLAY_LENGTH 50000

using namespace std;

int arr[MAX_ALLAY_LENGTH];
int moveCount[MAX_ALLAY_LENGTH];

typedef int KeyType;
struct Node{
    KeyType key;
    int priority, size;
    Node* left;
    Node* right;
    Node(KeyType _key): key(_key), priority(rand()),size(1),left(NULL),right(NULL){}
    void setLeft(Node* left) {this->left=left; calSize();}
    void setRight(Node* right) {this->right=right; calSize();}
    void calSize(){
        size=1;
        if(left) size+=left->size;
        if(right) size+=right->size;
    }
};
typedef pair<Node*, Node*> NodePair;

void reverseInsertion(int);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int arrLength;
        cin >> arrLength;
        for(int j=0;j<arrLength;j++){
            scanf("%d", &moveCount[j]);
        }
        reverseInsertion(arrLength);
        for(int j=0;j<arrLength;j++){
            printf("%d ", arr[j]);
        }
        printf("\n");
    }
    return 0;
}

NodePair split(Node* root, KeyType key){
    if(root==NULL) return NodePair(NULL,NULL);
    if(root->key<key){
        NodePair rightSubtree=split(root->right,key);
        root->setRight(rightSubtree.first);
        return NodePair(root, rightSubtree.second);
    }
    NodePair leftSubtree=split(root->left,key);
    root->setLeft(leftSubtree.second);
    return NodePair(leftSubtree.first,root);
}

Node* insertNode(Node* root, KeyType key){
    Node* node=new Node(key);
    if(root==NULL) return node;
    if(root->priority<node->priority){
        NodePair newRootSubtree=split(root,key);
        node->left=newRootSubtree.first;
        node->right=newRootSubtree.second;
        return node;
    }
    if(root->key<key){
        root->setRight(insertNode(root->right, key));
    }
    else{
        root->setLeft(insertNode(root->left,key));
    }
    return root;
}

Node* mergeNode(Node* a, Node* b){
    if(a==NULL) return b;
    if(b==NULL) return a;
    if(a->priority<b->priority){
        b->setLeft(mergeNode(a,b->left));
        return b;
    }
    a->setRight(mergeNode(a->right,b));
    return a;
}

Node* deleteNode(Node* root, KeyType key){
    if(root==NULL) return NULL;
    if(root->key==key){
        Node* temp=root;
        root=mergeNode(root->left,root->right);
        delete temp;
        return root;
    }
    if(root->key<key){
        root->setRight(deleteNode(root->right,key));
    }
    else{
        root->setLeft(deleteNode(root->left,key));
    }
    return root;
}

//k번째 원소 반환
Node* kth(Node* root, int k){
    int leftSize=0;
    if(root->left!=NULL) leftSize=root->left->size;
    if(k<=leftSize) return kth(root->left,k);
    if(k==leftSize+1) return root;
    return kth(root->right,k-leftSize-1);
}

int countLessThan(Node* root,KeyType key){
    if(root==NULL) return 0;
    if(root->key==key){
        if(root->left==NULL) return 0;
        return root->left->size;
    }
    else if(root->key>key){
        return countLessThan(root->left,key);
    }
    else{
        int leftSize=root->left==NULL ? 0:root->left->size;
        return leftSize+1+countLessThan(root->right,key);
    }
}

void reverseInsertion(int arrLength){
    Node* candidate=NULL;
    for(int i=0;i<arrLength;i++){
        candidate=insertNode(candidate,i+1);
    }
    for(int i=0;i<arrLength;i++){
        int movingIdx=arrLength-i-1-moveCount[arrLength-i-1];
        arr[arrLength-i-1]=kth(candidate,movingIdx+1)->key;
        candidate=deleteNode(candidate,arr[arrLength-i-1]);
    }
}

