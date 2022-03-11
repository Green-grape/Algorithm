#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int MAX_SIDE_LENGTH=100;
int endX,endY;

int board[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH];
int isCanGoToEndCache[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH];

int isCanGoToEnd(const int startX,const int startY);
void init();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int sideLength;
        cin >> sideLength;
        endX=endY=sideLength-1;
        init();
        for(int i=0;i<sideLength;i++){
            for(int j=0;j<sideLength;j++){
                cin >> board[i][j];
            }
        }
        string ret=isCanGoToEnd(0,0)==1 ? "YES":"NO";
        cout << ret <<"\n";
    }
    return 0;
}

void init(){
    memset(board,-1,sizeof(board));
    memset(isCanGoToEndCache,-1,sizeof(isCanGoToEndCache));
}

int isCanGoToEnd(const int startX,const int startY){
    //기저사례
    if(isCanGoToEndCache[startX][startY]!=-1) return isCanGoToEndCache[startX][startY];
    if(startX==endX && startY==endY) return 1;

    int move=board[startX][startY];
    int ret1=0,ret2=0;
    if(startX+move<=endX) ret1=isCanGoToEndCache[startX+move][startY]=isCanGoToEnd(startX+move,startY);
    if(startY+move<=endY) ret2=isCanGoToEndCache[startX][startY+move]=isCanGoToEnd(startX,startY+move);
    return ret1 || ret2;
}