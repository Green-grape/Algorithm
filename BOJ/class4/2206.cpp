#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <string>

using namespace std;

const int INF=987654321;

int CoordX[]={-1,1,0,0};
int CoordY[]={0,0,-1,1};
int bfs(vector<string>& board){
    int n=board.size(), m=board[0].size();
    vector<vector<vector<int>>> visit(n, vector<vector<int>>(m, vector<int>(2,INF)));
    queue<pair<int,pair<int,int>>> q;
    q.push(make_pair(0,make_pair(0,0)));
    visit[0][0][0]=1;
    while(!q.empty()){
        pair<int, pair<int,int>> cur=q.front();
        int curY=cur.second.first;
        int curX=cur.second.second;
        int isBroken=cur.first;
        q.pop();
        for(int i=0;i<4;i++){
            int nextY=cur.second.first+CoordY[i];
            int nextX=cur.second.second+CoordX[i];
            if(nextY<0 || n<=nextY || nextX<0 || m<=nextX) continue;
            if(board[nextY][nextX]=='0' && (visit[nextY][nextX][isBroken]==INF || (visit[nextY][nextX][isBroken]>visit[curY][curX][isBroken]+1))){
                //부수지 않고 이동이 가능한 경우
                visit[nextY][nextX][isBroken]=visit[curY][curX][isBroken]+1;
                q.push(make_pair(isBroken,make_pair(nextY, nextX)));
            }else if(board[nextY][nextX]=='1' && !isBroken){
                //부숴야하는 경우
                if(visit[nextY][nextX][1]==INF || (visit[nextY][nextX][1]>=visit[curY][curX][0]+1)){
                    visit[nextY][nextX][1]=visit[curY][curX][0]+1;
                    q.push(make_pair(1,make_pair(nextY,nextX)));
                }
            }
        }
    }
    return min(visit[n-1][m-1][0], visit[n-1][m-1][1]);
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<string> board(n);
    for(int i=0;i<n;i++){
        cin >> board[i];
    }
    int ret=bfs(board);
    if(ret==INF) ret=-1;
    cout << ret <<"\n";
    return 0;
}