#include <iostream>
#include <vector>

using namespace std;

const int MOD=1000000000;

int n;
vector<vector<vector<pair<int,int>>>> cache;
//계단수: 모든 인접한 자리의 수의 차가 1인 수 ex)45656
//현재 수가 cur이고 길이가 length이고 사용한 숫자가 taken일때 앞으로 만들어질 계단 수의 개수는?
pair<int,int> getStairNumberCnt(int cur, int length, int taken){
    if(length==n){
        if(taken==(1<<10)-1) return {1,1};
        return {0,0};
    }
    pair<int,int> &ret=cache[cur][length][taken];
    if(ret.first!=-1) return ret;
    ret={0,0};
    if(0<cur){
        pair<int,int> cand=getStairNumberCnt(cur-1,length+1, taken | (1<<(cur-1)));
        if(cand.second){
            ret.first=(ret.first%MOD+cand.first%MOD)%MOD;
            ret.second=1;
        }
    }
    if(cur<9){
        pair<int,int> cand=getStairNumberCnt(cur+1,length+1, taken | (1<<(cur+1)));
        if(cand.second){
            ret.first=(ret.first%MOD+cand.first%MOD)%MOD;
            ret.second=1;
        }
    }
    return ret;
}

int solve(){
    int ret=0;
    cache=vector<vector<vector<pair<int,int>>>>(10, vector<vector<pair<int,int>>>(n,vector<pair<int,int>>(1<<10,{-1,-1})));    
    for(int i=1;i<=9;i++){
        ret=(ret%MOD+getStairNumberCnt(i,1,1<<i).first%MOD)%MOD;
    }
    return ret%MOD;
}

int main(){
    cin >> n;
    cout << solve() <<"\n";
    return 0;
}

