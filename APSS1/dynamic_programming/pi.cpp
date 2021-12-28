#include <iostream>
#include <vector>
#include <string>
#include "string.h"

#define MAX_ARR_LENGTH 10000
#define INF 987654321

using namespace std;

int cache[MAX_ARR_LENGTH];
int getDif(vector<int>);
int getMinDif(vector<int>&, int idx);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        string s;
        vector<int> arr;
        cin >> s;
        for(int i=0;i<s.length();i++){
            arr.push_back(s[i]-'0');
        }
        memset(cache,-1,sizeof(cache));
        cout << getMinDif(arr,arr.size()-1)<< "\n";
    }
    return 0;
}

//s에 해당하는 수열의 난이도 반환
int getDif(vector<int> arr){
    bool isAllSame=true;
    bool isHaveSameDif=true;
    bool isHaveAllOneDif=true; 
    bool isHaveAllNegOneDif=true;   
    bool isHaveAlternativeNum=true;
    for(int i=1;i<arr.size();i++){
        if(arr[i-1]!=arr[i]) isAllSame=false;
        if((arr[i-1]-arr[i])!=-1) isHaveAllOneDif=false;
        if((arr[i-1]-arr[i])!=1) isHaveAllNegOneDif=false;
        if(i<arr.size()-1){
            if((arr[i-1]-arr[i])!=(arr[i]-arr[i+1])){
                isHaveSameDif=false;
            }
        }
        if(i>=2){
            if(arr[i]!=arr[i-2]) isHaveAlternativeNum=false;
        }
    }
    int ret;
    if(isAllSame) ret=1;
    else if(isHaveAllNegOneDif || isHaveAllOneDif) ret=2;
    else if(isHaveAlternativeNum) ret=4;
    else if(isHaveSameDif) ret=5;
    else ret=10;
    return ret;
}

int getMinDif(vector<int>& arr, int idx){
    int& ret=cache[idx];
    if(ret!=-1) return ret;
    if(idx<=4) return ret=getDif({&arr[0],&arr[idx+1]});
    ret=INF;
    for(int i=3;i<=5;i++){
        if(idx-i>=2){
            ret=min(ret,getMinDif(arr,idx-i)+getDif({&arr[idx-i+1],&arr[idx+1]}));
        }
    }
    return ret; 
}

