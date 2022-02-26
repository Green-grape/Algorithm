/*
4X4 모양 퍼즐에 1~15까지의 숫자가 있고 한 칸이 비어있다
비어있는 한칸으로 주변의 타일과 1회 교환하는 것을 움직임 1회라고 할때
최소한의 움직임 수는?
*/

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

const int BOARD_SIZE=4;

typedef vector<vector<int>> state;

int main(){
    vector<vector<int>> input(BOARD_SIZE, vector<int>(BOARD_SIZE));
    int temp;
    for(int i=0;i<input.size();i++){
        for(int j=0;j<input[i].size();j++){
            cin >> temp;
            input[i][j]=temp;
        }
    }
}

//빈 공간이 -1이라 가정
vector<vector<vector<int>>> getPossibleNextStates(vector<vector<int>> cur){
    pair<int,int> voidSpace(-1,-1);
    for(int i=0;i<cur.size();i++){
        for(int j=0;j<cur[i].size();j++){
            if(cur[i][j]==-1){
                voidSpace=make_pair(i,j);
                break;
            }
        }
        if(voidSpace.first!=-1) break;
    }
    vector<vector<vector<int>>> ret;
    if(voidSpace.first!=0){
        swap(cur[voidSpace.first][voidSpace.second], cur[voidSpace.first-1][voidSpace.second]);
        ret.push_back(cur);
        swap(cur[voidSpace.first][voidSpace.second], cur[voidSpace.first-1][voidSpace.second]);
    }
    if(voidSpace.first!=cur[voidSpace.first].size()-1){
        swap(cur[voidSpace.first][voidSpace.second], cur[voidSpace.first+1][voidSpace.second]);
        ret.push_back(cur);
        swap(cur[voidSpace.first][voidSpace.second], cur[voidSpace.first+1][voidSpace.second]);
    }
    if(voidSpace.second!=0){
        swap(cur[voidSpace.first][voidSpace.second], cur[voidSpace.first][voidSpace.second-1]);
        ret.push_back(cur);
        swap(cur[voidSpace.first][voidSpace.second], cur[voidSpace.first][voidSpace.second-1]);
    }
    if(voidSpace.second!=cur[voidSpace.first].size()-1){
        swap(cur[voidSpace.first][voidSpace.second], cur[voidSpace.first][voidSpace.second+1]);
        ret.push_back(cur);
        swap(cur[voidSpace.first][voidSpace.second], cur[voidSpace.first][voidSpace.second+1]);
    }
    return ret;
}

//갈수 없는 경우 -1
//가능한 경우 최소비용 반환
int getMinCost(vector<vector<int>> start, vector<vector<int>> end){
    if(start==end) return 0;
    map<vector<vector<int>>, int> states; //states[state]=val, val=cost
    queue<vector<vector<int>>> q;
    q.push(start);
    states[start]=0;
    while(!q.empty()){
        vector<vector<int>> cur=q.front();
        q.pop();
        int cost=states[cur];
        vector<vector<vector<int>>> nextStates=getPossibleNextStates(cur);
        for(int i=0;i<nextStates.size();i++){
            vector<vector<int>> next=nextStates[i];
            if(states.count(next)==0){
                if(next==end) return cost+1;
                states[next]=cost+1;
                q.push(next);
            }
        }
    }
    return -1;
}

int sign(int x){
    return x>=0 ? 1:-1;
}

int increaseCost(int x){
    return x>=0 ? x+1:x-1;
}

//getMinCost의 단방향 검색이 bfs가 진행됨에 따라 지수적으로 수행시간이 올라가서 문제가 발생하므로 
//양방향으로 검색하면 bfs의 수행횟수를 루트배로 줄일 수 있다. 
//역방향 간선이 찾아내기 간단+수가 많지 않은 경우에만 사용가능
int getMinCostBidirectional(vector<vector<int>> start, vector<vector<int>> end){
    if(start==end) return 0;
    map<vector<vector<int>>, int> states;
    queue<vector<vector<int>>> q;
    q.push(start);
    q.push(end);
    //양방향을 음,양으로 구분하기 위해서 최단 거리가 각각 -1,1
    states[start]=1;
    states[end]=-1;
    while(!q.empty()){
        vector<vector<int>> cur=q.front();
        q.pop();
        int cost=states[cur];
        vector<vector<vector<int>>> nextStates=getPossibleNextStates(cur);
        for(int i=0;i<nextStates.size();i++){
            map<vector<vector<int>>, int>::iterator it=states.find(nextStates[i]);
            if(it==states.end()){
                states[nextStates[i]]=increaseCost(cost);
                q.push(nextStates[i]);
            }
            else if(sign(it->second)!=sign(cost)){ //서로 만난 경우
                return abs(it->second)+abs(cost)-1;
            }
        }
    }
    return -1;
}

//추가적인 최적화
//우리가 움직이는 것의 하한은 두 상태사이의 빈칸들의 맨걸튼 거리임을 쉽게 알수 있다.
//따라서 빈칸들 사이의 맨해튼 거리+현재비용>=최선비용임을 체크하면 보다 빠르게 찾을 수 있다.
int estimate(vector<vector<int>> state1, vector<vector<int>> state2){
    pair<int,int> voidSpace1(-1,-1),voidSpace2(-1,-1);
    for(int i=0;i<state1.size();i++){
        for(int j=0;j<state1[i].size();j++){
            if(state1[i][j]==-1) voidSpace1=make_pair(i,j);
            if(state2[i][j]==-1) voidSpace2=make_pair(i,j);
        }
    }
    return abs(voidSpace2.first-voidSpace1.first)+abs(voidSpace2.second-voidSpace1.second);
}

int dfs(vector<vector<int>> curState, const vector<vector<int>>& endState, int& bestCost ,int curCost){
    if(curCost+estimate(curState,endState)>=bestCost) return -1;
    if(curState==endState){
        bestCost=curCost;
        return bestCost;
    }
    vector<vector<vector<int>>> nextStates=getPossibleNextStates(curState);
    for(int i=0;i<nextStates.size();i++){
        dfs(nextStates[i],endState, bestCost,curCost+1);
    }
}

//IDS(Iterativey Deepening Search):임의의 깊이 제한 l에 대해 이 제한보다 짧은 경로가 존재하는지 dfs를 통해서 확인하고
//성공하면 최소 비용 반환, 아니면 l을 늘려서 추가적으로 수행
int getMinCostIDS(vector<vector<int>> start, vector<vector<int>> end, int growthRate){
    int limit=4;
    int bestCost;
    while(true){
        bestCost=limit+1;
        bestCost=dfs(start,end,bestCost,0);
        if(bestCost!=-1 && bestCost<=limit) return bestCost; 
    }
    return -1;
}