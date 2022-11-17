#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> nexts;
vector<bool> isHaveTeam;
vector<bool> isVisit;

//사이클의 시작점이 하나라고 생각하지 말자(사이클은 원형이다)

void dfs(int cur, vector<int>& path, vector<bool>& visit){
    if(path.size()!=0 && visit[cur]){ //사이클 완성
        int i=0;
        // for(int j=0;j<path.size();j++){
        //     cout << path[j] <<" ";
        // }
        // cout << cur <<"\n";
        for(;i<path.size();i++){
            if(path[i]==cur) break;
        }
        for(;i<path.size();i++){
            isHaveTeam[path[i]]=true;
        }
        return;
    }
    if(isVisit[cur]) return;
    isVisit[cur]=true;
    visit[cur]=true;
    path.push_back(cur);
    dfs(nexts[cur],path,visit);
}

int solve(){
    int n=isVisit.size();
    for(int i=1;i<n;i++){
        if(!isVisit[i]){
            vector<int> path;
            path.reserve(n);
            vector<bool> visit(n);
            dfs(i,path, visit);
        }
    }
    int ret=0;
    for(int i=1;i<n;i++){
        if(!isHaveTeam[i]) ret++;
    }
    return ret;
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        int n;
        cin >> n;
        //init
        nexts=vector<int>(n+1);
        isHaveTeam=vector<bool>(n+1);
        isVisit=vector<bool>(n+1);
        for(int i=1;i<=n;i++){
            int next;
            scanf("%d", &next);
            nexts[i]=next;
        }
        cout << solve() <<"\n";
    }
}