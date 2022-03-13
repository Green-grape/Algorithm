#include <vector>
#include <iostream>
#include <string.h>

using namespace std;
const int INF=987654321;
const int MAX_LENGTH=10000;
vector<int> arr;
int cache[MAX_LENGTH];

int getMinDif(int start);
void init();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        string s;
        cin >> s;
        init();
        for(int j=0;j<s.length();j++){
            arr.push_back(s[j]-'0');
        }
        cout << getMinDif(0) <<"\n";
    }
}

void init(){
    arr.resize(0);
    memset(cache,-1,sizeof(cache));
}

int getDif(int start, int end){
    bool isAllSame=true;
    bool isAllIncreaseOne=true;
    bool isAllDecreaseOne=true;
    bool isAlternative=true;
    bool isHaveSameDif=true;
    for(int i=start;i<end;i++){
        if(arr[i]!=arr[i+1]) isAllSame=false;
        if(arr[i+1]-arr[i]!=1) isAllIncreaseOne=false;
        if(arr[i+1]-arr[i]!=-1) isAllDecreaseOne=false;
        if(i<end-2 && arr[i]!=arr[i+2]) isAlternative=false;
        if(i<end-2 && arr[i]-arr[i+1]!=arr[i+1]-arr[i+2]) isHaveSameDif=false;
    }
    if(isAllSame) return 1;
    if(isAllIncreaseOne || isAllDecreaseOne) return 2;
    if(isAlternative) return 4;
    if(isHaveSameDif) return 5;
    return 10;
}

int getMinDif(int start){
    int& ret=cache[start];
    if(ret!=-1) return ret;
    if(arr.size()-start<=5) return ret=getDif(start,arr.size()-1);
    ret=INF;
    for(int i=3;i<=5;i++){
        if(start+i-1<arr.size()) ret=min(ret,getDif(start,start+i-1)+getMinDif(start+i));
    }
    return ret;
}