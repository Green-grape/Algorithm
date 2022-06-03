#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int INF=987654321;
const int MAX_STAIR=300;
int stairCount;
int cache[MAX_STAIR+1][2];
vector<int> scores;

int maxScore(int curStair, int oneUpCount){ //현재 curStair 계단에 있고 연속적으로 올라온 칸수가 oneUpCount일때 최대 점수는?
    if(curStair>stairCount || oneUpCount>=3) return -INF; //연속적으로 3칸이상 움직일 수 없다.
    if(curStair==stairCount) return scores[curStair];
    int& ret=cache[curStair][oneUpCount];
    if(ret!=-1) return ret;
    ret=0;
    ret=max(ret,scores[curStair]+maxScore(curStair+1,oneUpCount+1));
    ret=max(ret,scores[curStair]+maxScore(curStair+2,1));
    return ret;
}

int main(){
    cin >> stairCount;
    scores.push_back(0); //시작칸은 0으로 취급
    for(int i=0;i<stairCount;i++){
        int score;
        cin >> score;
        scores.push_back(score);
    }
    memset(cache,-1,sizeof(cache));
    cout << maxScore(0,0) <<"\n";
}