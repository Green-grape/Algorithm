#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


bool cmp(pair<int,int> paper1, pair<int,int> paper2){
    if(paper1.first==paper2.first) return paper1.second>paper2.second;
    return paper1.first>paper2.first;
}

//paperL이 paperS를 포함하는가?
bool contains(pair<int,int> paperL, pair<int,int> paperS){
    return (paperS.first<=paperL.first && paperS.second<=paperL.second) || (paperS.first<=paperL.second && paperS.second<=paperL.first);
}

void dfs(int cur, int curDepth, int& ret, vector<vector<int>>& adj, int prev){
    ret=max(ret,curDepth);
    for(int i=0;i<adj[cur].size();i++){
        if(prev!=adj[cur][i]) dfs(adj[cur][i], curDepth+1, ret, adj, cur);
    }
}

int solve(vector<pair<int,int>> papers){
    int ret=1;
    sort(papers.begin(), papers.end(), cmp);
    vector<int> cache(papers.size(),1);
    for(int i=1;i<papers.size();i++){
        int cand=1;
        for(int j=0;j<i;j++){
            if(papers[j].second>=papers[i].second){
                cand=max(cand,cache[j]+1);
            }
        }
        cache[i]=cand;
        ret=max(ret,cand);
    }
    return ret;
}

int main(){
    int paperCnt;
    cin >> paperCnt;
    vector<pair<int,int>> papers(paperCnt);
    for(int i=0;i<paperCnt;i++){
        int x,y;
        cin >> x >> y;
        papers[i]={max(x,y),min(x,y)};
    }
    cout << solve(papers) <<"\n";
    return 0;
}