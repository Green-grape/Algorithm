#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int MAX_ELEMENT=500;
const int MAX_K=2e9+1;
const int MIN_INF=-987654321;
int cacheLen[MAX_ELEMENT+1];
int cacheCount[MAX_ELEMENT+1];
int arr[MAX_ELEMENT+1]; //arr[0]=-INF;
int elementCount;

int main(){

}

int getLis(int start){
    int& ret=cacheLen[start+1];
    if(ret!=-1) return ret;
    ret=1;
    for(int i=start+1;i<elementCount;i++){
        if(start==-1 || arr[start]<arr[i]){
            ret=max(ret,1+getLis(i));
        }
    }
    return ret;
}

int count(int start){
    if(getLis(start)==1) return 1;
    int& ret=cacheCount[start+1];
    ret=0;
    for(int i=start+1;i<elementCount;i++){
        if((start==-1 || arr[start]<arr[i]) && (getLis(start)==getLis(i)+1)){
            ret=min<long long>(MAX_K, (long long)ret+count(i));
        }
    } 
    return ret;
}

void reconstruct(int start, int k, vector<int>& lis){
    if(start!=-1) lis.push_back(arr[start]);
    vector<pair<int,int>> next;
    for(int i=start+1;i<elementCount;i++){
        if((start==-1 || arr[start]<arr[i]) && (getLis(start)==getLis(i)+1)){
            next.push_back(make_pair(arr[i],i));
        }
    }
    sort(next.begin(),next.end());
    for(int i=0;i<next.size();i++){
        int idx=next[i].second;
        int cnt=count(idx);
        if(cnt<=k) k-=cnt;
        else{
            lis.push_back(arr[idx]);
            reconstruct(idx,k,lis);
            break;
        }
    }
}



