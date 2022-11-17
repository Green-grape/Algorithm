#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> cost;
vector<vector<int>> cache;
const int INF=987654321;
int n;

//cache초기화 고려
//사이클이 아니라서 어디서 시작해도 같은 답이나온다.

int getMincost(int& start, int cur, int status){
    if(status==((1<<n)-1)){
        return cost[cur][start];
    }
    int& ret=cache[cur][status];
    if(ret!=-1) return ret;
    ret=INF;
    for(int i=0;i<n;i++){
        if((status & (1<<i))!=0) continue;
        ret=min(ret, min(INF,cost[cur][i]+getMincost(start, i, status + (1<<i))));
    }
    return ret;
}

int solve(){
    int ret=INF;
    for(int i=0;i<n;i++){
        cache=vector<vector<int>>(n,vector<int>(1<<n,-1));
        ret=min(ret, getMincost(i, i,1<<i));
    }
    return ret;
}

int main(){
    cin >> n;
    cost=vector<vector<int>>(n,vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d", &cost[i][j]);
            if(i!=j && cost[i][j]==0) cost[i][j]=INF;
        }
    }
    cout << solve() <<"\n";
    return 0;
}