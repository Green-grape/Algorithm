#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

const int INF=987654321;
vector<vector<int>> board;

vector<vector<int>> addToSquare(vector<vector<int>>& leftTop, vector<vector<int>>& rightTop, vector<vector<int>>& leftBottom, vector<vector<int>>& rightBottom){
    vector<vector<int>> retDown=leftBottom;
    vector<vector<int>> retUp=leftTop;
    int n=retDown.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            retUp[i].push_back(rightTop[i][j]);
            retDown[i].push_back(rightBottom[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        retUp.push_back(retDown[i]);
    }
    return retUp;
}

vector<vector<int>> poling222(int x1,int y1,int x2,int y2){ //(x1,y1)~(x2,y2) 222풀링한 결과를 반환 (2X2 행렬로 나누어 그중에서 2번째로 큰것을 선택)
    if(x2==x1+1 && y2==y1+1){ //기저사례
        int mostBig=-INF,secondBig=-INF;
        for(int i=x1;i<=x2;i++){
            for(int j=y1;j<=y2;j++){
                if(mostBig<board[i][j]){
                    secondBig=mostBig;
                    mostBig=board[i][j];
                }else if(board[i][j]>secondBig){
                    secondBig=board[i][j];
                }
            }
        }
        return vector<vector<int>>(1,vector<int>(1,secondBig));
    }
    int midX=(x1+x2)/2, midY=(y1+y2)/2;
    vector<vector<int>> leftTop=poling222(x1,y1,midX,midY);
    vector<vector<int>> rightTop=poling222(x1,midY+1,midX,y2);
    vector<vector<int>> leftBottom=poling222(midX+1,y1,x2,midY);
    vector<vector<int>> rightBottom=poling222(midX+1,midY+1,x2,y2);
    return addToSquare(leftTop,rightTop,leftBottom,rightBottom);
}

int solve(){
    while(board.size()>1){
        board=poling222(0,0,board.size()-1,board.size()-1);
        // for(int i=0;i<board.size();i++){
        //     for(int j=0;j<board.size();j++){
        //         cout << board[i][j]<<" ";
        //     }
        //     cout << "\n";
        // }
    }
    return board[0][0];
}


int main(){
    int n;
    cin >> n;
    board.resize(n);
    for(int i=0;i<n;i++){
        board[i].resize(n);
        for(int j=0;j<n;j++){
            scanf("%d", &board[i][j]);
        }
    }
    cout << solve() <<"\n";
    return 0;
}