#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

class RMQ{
private:
    static const int INF=987654321;
    vector<int> arr, tree;
    void update(int node, int left, int right, int idx, int val){
        if(left<=idx && idx<=right){
            tree[node]=min(tree[node],val);
            int mid=(left+right)/2;
            update(node*2, left, mid, idx, val);
            update(node*2+1,mid+1, right, idx,val);
        }
    }
    int query(int node, int nodeLeft, int nodeRight, int left, int right){
        if(right<nodeLeft || nodeRight<left) return INF;
        if(left<=nodeLeft && nodeRight<=right) return tree[node];
        int nodeMid=(nodeLeft+nodeRight)/2;
        return min(query(node*2, nodeLeft, nodeMid, left,right),query(node*2+1, nodeMid+1,nodeRight, left,right));
    }
public:
    RMQ(vector<int> arr){
        this->arr=arr;
        tree=vector<int>(4*arr.size());
        makeTree(1,0,arr.size()-1);
    }
    int makeTree(int node, int left, int right){
        if(left==right){return tree[node]=arr[left];}
        int mid=(left+right)/2;
        return tree[node]=min(makeTree(node*2, left, mid), makeTree(node*2+1, mid+1,right));
    }
    void update(int idx, int val){
        update(1,0,arr.size()-1,idx,val);
        arr[idx]=val;
    }
    int query(int left, int right){
        return query(1,0,arr.size()-1,left,right);
    }
};

int main(){
    int testcase;
    cin >> testcase;
    while(testcase){
        int arrSize, opCnt;
        cin >> arrSize >> opCnt;
        vector<int> arr(arrSize),negArr(arrSize);
        for(int i=0;i<arrSize;i++){
            scanf("%d", &arr[i]);
            negArr[i]=-arr[i];
        }
        RMQ minTree=RMQ(arr),maxTree=RMQ(negArr);
        for(int i=0;i<opCnt;i++){
            int start, end;
            scanf("%d %d", &start, &end);
            int minVal=minTree.query(start,end), maxVal=-maxTree.query(start,end);
            cout << maxVal-minVal <<"\n";
        }
        testcase--;
    }
}