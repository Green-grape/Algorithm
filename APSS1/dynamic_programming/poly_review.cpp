#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int MAX_SQUARE_COUNT=100;
const int MOD=10000000;
int cache[MAX_SQUARE_COUNT+2][MAX_SQUARE_COUNT+2];

void init();
int solve(int n);

int main(){
    int testCase;
    cin >> testCase;
    init();
    for(int i=0;i<testCase;i++){
        int squareCount;
        cin >> squareCount;
        cout <<solve(squareCount)<<"\n";
    }
    return 0;
}

void init(){
    memset(cache,-1,sizeof(cache));
}

//전체 정사각형이 squareCount이고 맨 위의 정사각형 개수가 topSquareCount인 세로 단조 폴리오미노의 개수
int getVerticalMonotonePolyominoCount(int squareCount,int topSquareCount){
    int& ret=cache[squareCount][topSquareCount];
    if(ret!=-1) return ret;
    if(squareCount==topSquareCount) return ret=1;
    ret=0;
    for(int i=1;i<=squareCount-topSquareCount;i++){
        ret=(ret+(topSquareCount+i-1)*getVerticalMonotonePolyominoCount(squareCount-topSquareCount, i))%MOD;
    }
    return ret;
}

int solve(int n){
    int ret=0;
    for(int i=1;i<=n;i++){
        ret=(ret+getVerticalMonotonePolyominoCount(n,i))%MOD;
    }
    return ret;
}
