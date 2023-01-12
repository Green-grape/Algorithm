#include <iostream>
#include <vector>

using namespace std;

pair<int,vector<int>> solve(vector<vector<int>>& adj){
    for(int k=1;k<adj.size();k++){
        for(int i=1;i<adj.size();i++){
            for(int j=1;j<adj.size();j++){
                adj[i][j]=min(adj[i][j], adj[i][k]+adj[k][j]);
            }
        }
    }
    vector<int> ret;
    int retScore=100;
    for(int i=1;i<adj.size();i++){
        int curMax=1;
        for(int j=1;j<adj.size();j++){
            if(i!=j){
                curMax=max(adj[i][j],curMax);
            }
        }
        if(curMax<retScore){
            retScore=curMax;
            ret=vector<int>(1,i);
        }else if(curMax==retScore){
            ret.push_back(i);
        }
    }
    return {retScore,ret};
}

int main(){
    int nodeCnt;
    cin >> nodeCnt;
    vector<vector<int>> adj(nodeCnt+1, vector<int>(nodeCnt+1,100));
    for(int i=1;i<=nodeCnt;i++) adj[i][i]=0;
    while(true){
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        if(v1==-1 && v2==-1) break;
        adj[v1][v2]=1;
        adj[v2][v1]=1;
    }
    pair<int, vector<int>> ret=solve(adj);
    cout << ret.first<<" "<<ret.second.size()<<"\n";
    for(int i=0;i<ret.second.size();i++){
        cout << ret.second[i] <<" ";
    }
    return 0;
}