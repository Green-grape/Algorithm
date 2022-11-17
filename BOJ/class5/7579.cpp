#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

//cost가 작다는 것 주의

using namespace std;

const int MAXN=100;
const int MAXC=100;
vector<pair<int,int>> info;//info[i].first=비어지는 메모리, info[i].second=비용
int cache[MAXN][MAXN*MAXC+1];

int getMaxMem(int cur, int cost){ //현재 cur이고 남은 비용이 cost일때 최대로 비울 수 있는 메모리는
    if(cur==info.size()) return 0;
    if(cache[cur][cost]!=-1) return cache[cur][cost];
    int& ret=cache[cur][cost];
    //cur 선택 x
    ret=getMaxMem(cur+1,cost);
    //cur 선택
    if(info[cur].second<=cost) ret=max(ret, info[cur].first+getMaxMem(cur+1,cost-info[cur].second));
    return ret;
}

int solve(int target){
    memset(cache,-1,sizeof(cache));
    int totalCost=0;
    while(true){
        if(getMaxMem(0,totalCost)>=target){
            break;
        }
        totalCost++;
    }
    return totalCost;
}

int main(){
    int n,target;
    cin >> n >> target;
    info.resize(n);
    for(int i=0;i<n;i++){
        scanf("%d", &info[i].first);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&info[i].second);
    }
    cout << solve(target)<<"\n";
    return 0;
}