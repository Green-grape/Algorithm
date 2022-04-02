#include <vector>
#include <iostream>
#include <string.h>

const int INF=987654321;
int cache[50][50];
int cache2[50][50][2];
using namespace std;
vector<int> board;

int getDif(int left, int right);
int getDif2(int left, int right, char turn);
void init();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int boardLength;
        cin >> boardLength;
        init();
        for(int j=0;j<boardLength;j++){
            int num;
            cin >> num;
            board.push_back(num);
        }
        cout << getDif2(0,board.size()-1,'A')<<"\n";
    }
    return 0;
}

void init(){
    for(int i=0;i<50;i++){
        for(int j=0;j<50;j++){
            cache[i][j]=-INF;
        }
    }
    for(int i=0;i<50;i++){
        for(int j=0;j<50;j++){
            cache2[i][j][0]=cache2[i][j][1]=-INF;
        }
    }
    board.resize(0);
}

//현재 게임판이 board일때 turn 플레이어가 최적의 수를 놓았을때 플레이어가 얻을 수 있는 최대
int getDif(int left, int right){
    if(left>right) return 0;
    int& ret=cache[left][right];
    if(ret!=-INF) return ret;
    if(right-left+1>=2){
        ret=max(ret, -getDif(left+2,right));
        ret=max(ret, -getDif(left,right-2));
    }
    ret=max(ret, board[left]-getDif(left+1,right));
    ret=max(ret, board[right]-getDif(left,right-1));
    return ret;
}

//turn이 A이면 scoreA-scoreB를 최대화
//turn이 B이면 scoreA-scoreB를 최소화
//하도록 선택한 점수차 반환(scoreA-scoreB)
//minimax algorithm
int getDif2(int left, int right, char turn){
    if(left>right) return 0;
    int& ret=cache2[left][right][turn-'A'];
    if(ret!=-INF) return ret;
    if(turn=='A'){
        if(right-left+1>=2){
            ret=max(ret, getDif2(left+2,right,'B'));
            ret=max(ret, getDif2(left,right-2,'B'));
        }
        ret=max(ret, board[left]+getDif2(left+1,right,'B'));
        ret=max(ret, board[right]+getDif2(left,right-1,'B'));
        return ret;
    }
    else{
        ret=INF;
        if(right-left+1>=2){
            ret=min(ret, getDif2(left+2,right,'A'));
            ret=min(ret, getDif2(left,right-2,'A'));
        }
        ret=min(ret, getDif2(left+1,right,'A')-board[left]);
        ret=min(ret, getDif2(left,right-1,'A')-board[right]);
        return ret;
    }
}