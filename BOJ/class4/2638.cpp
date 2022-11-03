#include <iostream>
#include <vector>
#include <cstdio>


using namespace std;

//발상의 전환 -> 안에 있는걸 찾기=전체-밖에 있는 걸 찾기

int n, m;
vector<vector<int>> board;
vector<vector<bool>> isVisit;
const int coordX[]={-1,1,0,0};
const int coordY[]={0,0,-1,1};

void dfs(int y, int x){
    if(isVisit[y][x]) return;
    isVisit[y][x]=true;
    for(int i=0;i<4;i++){
        int nextY=y+coordY[i];
        int nextX=x+coordX[i];
        if(nextY<0 || n<=nextY || nextX<0  || m<=nextX) continue;
        if(board[nextY][nextX]==1) continue;
        dfs(nextY,nextX);
    }
}

void precal(){
    isVisit=vector<vector<bool>>(n, vector<bool>(m));
    dfs(0,0);
}

bool isOutside(int y, int x){ //y,x가 공기와 2칸 이상 접촉하여 녹는가? (board[y][x]==1가정)
    int outSideCount=0;
    for(int i=0;i<4;i++){
        int nextY=y+coordY[i];
        int nextX=x+coordX[i];
        if(nextY<0 || n<=nextY || nextX<0 || m<=nextX) continue;
        if(isVisit[nextY][nextX]) outSideCount++;
    }
    return outSideCount>=2;
}

int getEmptyTime(int count){
    int ret=0;
    while(count>0){
        precal();
        vector<vector<int>> target(n, vector<int>(m));
        for(int y=0;y<n;y++){
            for(int x=0;x<m;x++){
                if(board[y][x]==1 && isOutside(y,x)){
                    target[y][x]=1;
                }
            }
        }
        for(int y=0;y<n;y++){
            for(int x=0;x<m;x++){
                if(target[y][x]==1){
                    board[y][x]=0;
                    count--;
                }
            }
        }
        // cout <<"\n";
        // for(int y=0;y<n;y++){
        //     for(int x=0;x<m;x++){
        //         cout << board[y][x] <<" ";
        //     }
        //     cout <<"\n";
        // }
        ret++;
        //cout << count <<"\n";
    }
    return ret;
}

int main(){
    cin >> n >> m;
    board=vector<vector<int>>(n, vector<int>(m));
    int count=0;
    for(int y=0;y<n;y++){
        for(int x=0;x<m;x++){
            scanf("%d", &board[y][x]);
            if(board[y][x]==1) count++;
        }
    }
    cout << getEmptyTime(count) <<"\n";
    return 0;
}