#include <iostream>
#include <vector>

using namespace std;

const int INF=987654321;

vector<vector<int>> costs;
vector<vector<vector<int>>> cache;

int getCost(int cur, int prevColor, int startColor){
    if(cur==costs.size()-1){
        int ret=INF;
        for(int i=0;i<3;i++){
            if(i!=prevColor && i!=startColor){
                ret=min(ret,costs[cur][i]);
            }
        }
        return ret;
    }
    int& ret=cache[cur][prevColor+1][startColor+1];
    if(ret!=-1) return ret;
    ret=INF;
    for(int i=0;i<3;i++){
        if(i!=prevColor){
            ret=min(ret,costs[cur][i]+getCost(cur+1,i,cur==0 ? i:startColor));
        }
    }
    return ret;
}

int solve(){
    cache=vector<vector<vector<int>>>(costs.size(), vector<vector<int>>(4, vector<int>(4,-1)));
    return getCost(0,-1,-1);
}

int main(){
    int n;
    cin >> n;
    costs.resize(n);
    for(int i=0;i<n;i++){
        costs[i].resize(3);
        for(int j=0;j<3;j++){
            scanf("%d", &costs[i][j]);
        }
    }
    cout << solve() <<"\n";
    return 0;
}