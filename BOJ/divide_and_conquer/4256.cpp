/*(전위 순회)preorder(root node of BT)와 (중위 순회)inorder(root node of BT)를 호출해서 만든 리스트
가 주어질때 후위 순회한 결과는?
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>

using namespace std;

struct Node{
    int val;
    Node* left=NULL;
    Node* right=NULL;
};

vector<int> preorder;
vector<int> inorder;

Node* makeNode(int val){
    Node* node=new Node;
    node->val=val;
    return node;
}

Node* makeTree(int preStart,int preEnd, int inStart, int inEnd){//start~end까지의 preorder과 inorder를 읽어서 BT를 구성한다.
    if(preStart>preEnd || inStart>inEnd) return NULL;
    Node* root=makeNode(preorder[preStart]);
    int pivot=find(inorder.begin(),inorder.end(),preorder[preStart])-inorder.begin(); //root가 inorder에 어디 있는가?
    root->left=makeTree(preStart+1,preStart+pivot-inStart,inStart,pivot-1); //pivot기준으로 자름(왼쪽)
    root->right=makeTree(preStart+pivot-inStart+1,preEnd,pivot+1,inEnd); //pivot기준으로 자름(오른쪽)
    return root;
}

void postOrder(Node* root){
    if(root->left!=NULL) postOrder(root->left);
    if(root->right!=NULL) postOrder(root->right);
    cout << root->val <<" ";
}

int main(){
    int testCase;
    cin >> testCase;
    while(testCase--){
        int treesize;
        cin >> treesize;
        preorder.resize(treesize);
        inorder.resize(treesize);
        for(int i=0;i<treesize;i++) scanf("%d", &preorder[i]);
        for(int i=0;i<treesize;i++) scanf("%d", &inorder[i]);
        Node* root=makeTree(0,treesize-1,0,treesize-1);
        postOrder(root);
        cout <<"\n";
        //init
        preorder.resize(0);
        inorder.resize(0);
    }
    return 0;
}
