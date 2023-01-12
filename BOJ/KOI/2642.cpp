#include <iostream>
#include <vector>

using namespace std;

const int N=6;

int board[N][N]={0,};
int coords[][2]={
    {-1,0},{1,0},{0,-1},{0,1}
};
int face[N+1]={0,};
vector<pair<int,int>> pos(N+1,{-1,-1});
vector<vector<bool>> isVisit;

void dfs(int curDepth, int curY, int curX, int dir, int& start){
    if(isVisit[curY][curX]) return;
    isVisit[curY][curX]=true;
    for(int i=0;i<4;i++){
        int nextY=curY+coords[i][0], nextX=curX+coords[i][1];
        if(nextY<0 || N<=nextY || nextX<0 || N<=nextX || board[nextY][nextX]==0 || isVisit[nextY][nextX]) continue;
        if(dir==-1){ //지금이 처음인경우
            dfs(1,nextY, nextX, i, start);
        }else if(dir!=i){ //지금과 다른 방향으로 가는 경우
            dfs(curDepth, nextY, nextX, dir, start);
        }else if(dir==i && curDepth==1){
            if(face[board[nextY][nextX]]==0 && face[board[pos[start].first][pos[start].second]]==0){
                face[board[nextY][nextX]]=start;
                face[board[pos[start].first][pos[start].second]]=board[nextY][nextX];
            }
        }
    }
}

bool isHaveProperNumbers(){
    //숫자가 한개씩만 존재하는지 확인
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            if(board[i][j]!=0){
                if(pos[board[i][j]].first!=-1) return false;
                pos[board[i][j]]={i,j};
            }
        }
    }
    for(int i=1;i<=6;i++){
        if(pos[i].first==-1) return false;
    }
    return true;
}

int solve(){
    if(!isHaveProperNumbers()) return 0;
    for(int i=1;i<=6;i++){
        isVisit=vector<vector<bool>>(N, vector<bool>(N));
        dfs(0,pos[i].first, pos[i].second, -1,i);
    }
    // cout <<"\n";
    // for(int i=1;i<=6;i++){
    //     cout << face[i] <<" ";
    // }
    // cout <<"\n";
    for(int i=1;i<=6;i++){
        if(face[i]==0) return 0;
    }
    return face[1];
}

int main(){
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            cin >> board[i][j];
        }
    }
    int ret=solve();
    cout << ret <<"\n";
    return 0;
}