#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int coords[][2]={
    {-1,0},{1,0},{0,1},{0,-1}
};

void dfs(int curY, int curX, int& ret, vector<string>& board, vector<vector<bool>>& isVisit){
    if(isVisit[curY][curX]) return;
    isVisit[curY][curX]=true;
    ret++;
    for(int i=0;i<4;i++){
        int nextY=curY+coords[i][0], nextX=curX+coords[i][1];
        if(nextY<0 || board.size()<=nextY || nextX<0 || board[0].size()<=nextX) continue;
        if(board[nextY][nextX]=='1') dfs(nextY, nextX,ret, board, isVisit);
    }
}

vector<int> solve(vector<string>& board){
    vector<vector<bool>> isVisit(board.size(), vector<bool>(board[0].size()));
    vector<int> ret;
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++){
            if(!isVisit[i][j] && board[i][j]=='1'){
                int houseCnt=0;
                dfs(i,j,houseCnt, board,isVisit);
                ret.push_back(houseCnt);
            }
        }
    }
    sort(ret.begin(),ret.end());
    return ret;
}

int main(){
    int n;
    cin >> n;
    vector<string> board(n);
    for(int i=0;i<n;i++){
        string row;
        cin >> row;
        board[i]=row;
    }
    vector<int> ret=solve(board);
    cout << ret.size() <<"\n";
    for(int i=0;i<ret.size();i++){
        cout << ret[i] <<"\n";
    }
    return 0;
}