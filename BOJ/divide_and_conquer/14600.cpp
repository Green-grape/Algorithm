/*
2^kX2^k모양 타일(1<=K<=2)을 주어진 한 칸을 제외하고 ㄱ모양 블럭으로 채우는 것이 가능한가?
불가능하면 -1 출력, 가능하면 각각의 ㄱ모양 블럭에 고유 번호를 붙여서 타일을 출력하라
*/

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

vector<vector<int>> board;
int id=0;

bool checkEmpty(int x, int y, int n){
    for(int i=x;i<x+n;i++){
        for(int j=y;j<y+n;j++){
            if(board[i][j]!=0) return false;
        }
    }
    return true;
}

void fillBoard(int x, int y, int n){
    id++;
    if(checkEmpty(x,y,n/2)) board[x+n/2-1][y+n/2-1]=id;
    if(checkEmpty(x+n/2,y,n/2)) board[x+n/2][y+n/2-1]=id;
    if(checkEmpty(x,y+n/2,n/2)) board[x+n/2-1][y+n/2]=id;
    if(checkEmpty(x+n/2, y+n/2, n/2)) board[x+n/2][y+n/2]=id;
    if(n==2) return;
    fillBoard(x,y,n/2);
    fillBoard(x+n/2,y,n/2);
    fillBoard(x,y+n/2,n/2);
    fillBoard(x+n/2,y+n/2,n/2);
}

int main(){
    int k;
    cin >> k;
    board.resize(pow(2,k));
    for(int i=0;i<board.size();i++) board[i].resize(pow(2,k));
    int x,y;
    cin >> x >> y;
    board[y-1][x-1]=-1;
    fillBoard(0,0,pow(2,k));
    for(int j=board.size()-1;j>=0;j--){
        for(int i=0;i<board.size();i++){
            cout << board[j][i] <<" ";
        }
        cout <<"\n";
    }
    return 0;
}