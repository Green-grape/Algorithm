#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

void findOutside(vector<vector<bool>>& isVisit, vector<vector<int>>& board){
    queue<pair<int,int>> q;
    q.push({0,0});
    isVisit[0][0]=true;
    int coords[][2]={
        {0,1},{0,-1},{1,0},{-1,0}
    };
    while(!q.empty()){
        pair<int,int> cur=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int nextY=cur.first+coords[i][0],nextX=cur.second+coords[i][1];
            if(nextY<0 || board.size()<=nextY || nextX<0 || board[0].size()<=nextX || isVisit[nextY][nextX]) continue;
            if(board[nextY][nextX]==0){
                isVisit[nextY][nextX]=true;
                q.push({nextY, nextX});
            }
        }
    }
}

bool isOutSide(vector<vector<bool>>& isVisit, vector<vector<int>>& board, int y, int x){
    int coords[][2]={
        {0,1},{0,-1},{1,0},{-1,0}
    };
    for(int i=0;i<4;i++){
        int nextY=y+coords[i][0],nextX=x+coords[i][1];
        if(nextY<0 || board.size()<=nextY || nextX<0 || board[0].size()<=nextX || !isVisit[nextY][nextX]) continue;
        if(board[nextY][nextX]==0) return true;
    }
    return false;
}

pair<int,int> getLastRemain(vector<vector<int>>& board){
    int emptyTime=0,lastRemoved;
    while(true){
        vector<vector<bool>> isVisit(board.size(),vector<bool>(board[0].size()));
        findOutside(isVisit,board);
        int removed=0;
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                if(board[i][j]==1 && isOutSide(isVisit,board,i,j)){
                    board[i][j]=-1;
                    removed++;
                }
            }
        }
        if(removed==0) break;
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                if(board[i][j]==-1){
                    board[i][j]=0;
                }
            }
        }
        emptyTime++;
        lastRemoved=removed;
    }
    return {emptyTime,lastRemoved};
}

int main(){
    int height,width;
    cin >> height >> width;
    vector<vector<int>> board(height, vector<int>(width));
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            scanf("%d", &board[i][j]);
        }
    }
    pair<int,int> ret=getLastRemain(board);
    cout << ret.first <<"\n"<<ret.second<<"\n";
    return 0;
}