#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<bool> isVisit;
vector<vector<int>> adj;
int UNWATCHED=0;
int WATCHED=1;
int SELECTED=2;

//현재 노드의 상태를 반환한다. ret 설치된 카메라 수
int dfs(int cur, int& ret){
    isVisit[cur]=true;
    int chilren_status[3]={0,};
    for(int i=0;i<adj[cur].size();i++){
        int next=adj[cur][i];
        if(!isVisit[next]){
            chilren_status[dfs(next,ret)]++;
        }
    }
    if(chilren_status[UNWATCHED]){ //감시가 안되는 chilren이 하나라도 존재
        ret++;
        return SELECTED;
    }else if(chilren_status[SELECTED]){ //이미 선택된 것이 있음
        return WATCHED;
    }
    return UNWATCHED;
}

int solve(){
    isVisit=vector<bool>(adj.size());
    int ret=0;
    for(int i=0;i<adj.size();i++){
        if(!isVisit[i] && dfs(i,ret)==UNWATCHED){
            ret++;
        }
    }
    return ret;
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        int nodeCnt, edgeCnt;
        cin >> nodeCnt >> edgeCnt;
        adj=vector<vector<int>>(nodeCnt);
        for(int i=0;i<edgeCnt;i++){
            int v1, v2;
            scanf("%d %d", &v1, &v2);
            adj[v1].push_back(v2);
            adj[v2].push_back(v1);
        }
        cout << solve() <<"\n";
    }
    return 0;
}