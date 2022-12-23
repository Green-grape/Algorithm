#include <iostream>
#include <vector>

using namespace std;

vector<vector<bool>> isSetable;
int n;
// int coord[][2]={
//     {-1,-1},{-1,1},{1,-1},{1,1}
// };
//board값 2: 비숍이 있음, 1: 비숍의 공격 범위 내, 0: 놓을 수 있는 공간
//brute_force timeout //
// bool insert(int y, int x, vector<int>& board){
//     if(board[y*n+x]==0){
//         board[y*n+x]=2;
//         for(int i=1;i<n;i++){
//             for(int j=0;j<4;j++){
//                 int nextY=y+coord[j][0]*i, nextX=x+coord[j][1]*i;
//                 if(nextY<0 || n<=nextY || nextX<0 || n<=nextX) continue;
//                 if(board[nextY*n+nextX]==0) board[nextY*n+nextX]=1;
//             }
//         }
//         return true;
//     }
//     return false;
// }

// int getMaxSet(int idx, vector<int>& board){
//     vector<int> prevBoard=board;
//     int ret=0;
//     for(int i=idx;i<board.size();i++){
//         int curY=i/n,curX=i%n;
//         if(isSetable[curY][curX] && insert(curY, curX, board)){
//             ret=max(ret, 1+getMaxSet(i+1,board));
//             board=prevBoard;
//         }
//     }
//     return ret;
// }

//비숍의 이동경로가 대각선이므로 체스판을 대각선의 합으로 생각하자
int getMaxSet(int idx, vector<int>& diag){
    if(idx>=diag.size()) return 0;
    int ret=-1;
    int y=idx<n ? 0:idx-(n-1);
    int x=idx<n ? idx: n-1;
    while(y<n && 0<=x){
        if(isSetable[y][x] && diag[y-x+n]==0){
            diag[y-x+n]=1;
            ret=max(ret,1+getMaxSet(idx+1,diag));
            diag[y-x+n]=0;
        }
        y++;
        x--;
    }
    if(ret<0) ret=getMaxSet(idx+1,diag);
    return ret;
}

int solve(){
    vector<int> diag(2*n-1);
    return getMaxSet(0,diag);
}

int main(){
    cin >> n;
    isSetable=vector<vector<bool>>(n, vector<bool>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int input;
            cin >> input;
            isSetable[i][j]=input==1;
        }
    }
    cout << solve() <<"\n";
    return 0;
}