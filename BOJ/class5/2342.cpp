#include <iostream>
#include <vector>

using namespace std;

const int INF=987654321;

vector<int> moves;
vector<vector<vector<int>>> cache;

int getForce(int from, int to){
    if(from==to) return 1;
    if(from==0) return 2;
    if((from+1)%4==to%4 || (from-1)%4==to%4) return 3;
    return 4;
}

int getMinForce(int idx, int foot1, int foot2){ //moves[idx]를 눌러야하고 현재 발의 위치가 foot1, foot2일때 moves를 끝내기 위한 최소 힘은?
    if(idx==moves.size()) return 0;
    if(cache[idx][foot1][foot2]!=-1) return cache[idx][foot1][foot2];
    int& ret=cache[idx][foot1][foot2];
    ret=INF;
    if(moves[idx]==foot1 || moves[idx]==foot2){ //같은 발이 한 발판이 놓이면 안됨
        ret=min(ret, 1+getMinForce(idx+1,foot1,foot2));
    }
    //foot1이 움직임
    ret=min(ret, getForce(foot1,moves[idx])+getMinForce(idx+1,moves[idx],foot2));
    //foot2이 움직임
    ret=min(ret, getForce(foot2,moves[idx])+getMinForce(idx+1,foot1,moves[idx]));
    cache[idx][foot2][foot1]=ret;
    return ret;
}

int main(){
    int move;
    while(true){
        scanf("%d", &move);
        if(move==0) break;
        moves.push_back(move);
    }
    cache=vector<vector<vector<int>>>(moves.size(),vector<vector<int>>(5,vector<int>(5,-1)));
    cout << getMinForce(0,0,0) <<"\n";
    return 0;
}