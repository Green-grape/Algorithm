#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<vector<int>> board;
vector<pair<int,int>> ripePositions;
int width,height;
int target=0;
const int INF=987654321;
const int adj[][2]={
    {-1,0},{1,0},{0,-1},{0,1}
};

bool isInRange(int y, int x){
    if(0<=x && x<width && 0<=y && y<height) return true;
    return false;
}

int getDays(int posIdx){
    if(ripePositions.size()==target) return 0;
    int n=ripePositions.size();
    if(posIdx==n) return -2*INF;
    for(int i=posIdx;i<n;i++){
        int y=ripePositions[i].first, x=ripePositions[i].second;
        for(int j=0;j<4;j++){
            int nextY=y+adj[j][0],nextX=x+adj[j][1];
            if(isInRange(nextY,nextX)){
                if(board[nextY][nextX]==0){
                    board[nextY][nextX]=1;
                    ripePositions.push_back(make_pair(nextY,nextX));
                }
            }
        }
    }
    // for(int i=0;i<height;i++){
    //     for(int j=0;j<width;j++){
    //         cout << board[i][j] <<" ";
    //     }
    //     cout << "\n";
    // }
    return 1+getDays(n);
}

int main(){
    cin >> width >> height;
    board=vector<vector<int>>(height, vector<int>(width));
    for(int i=0;i<height;i++){ //y
        for(int j=0;j<width;j++){ //x
            scanf("%d", &board[i][j]);
            if(board[i][j]==1) ripePositions.push_back(make_pair(i,j));
            if(board[i][j]!=-1) target++;
        }
    }
    int ret=getDays(0);
    if(ret<-INF) cout << -1 <<"\n";
    else cout << ret<<"\n";
    return 0;
}