/*
지구와 우주사이는 N X M 행렬로 나타낼 수 있으며 각 원소의 값은 우주선이 그 공간을 지날 때 소모되는 연료의 양이다.
우주선의 특징은 다음과 같다.
1. 지구 -> 달로 가는 경우 우주선이 움직일 수 있는 방향은 좌하, 하, 우하(1칸)이다.
2. 우주선은 전에 움직인 방향으로 움직일 수 없다. 즉, 같은 방향으로 두번 연속으로 움직일 수 없다.
이때 지구에서 달까지 필요한 연료의 최소값은?
*/

#include <iostream>
#include <vector>

using namespace std;

int direct[][2]={
    {-1,+1},
    {0,+1},
    {+1,+1}
};

const int MAXN=1000;
const int INF=987654321;

vector<vector<int>> board;
vector<vector<vector<int>>> cache(MAXN, vector<vector<int>>(MAXN, vector<int>(4,-1)));

bool isCanMove(int x, int y){
    if(0<=y && y<board.size() && 0<=x && x<board[y].size()) return true;
    return false;
}

int getMinFuel(int x, int y, int before){ //현재 위치가 (x,y)이고 이전에 direct[before]로 움직였을때 현재 위치로 부터 끝까지의 필요한 최소 연료량
    if(y==board.size()-1) return board[y][x];
    int& ret=cache[y][x][before];
    if(ret!=-1) return ret;
    ret=INF;
    for(int moveIdx=0;moveIdx<3;moveIdx++){
        if(before==moveIdx) continue;
        if(isCanMove(x+direct[moveIdx][0],y+direct[moveIdx][1])){
            ret=min(ret, board[y][x]+getMinFuel(x+direct[moveIdx][0],y+direct[moveIdx][1],moveIdx));
        }
    }
    return ret;
}

int solve(){
    int ret=INF;
    for(int i=0;i<board[0].size();i++){
        ret=min(ret, getMinFuel(i,0,3));
    }
    return ret;
}

int main(){
    int height,width;
    cin >> height >> width;
    board.resize(height);
    for(int i=0;i<height;i++){
        board[i].resize(width);
        for(int j=0;j<width;j++){
            cin >> board[i][j];
        }
    }
    cout << solve() <<"\n";
    return 0;
}