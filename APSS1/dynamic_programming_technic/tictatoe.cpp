#include <vector>
#include <string>
#include <cmath>

using namespace std;

const int BOARD_SIZE=3;
const int CACHE_SIZE=19683; //pow(3,9)
int cache[CACHE_SIZE];

bool finished(const vector<string>& board, char turn){
    const vector<vector<pair<int,int>>> endCondition={
        {make_pair(0,0), make_pair(0,1), make_pair(0,2)},
        {make_pair(1,0), make_pair(1,1), make_pair(1,2)},
        {make_pair(2,0), make_pair(2,1), make_pair(2,2)},
        {make_pair(0,0), make_pair(1,0), make_pair(2,0)},
        {make_pair(0,1), make_pair(1,1), make_pair(2,1)},
        {make_pair(0,2), make_pair(1,2), make_pair(2,2)},
        {make_pair(0,0), make_pair(1,1), make_pair(2,2)},
        {make_pair(2,0), make_pair(1,1), make_pair(0,2)}
    };
    for(int i=0;i<endCondition.size();i++){
        bool isFinished=true;
        for(int j=0;j<endCondition[i].size();j++){
            isFinished=isFinished && (board[endCondition[i][j].first][endCondition[i][j].second]==turn);
        }
        if(isFinished) return true;
    }
    return false;
}

//board를 9자리 3진수로 본다
int bijection(const vector<string>& board){
    int ret=0;
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].length();j++){
            ret*=3;
            if(board[i][j]=='O') ret++;
            else if(board[i][j]=='X') ret+=2;
        }
    }
    return ret;
}

//틱택토 게임판이 현재 board일때 이번 차례 사람이 이길 수 있는가?
//3목 게임
//비기는 경우: 둘 다 3목을 만들지 못하고 게임판이 꽉 찬 경우
//1: 이번 차례의 참가자 이길 수 있는 경우
//0: 비기는 것이 가능한 경우(이길 수는 없음)
//-1: 상대가 반드시 승리
//참가자는 모든 수를 생각해보며 -1인수가 있으면 그 것을 선택하고 없으면 0이라도 선택 최악 1 선택
int canWin(vector<string>& board,char turn){
    if(finished(board, 'O'+'X'-turn)) return -1;
    int& ret=cache[bijection(board)];
    if(ret!=-2) return ret;
    int minValue=2;
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].length();j++){
            if(board[i][j]=='.'){
                board[i][j]=turn;
                minValue=min(minValue, canWin(board,'O'+'X'-turn));
                board[i][j]='.';
            }
        }
    }
    if(minValue==2 || minValue==0) return 0;
    return -minValue; 
}