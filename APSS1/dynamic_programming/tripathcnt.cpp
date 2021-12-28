#include <iostream>
#include <vector>
#include <string>

#define MAX_BOARD_SIZE 100

using namespace std;

int triangleBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int maxLengthFrom[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int maxLengthCountFrom[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

int getMaxPathLengthFrom(int,int);
int getMaxPathLengthCountFrom(int,int);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int boardSize;
        cin >> boardSize;
        for(int j=0;j<boardSize;j++){
            for(int k=0;k<boardSize;k++){
                int temp;
                cin >> temp;
                triangleBoard[j][k]=temp;
            }
        }
        memset(maxLengthFrom, -1, sizeof(maxLengthFrom));
    }   
}

int getMaxPathLengthFrom(int y, int x){
    int& ret=maxLengthFrom[y][x];
    if(y==MAX_BOARD_SIZE-1) return ret=triangleBoard[y][x];
    if(ret!=-1) return ret;
    return ret=max(maxLengthFrom[y+1][x],maxLengthFrom[y+1][x+1])+triangleBoard[y][x];
}

int getMaxPathLengthCountFrom(int y, int x){
    int& ret=maxLengthCountFrom[y][x];
    if(y==MAX_BOARD_SIZE-1) return ret=1;
    if(ret!=-1) return ret;
    ret=0;
    if(maxLengthFrom[y+1][x]>=maxLengthFrom[y+1][x+1]) ret+=maxLengthCountFrom[y+1][x];
    if(maxLengthFrom[y+1][x]<=maxLengthFrom[y+1][x+1]) ret+=maxLengthCountFrom[y+1][x+1];
    return ret;

}
