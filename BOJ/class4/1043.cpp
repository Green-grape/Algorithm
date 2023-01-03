#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<int> cache;

//dfs는 cache 사용을 자제하자

int dfs(int cur, set<int>& knowTrue,vector<vector<bool>>& adj, vector<bool>& isVisit){
    if(isVisit[cur]) return 0;
    isVisit[cur]=true;
    if(knowTrue.count(cur)>0) return 1;
    int ret=0;
    for(int i=1;i<adj[cur].size();i++){
        if(adj[cur][i] && cur!=i && !isVisit[i]){
            ret|=dfs(i,knowTrue,adj,isVisit);
        }
        if(ret) break;
    }
    return ret;
}

int main(){
    int peopleCnt, partyCnt;
    cin >> peopleCnt >> partyCnt;
    vector<vector<bool>> adj(peopleCnt+1,vector<bool>(peopleCnt+1));
    set<int> knowTrue;
    int knowTrueCnt;
    cin >> knowTrueCnt;
    for(int i=0;i<knowTrueCnt;i++){
        int person;
        cin >> person;
        knowTrue.insert(person);
    }
    vector<vector<int>> partys(partyCnt);
    for(int i=0;i<partyCnt;i++){
        int partyPeopleCnt;
        cin >> partyPeopleCnt;
        for(int j=0;j<partyPeopleCnt;j++){
            int partyPeopleNum;
            cin >> partyPeopleNum;
            partys[i].push_back(partyPeopleNum);
        }
        for(int j=0;j<partyPeopleCnt;j++){
            for(int k=j+1;k<partyPeopleCnt;k++){
                adj[partys[i][j]][partys[i][k]]=true;
                adj[partys[i][k]][partys[i][j]]=true;
            }
        }
    }
    int ret=0;
    vector<bool> isVisit(partyCnt+1);
    for(int i=0;i<partyCnt;i++){
        if(!dfs(partys[i][0],knowTrue,adj, isVisit)){
            ret++;
        }
        isVisit=vector<bool>(partyCnt+1);
    }
    cout << ret <<"\n";
    return 0;
}