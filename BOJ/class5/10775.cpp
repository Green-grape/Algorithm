#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int getParent(int cur, vector<int>& parent){
    if(parent[cur]==cur) return cur;
    return parent[cur]=getParent(parent[cur],parent);
}

int solve(vector<int>& until, int gateCnt){
    vector<int> parent(gateCnt+1);
    for(int i=1;i<parent.size();i++) parent[i]=i;
    int cnt=0;
    for(int i=1;i<until.size();i++){
        int p=getParent(until[i],parent);
        if(p==0) break;
        parent[p]=p-1;
        cnt++;
    }
    return cnt;
}

int main(){
    int gateCnt, planeCnt;
    cin >> gateCnt >> planeCnt;
    vector<int> until(planeCnt+1); //i번째 항공기는 1~until[i]까지 세울수 있다.
    for(int i=1;i<=planeCnt;i++){
        scanf("%d", &until[i]);
    }
    int ret=solve(until,gateCnt);
    cout << ret <<"\n";
    return 0;
}