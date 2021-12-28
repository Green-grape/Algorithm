#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int boardSize=5;
const int moveCount=8;
vector<string> gameBoard;
//반시계로 움직임
int moveX[]={-1,-1,0,+1,+1,+1,0,-1};
int moveY[]={0,-1,-1,-1,0,+1,+1,+1};

bool hasWord(int, int , const string);
bool isInRange(int,int);

int main(){
    int testCount, wordsCount;
    vector<string> words;
    vector<string> results;
    string temp;
    cin >> testCount;
    for(int i=0;i<testCount;i++){
        for(int j=0;j<boardSize;j++){
            cin >> temp;
            gameBoard.push_back(temp);
        }
        cin >> wordsCount;
        for(int j=0;j<wordsCount;j++){
            cin >> temp;
            words.push_back(temp);
            int res=0;
            for(int x=0;x<boardSize;x++){
                for(int y=0;y<boardSize;y++){
                    if(hasWord(x,y,words[j])){
                        res=1;
                        break;
                    } 
                }
            }
            if(res==1) results.push_back("YES");
            else results.push_back("NO");
        }

        for(int j=0;j<wordsCount;j++){
            cout << words[j]+' '+results[j]+"\n";
        }
        //initialize
        gameBoard.resize(0);
        words.resize(0);
        results.resize(0);
    }
    return 0;
}

bool isInRange(int x, int y){
    if((x<0) || (x>=boardSize) || (y<0) || (y>=boardSize)) return false;
    return true;
}

//gameBoard의 (x,y)좌서에서부터 시작하는 word가 존재하는지 확인하는 함수
bool hasWord(int x, int y, const string word){
    //기저값 확인
    if(!isInRange(x,y)) return 0;
    if(gameBoard[x][y]!=word[0]) return 0;
    if(word.size()==1) return 1;

    bool res=false;
    for(int i=0;i<moveCount;i++){
        res=res || hasWord(x+moveX[i],y+moveY[i],word.substr(1));
    }
    return res;
}