#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> board;

int CoordY[]={-1,0,1,0};
int CoordX[]={0,-1,0,1};
const int INF=987654321;

int curSize=2;
int sizeExp=0;
void eat(int y, int x){
    board[y][x]=0;
    sizeExp++;
    if(curSize==sizeExp){
        curSize++;
        sizeExp=0;
    }
}

int cmp(pair<int,pair<int,int>> p1, pair<int,pair<int,int>> p2){
    if(p1.first!=p2.first) return p1.first<p2.first;
    else if(p1.second.first!=p2.second.first) return p1.second.first<p2.second.first;
    else if(p1.second.second!=p2.second.second) return p1.second.second<p2.second.second;
    return 1;
}

pair<int,pair<int,int>> bfs(int y, int x){
    int n=board.size();
    vector<vector<bool>> isVisit(n, vector<bool>(n));
    isVisit[y][x]=true;
    queue<pair<int,pair<int,int>>> q;
    q.push(make_pair(0,make_pair(y,x)));
    pair<int,pair<int,int>> ret=make_pair(INF,make_pair(0,0));
    while(!q.empty()){
        pair<int,pair<int,int>> cur=q.front();
        int curTime=cur.first;
        q.pop();
        for(int i=0;i<4;i++){
            int nextY=cur.second.first+CoordY[i];
            int nextX=cur.second.second+CoordX[i];
            if(nextY<0 || n<=nextY || nextX<0 || n<=nextX) continue;
            if(!isVisit[nextY][nextX] && curSize>=board[nextY][nextX]){
                isVisit[nextY][nextX]=true;
                pair<int,pair<int,int>> cand=make_pair(curTime+1, make_pair(nextY, nextX));
                if(board[nextY][nextX]!=0 && curSize>board[nextY][nextX]){
                    if(cmp(cand,ret)) ret=cand;
                }
                q.push(cand);
            }
        }
    }
    return ret;
}

int solve(int y, int x){
    int ret=0;
    while(true){
        pair<int,pair<int,int>> subRet=bfs(y,x);
        if(subRet.first==INF) break;
        board[y][x]=0;
        ret+=subRet.first;
        y=subRet.second.first;
        x=subRet.second.second;
        eat(y,x);
    }
    return ret;
}

int main(){
    int n;
    cin >> n;
    board=vector<vector<int>>(n,vector<int>(n));
    int startY,startX;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> board[i][j];
            if(board[i][j]==9){
                startY=i;
                startX=j;
            }
        }
    }
    cout << solve(startY, startX) <<"\n";
    return 0;
}