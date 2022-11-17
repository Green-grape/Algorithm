#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN=500;
long long cache[MAXN][MAXN];
vector<pair<int,int>> matrixs;

long long getMinOperate(int from, int end){
    if(from==end) return 0;
    long long& ret=cache[from][end];
    if(ret!=-1) return ret;
    ret=__LONG_MAX__;
    for(int i=from;i<end;i++){
        ret=min(ret, getMinOperate(from,i)+getMinOperate(i+1,end)+matrixs[from].first*matrixs[i].second*matrixs[end].second);
    }
    //cout << from << " " <<end <<" "<<ret <<"\n";
    return ret;
}

long long solve(){
    memset(cache,-1,sizeof(cache));
    return getMinOperate(0,matrixs.size()-1);
}

int main(){
    int n;
    cin >> n;
    matrixs.resize(n);
    for(int i=0;i<n;i++){
        int r,c;
        scanf("%d %d", &r , &c);
        matrixs[i]={r,c};
    }
    cout << solve() <<"\n";
    return 0;
}