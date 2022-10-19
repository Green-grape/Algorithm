#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

int n,m,h;
vector<vector<vector<int>>> board;

//z, y, x 순서
int adj[][3]={
    {1,0,0},
    {-1,0,0},
    {0,1,0},
    {0,-1,0},
    {0,0,1},
    {0,0,-1}
};

int bfs(const vector<pair<int, pair<int,int>>>& ripes, const int need){
    vector<vector<vector<bool>>> isVisit(h, vector<vector<bool>>(n,vector<bool>(m)));
    queue<pair<pair<int, pair<int,int>>,int>> q;
    int count=0,ret=0;
    for(int i=0;i<ripes.size();i++){
        isVisit[ripes[i].first][ripes[i].second.first][ripes[i].second.second]=true;
        q.push(make_pair(ripes[i],0));
        count++;
    }
    while(!q.empty()){
        pair<pair<int,pair<int,int>>,int> cur=q.front();
        q.pop();
        for(int i=0;i<6;i++){
            int nextZ=cur.first.first+adj[i][0];
            int nextY=cur.first.second.first+adj[i][1];
            int nextX=cur.first.second.second+adj[i][2];
            int curDay=cur.second;
            if(nextZ<0 || h<=nextZ || nextY<0 || n<=nextY || nextX<0 || m<=nextX) continue;
            if(board[nextZ][nextY][nextX]==0 && !isVisit[nextZ][nextY][nextX]){
                isVisit[nextZ][nextY][nextX]=true;
                board[nextZ][nextY][nextX]=1;
                ret=max(ret,curDay+1);
                count++;
                q.push(make_pair(make_pair(nextZ, make_pair(nextY, nextX)),curDay+1));
            }
        }
    }
    if(need>count) return -1;
    return ret;
}

int main(){
    cin >> m >> n >> h;
    board.resize(h);
    int need=m*n*h;
    vector<pair<int, pair<int,int>>> ripes;
    for(int k=0;k<h;k++){
        board[k].resize(n);
        for(int i=0;i<n;i++){
            board[k][i].resize(m);
            for(int j=0;j<m;j++){
                scanf("%d", &board[k][i][j]);
                if(board[k][i][j]==-1) need--;
                if(board[k][i][j]==1){
                    ripes.push_back(make_pair(k, make_pair(i,j)));
                }
            }
        }
    }
    int ret=bfs(ripes,need);
    cout << ret <<"\n";
    return 0;
}