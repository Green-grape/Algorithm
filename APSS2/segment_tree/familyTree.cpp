#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> children;
vector<int> serialToNumber;
vector<int> numberToSerial;
vector<int> locInTrip;
vector<int> trip;
vector<int> depth;

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


void preorder(int cur,int d, int& curSerial){
    serialToNumber[curSerial]=cur;
    numberToSerial[cur]=curSerial;
    locInTrip[cur]=trip.size();
    trip.push_back(numberToSerial[cur]);
    depth[cur]=d;
    curSerial++;
    for(int i=0;i<children[cur].size();i++){
        preorder(children[cur][i],d+1,curSerial);
        trip.push_back(numberToSerial[cur]);
    }
}

RMQ precal(int n){
    int serial=0;
    serialToNumber.resize(n);
    numberToSerial.resize(n);
    locInTrip.resize(n);
    depth.resize(n);
    preorder(0,0,serial);
    return RMQ(trip);
}

int solve(RMQ rmq, int start, int end){
    int ls=locInTrip[start], le=locInTrip[end];
    if(ls>le) return solve(rmq, end,start);
    int lca=serialToNumber[rmq.query(ls,le)];
    return depth[start]+depth[end]-2*depth[lca];
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase){
        int arrSize,opCnt;
        cin >> arrSize >> opCnt;
        children.resize(arrSize);
        for(int i=1;i<arrSize;i++){
            int parent;
            scanf("%d", &parent);
            children[parent].push_back(i);
        }
        RMQ rmq=precal(arrSize);
        for(int i=0;i<opCnt;i++){
            int start, end;
            scanf("%d %d", &start, &end);
            cout << solve(rmq, start, end)<<"\n";
        }
        testcase--;
    }
    return 0;
}