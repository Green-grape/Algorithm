#include <iostream>
#include <vector>
#include <string>
#include <string.h>

#define MAX_BOARD_SIZE 100

using namespace std;

int gameBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int canGoToEndFrom[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

int canGoToNext2(int,int ,const int&);

int main(){
    int testCase; //   1<=testCase<=50
    cin >>testCase;
    vector<string> results;
    for(int i=0;i<testCase;i++){
        int boardSize;
        cin >> boardSize;
        for(int j=0;j<boardSize;j++){
            for(int k=0;k<boardSize;k++){
                int temp;
                cin >> temp;
                gameBoard[j][k]=temp;
            }
        }
        memset(canGoToEndFrom,-1,sizeof(canGoToEndFrom));
        if(canGoToNext2(0,0,boardSize)==1) results.push_back("YES");
        else results.push_back("NO");
    }
    for(int i=0;i<testCase;i++){
        cout << results[i] << "\n";
    }
    return 0;
}

//완전탐색 풀이 O(2^n) -> 2^100이면 시간초과
bool canGoToNext(int x, int y,const int& boardSize){
    //기저사례
    if((x>=boardSize) || (y>=boardSize)) return false;
    if((x==boardSize-1) && (y==boardSize-1)) return true;
    
    int moveCount=gameBoard[x][y];
    return canGoToNext(x+moveCount,y, boardSize) ||  canGoToNext(x,y+moveCount,boardSize);
}

//입력은 최대 1만개 고정 => dynamic programming O(n^2) 풀이
int canGoToNext2(int x, int y, const int& boardSize){
    //기저사례
    if((x>=boardSize) || (y>=boardSize)) return 0;
    if((x==boardSize-1) && (y==boardSize-1)) return 1;
    if(canGoToEndFrom[x][y]!=-1) return canGoToEndFrom[x][y];

    int moveCount=gameBoard[x][y];
    return canGoToEndFrom[x][y]=(canGoToNext2(x+moveCount,y,boardSize) || canGoToNext2(x,y+moveCount,boardSize));
}