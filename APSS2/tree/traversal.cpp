/*전위순회, 중위순회의 결과를 바탕으로 후위순회의 결과를 알아내는 방법은?*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printPostOrder(vector<int>&, vector<int>&);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        vector<int> preOrder, inOrder;
        int nodeCount;
        cin >> nodeCount;
        int temp;
        for(int j=0;j<nodeCount;j++){
            cin >> temp;
            preOrder.push_back(temp);
        }
        for(int j=0;j<nodeCount;j++){
            cin >> temp;
            inOrder.push_back(temp);
        }
        printPostOrder(preOrder, inOrder);
    }
    return 0;
}

void printPostOrder(vector<int>& preOrder, vector<int>& inOrder){
    if(preOrder.size()==0) return;
    const int root=preOrder[0];
    const int rootIdx=find(inOrder.begin(), inOrder.end(), root)-inOrder.begin();

    vector<int> leftInOrder(inOrder.begin(), inOrder.begin()+rootIdx);
    vector<int> rightInOrder(inOrder.begin()+rootIdx+1, inOrder.end());

    vector<int> leftPreOrder(preOrder.begin()+1, preOrder.begin()+1+leftInOrder.size());
    vector<int> rightPreOrder(preOrder.begin()+1+leftInOrder.size(), preOrder.end());

    printPostOrder(leftPreOrder, leftInOrder);
    printPostOrder(rightPreOrder, rightInOrder);
    cout << root <<" ";
}