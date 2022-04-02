#include <vector>
#include <iostream>
#include <string>
#include <string.h>

const char EMPTY=0;
const char LOSE=1;
const char WIN=2;
using namespace std;

vector<int> moves;
int cell(int x, int y) {return 1<<(x*5+y);}

void preCal(){
    for(int x=0;x<4;x++){
        for(int y=0;y<4;y++){
            vector<int> cells;
            for(int dx=0;dx<2;dx++){
                for(int dy=0;dy<2;dy++){
                    cells.push_back(cell(x+dx,y+dy));
                }
            }
            int square=cells[0]+cells[1]+cells[2]+cells[3]; // 큰 네모에서 한개를 빼면 L자모양
            for(int i=0;i<4;i++){
                moves.push_back(square-cells[i]);
            }
        }
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<4;j++){
            moves.push_back(cell(i,j)+cell(i,j+1));
            moves.push_back(cell(j,i)+cell(j+1,i));
        }
    }
}

char cache[1<<25];

char play(int state){
    char& ret=cache[state];
    if(ret!=EMPTY) return ret;
    ret=LOSE;
    for(int i=0;i<moves.size();i++){
        if((moves[i] & state)==0){
            if(((int)play(state | moves[i]))==LOSE){
                ret=WIN;
                break;
            }
        }
    }
    return ret;
}

int main(){
    int testCase;
    cin >> testCase;
    memset(cache,EMPTY,sizeof(cache));
    preCal();
    for(int i=0;i<testCase;i++){
        string board="";
        for(int j=0;j<5;j++){
            string s;
            cin >> s;
            board+=s;
        }
        int state=0;
        for(int j=board.length()-1;j>=0;j--){
            if(board[j]=='#') state=state | (1<<j);
        }
        int r=(int)play(state);
        if(r==WIN) cout << "WINNING" <<"\n";
        else cout <<"LOSING"<<"\n";
    }
    return 0;
}