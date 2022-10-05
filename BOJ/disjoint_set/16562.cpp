#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> parent, friendPay;

int getParent(int child){
    if(parent[child]==child) return child;
    return parent[child]=getParent(parent[child]);
}

void unify(int n1, int n2){
    int p1=getParent(n1), p2=getParent(n2);
    if(p1==p2) return;
    if(friendPay[p1]<friendPay[p2]){
        parent[p2]=p1;
    }else{
        parent[p1]=p2;
    }
}

int getMinTotalFriendPay(){
    vector<int> isVisit(parent.size());
    int ret=0;
    for(int i=1;i<parent.size();i++){
        int cur=getParent(i);
        if(!isVisit[cur]){
            isVisit[cur]=1;
            ret+=friendPay[cur];
        }
    }
    return ret;
}

int main(){
    int nodeCount, edgeCount, maxPay;
    cin >> nodeCount >> edgeCount >> maxPay;
    friendPay=vector<int>(nodeCount+1);
    parent=vector<int>(nodeCount+1);
    for(int i=1;i<parent.size();i++){
        parent[i]=i;
    }
    for(int i=1;i<friendPay.size();i++){
        scanf("%d", &friendPay[i]);
    }
    for(int i=0;i<edgeCount;i++){
        int n1, n2;
        scanf("%d %d", &n1, &n2);
        unify(n1,n2);
    }
    int minTotalFriendPay=getMinTotalFriendPay();
    if(minTotalFriendPay<=maxPay){
        cout << minTotalFriendPay <<"\n";
    }else{
        cout <<"Oh no" <<"\n";
    }
    return 0;
}