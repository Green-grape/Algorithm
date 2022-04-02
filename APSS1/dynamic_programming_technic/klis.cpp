#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

const int MAX_ELEMENT=500;
const int MAX_K=2e9+1;
using namespace std;
int cache[MAX_ELEMENT];
vector<vector<pair<int,int>>> lisNexts;
int lisCountFrom[MAX_ELEMENT];
int arr[MAX_ELEMENT];
int elementCount;

vector<int> getKthLis(int start, int kth);
void init();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int kth;
        cin >> elementCount >> kth;
        for(int j=0;j<elementCount;j++){
            cin >> arr[j];
        }
        init();
        vector<int> ret=getKthLis(-1,kth);
        reverse(ret.begin(),ret.end());
        cout << ret.size() <<"\n";
        for(int j=0;j<ret.size();j++) cout <<ret[j]<<" ";
    }
    return 0;
}

void init(){
    memset(cache,-1,sizeof(cache));
    lisNexts=vector<vector<pair<int,int>>>(MAX_ELEMENT,vector<pair<int,int>>());
    memset(lisCountFrom,0,sizeof(lisCountFrom));
}

//start부터 시작하는 lis의 길이, lis의 개수 반환 
//feedback:overflow 주의!!
pair<int,int> getLisFrom(int start){
    int& lisLength=cache[start];
    if(lisLength!=-1) return make_pair(lisLength, lisCountFrom[start]);
    lisLength=1;
    lisCountFrom[start]=1;
    for(int i=start+1;i<elementCount;i++){
        if(arr[start]<arr[i]){
            pair<int,int> lisNext=getLisFrom(i);
            lisNext.first+=1;
            if(lisLength<lisNext.first){
                lisLength=lisNext.first;
                lisNexts[start].resize(0);
                lisNexts[start].push_back(make_pair(arr[i],i));
                lisCountFrom[start]=min(MAX_K,lisNext.second);
            }else if(lisLength==lisNext.first){
                lisNexts[start].push_back(make_pair(arr[i],i));
                lisCountFrom[start]=min((long long)MAX_K,(long long)lisCountFrom[start]+lisNext.second);
            }
        }
    }
    sort(lisNexts[start].begin(),lisNexts[start].end());
    return make_pair(lisLength, lisCountFrom[start]);
}

//start부터의 lis의 시작점의 인덱스와 실제값 반환 first:실제값, second:인덱스
vector<pair<int,int>> getLisStart(int start){
    vector<pair<int,int>> ret;
    int lisLength=0;
    for(int i=start;i<elementCount;i++){
        pair<int,int> lisNext=getLisFrom(i);
        if(lisLength<lisNext.first){
            lisLength=lisNext.first;
            ret.resize(0);
            ret.push_back(make_pair(arr[i],i));
        }
        else if(lisLength==lisNext.first) ret.push_back(make_pair(arr[i],i));
    }
    sort(ret.begin(),ret.end());
    return ret;
}

//k번째 LIS 반환
//start:현재까지 추가된 LIS 구성값중 가장 마지막 숫자의 인덱스(시작시 start=-1)
vector<int> getKthLis(int start, int kth){
    if(kth<=0) return vector<int>();
    if(start!=-1 && lisNexts[start].size()==0) return vector<int>();

    vector<pair<int,int>> lisStart;
    if(start==-1) lisStart=getLisStart(0);
    else lisStart=lisNexts[start];
    vector<int> ret;
    for(int i=0;i<lisStart.size();i++){
        if(lisCountFrom[lisStart[i].second]<kth) kth-=lisCountFrom[lisStart[i].second];
        else{
            ret=getKthLis(lisStart[i].second,kth);
            ret.push_back(lisStart[i].first);
            return ret;
        }
    }
    return vector<int>(1,-1);
}



