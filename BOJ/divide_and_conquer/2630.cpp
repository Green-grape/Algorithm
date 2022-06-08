#include <iostream>

using namespace std;

const int MAX_N=128;
int board[MAX_N][MAX_N];

pair<int,int> operator+(pair<int,int> p1, pair<int,int> p2){
    return make_pair(p1.first+p2.first, p1.second+p2.second);
}

pair<int,int> getColorCount(int x1,int y1, int x2, int y2){ //(x1,y1)~(x2,y2)까지의 흰색, 검정색 종이의 개수는?
    bool isAllZero=true,isAllOne=true;
    for(int i=x1;i<=x2;i++){
        for(int j=y1;j<=y2;j++){
            if(board[i][j]==0) isAllOne=false;
            else isAllZero=false;
            if(!isAllZero && !isAllOne) break;
        }
        if(!isAllZero && !isAllOne) break;
    }
    if(isAllZero) return make_pair(1,0);
    if(isAllOne) return make_pair(0,1);
    int midX=(x1+x2)/2,midY=(y1+y2)/2;
    return getColorCount(x1,y1,midX,midY)+getColorCount(x1,midY+1,midX,y2)+getColorCount(midX+1,y1,x2,midY)+getColorCount(midX+1,midY+1,x2,y2);
}

int main(){
    int boardLength;
    cin >> boardLength;
    for(int i=0;i<boardLength;i++){
        for(int j=0;j<boardLength;j++){
            cin >> board[i][j];
        }
    }
    pair<int,int> ret=getColorCount(0,0,boardLength-1,boardLength-1);
    cout << ret.first <<"\n"<<ret.second<<"\n";
    return 0;
}