#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> arr;
vector<vector<int>> cacheLis;
vector<int> cacheLds;

int lis(int cur, int end){
    if(cur!=-1 && cur==end-1) return 1;
    if(cacheLis[cur+1][end]!=-1) return cacheLis[cur+1][end];
    
    int& ret=cacheLis[cur+1][end];
    if(cur!=-1) ret=1;
    else ret=0;

    for(int i=cur+1;i<end;i++){
        if(cur==-1 && arr[i]<arr[end]) ret=max(ret,lis(i,end));
        if(cur!=-1 && arr[cur]<arr[i] && arr[i]<arr[end]) ret=max(ret,1+lis(i,end));
    }
    return ret;
}

int lds(int cur){
    if(cur==arr.size()-1) return 1;
    if(cacheLds[cur]!=-1) return cacheLds[cur];
    int& ret=cacheLds[cur];
    ret=1;
    for(int i=cur+1;i<arr.size();i++){
        if(arr[cur]>arr[i]) ret=max(ret,1+lds(i));
    }
    return ret;
}

int solve(){
    cacheLis=vector<vector<int>>(arr.size()+1, vector<int>(arr.size(),-1));
    cacheLds=vector<int>(arr.size(),-1);
    int ret=0;
    for(int i=0;i<arr.size();i++){
        ret=max(ret, lis(-1,i)+lds(i));
    }
    return ret;
}

int main(){
    int arrLength;
    cin >> arrLength;
    arr.resize(arrLength);
    for(int i=0;i<arrLength;i++){
        scanf("%d", &arr[i]);
    }
    cout << solve() <<"\n";
    return 0;
}