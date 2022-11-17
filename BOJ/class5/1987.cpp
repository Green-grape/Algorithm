#include <iostream>
#include <vector>

using namespace std;

vector<string> board;

int coordY[]={-1,1,0,0};
int coordX[]={0,0,-1,1};

bool isVisit(int y, int x, int moved,vector<vector<bool>>& visit){
    return ((1<<(board[y][x]-'A')) & moved)!=0 || visit[y][x];
}

int getMaxMove(int y, int x, int moved, vector<vector<bool>>& visit){
    if(isVisit(y,x,moved,visit)) return 0;
    moved=moved | (1<<(board[y][x]-'A'));
    visit[y][x]=true;
    int ret=0;
    for(int i=0;i<4;i++){
        int nextY=y+coordY[i];
        int nextX=x+coordX[i];
        if(nextX<0 || board[0].size()<=nextX || nextY<0 || board.size()<=nextY) continue;
        ret=max(ret,1+getMaxMove(nextY,nextX,moved,visit));
        if(ret>=26) return ret;
        visit[nextY][nextX]=false;
    }
    return ret;
}

int main(){
    int n, m;
    cin >> n >> m;
    board.resize(n);
    vector<vector<bool>> visit(n,vector<bool>(m));
    for(int i=0;i<n;i++){
        cin >> board[i];
    }
    cout << getMaxMove(0,0,0,visit) <<"\n";
    return 0;
}