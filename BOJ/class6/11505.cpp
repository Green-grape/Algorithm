#include <iostream>
#include <vector>
#include <cstdio>
#include <tuple>

const int MOD=1000000007;

using namespace std;

vector<int> tree;
vector<int> arr;

//return {k,{x,y}}, ax+by=k
pair<int,pair<int,int>> xGCD(int a, int b){
    if(b==0) return {a,{1,0}};
    pair<int, pair<int,int>> nextGCD=xGCD(b,a%b);
    int k,x,y;
    k=nextGCD.first;
    tie(x,y)=nextGCD.second;
    return {k,{y,x-(a/b)*y}};
}

int getModuloInverse(int x){
    pair<int,pair<int,int>> ret=xGCD(x,MOD);
    if(ret.first>1) return -1;
    return (ret.second.first+MOD)%MOD;
}

void makeTree(int treeIdx, int left, int right){
    if(left>right) return;
    if(left==right){
        tree[treeIdx]=arr[left];
        return;
    }
    int mid=(left+right)/2;
    makeTree(treeIdx*2, left, mid);
    makeTree(treeIdx*2+1,mid+1,right);
    tree[treeIdx]=((tree[treeIdx*2]%MOD)*((long long int)tree[treeIdx*2+1]%MOD))%MOD;
}

void updateTree(int arrLeft, int arrRight, int treeIdx, int &arrIdx, int &div, int &mul){
    if(arrLeft<=arrIdx && arrIdx<=arrRight){
        tree[treeIdx]=((((tree[treeIdx]%MOD)*((long long int)getModuloInverse(div)%MOD))%MOD)*(mul%MOD))%MOD;
        //tree[treeIdx]=(tree[treeIdx]/div)*mul;
        if(arrLeft!=arrRight){
            int mid=(arrLeft+arrRight)/2;
            updateTree(arrLeft,mid,treeIdx*2, arrIdx, div, mul);
            updateTree(mid+1,arrRight,treeIdx*2+1,arrIdx,div,mul);
        }
    }
}

int getMul(int arrLeft, int arrRight, int treeIdx, int &targetLeft, int &targetRight){
    if(targetLeft>targetRight || targetRight<arrLeft || arrRight<targetLeft) return 1;
    if(targetLeft<=arrLeft  && arrRight<=targetRight) return tree[treeIdx];
    int mid=(arrLeft+arrRight)/2;
    return ((getMul(arrLeft, mid, treeIdx*2, targetLeft, targetRight)%MOD)*((long long int)getMul(mid+1,arrRight,treeIdx*2+1,targetLeft, targetRight)%MOD))%MOD;
}

int main(){
    int length, changeCnt, mulCnt;
    cin >> length >> changeCnt >> mulCnt;
    tree.resize(4*(length+1));   
    arr.resize(length+1);
    for(int i=1;i<arr.size();i++) scanf("%d", &arr[i]);
    makeTree(1, 1, arr.size()-1);
    for(int i=0;i<changeCnt+mulCnt;i++){
        int op,b,c;
        scanf("%d %d %d", &op, &b, &c);
        if(op==1){
            if(arr[b]!=0){
                updateTree(1,arr.size()-1,1,b,arr[b],c);
                arr[b]=c;
            }
            else{
                arr[b]=c;
                makeTree(1,1,arr.size()-1);
            }
        }else if(op==2){
            int ret=getMul(1,arr.size()-1,1,b,c);
            printf("%d\n", ret);
        }
    }
    return 0;
}