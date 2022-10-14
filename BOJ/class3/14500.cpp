#include <iostream>
#include <vector>

using namespace std;

const vector<vector<vector<int>>> tetrominos={
    {{0,0},{0,1},{0,2},{0,3}}, //(4,0,0,0)

    {{0,0},{0,1},{0,2},{1,0}}, //(3,1,0,0)
    {{0,0},{0,1},{0,2},{1,1}},
    {{0,0},{0,1},{0,2},{1,2}},

    {{0,0},{0,1},{1,0},{1,1}}, //(2,2,0,0)
    {{0,0},{0,1},{1,1},{1,2}},

    {{0,0},{1,0},{2,0},{2,1}}, //(2,1,1,0)
    {{0,0},{1,0},{2,0},{1,1}},
    {{0,0},{1,0},{2,0},{0,1}},
    {{0,0},{0,1},{1,1},{2,1}},

    {{0,0},{1,0},{1,1},{1,2}},//(1,3,0,0)

    {{0,0},{1,0},{1,1},{2,0}},//(1,2,1,0)
    {{0,0},{1,0},{1,1},{2,1}},
    
    {{0,0},{1,0},{2,0},{2,1}},//(1,1,2,0)

    {{0,0},{1,0},{2,0},{3,0}}//(1,1,1,1)
};

const vector<vector<int>> rotate={
    {1,1},{1,-1},{-1,1},{-1,-1}
};

vector<vector<int>> board;
int n,m;

bool canInsert(int y, int x, int blockIdx, int rotateIdx){
    for(int i=0;i<tetrominos[blockIdx].size();i++){
        int curY=rotate[rotateIdx][1]*tetrominos[blockIdx][i][1]+y;
        int curX=rotate[rotateIdx][0]*tetrominos[blockIdx][i][0]+x;
        if(0<=curX && curX<m && 0<=curY && curY<n) continue;
        return false;
    }
    return true;
}

int getValue(int y, int x, int blockIdx,int rotateIdx){
    int ret=0;
      for(int i=0;i<tetrominos[blockIdx].size();i++){
        int curY=rotate[rotateIdx][1]*tetrominos[blockIdx][i][1]+y;
        int curX=rotate[rotateIdx][0]*tetrominos[blockIdx][i][0]+x;
        ret+=board[curY][curX];
    }
    return ret;
}

int getMaxValue(){
    int ret=0;
    for(int y=0;y<n;y++){
        for(int x=0;x<m;x++){
            for(int i=0;i<tetrominos.size();i++){
                for(int j=0;j<rotate.size();j++){
                     if(canInsert(y,x,i,j)){
                        ret=max(ret, getValue(y,x,i,j));
                    }
                }
            }
        }
    }
    return ret;
}

int main(){
    cin >> n >> m;
    board=vector<vector<int>>(n, vector<int>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d", &board[i][j]);
        }
    }
    cout << getMaxValue() <<"\n";
    return 0;
}