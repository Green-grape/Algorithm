/*
기둥의 개수가 4개인 하노이의 탑 문제 풀기
*/

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string.h>

using namespace std;

int getMinDistance(const vector<vector<int>>, const vector<vector<int>>,const int);
int getMinDistanceBidirectional(const vector<vector<int>>, const vector<vector<int>>, const int);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int blockNum;
        cin >> blockNum;
        vector<vector<int>> start(4,vector<int>()),end(4,vector<int>());
        for(int j=0;j<4;j++){
            int blockCount;
            cin >> blockCount;
            for(int k=0;k<blockCount;k++){
                int temp;
                cin >> temp;
                start[j].push_back(temp);
            }
        }
        for(int j=0;j<4;j++){
            int blockCount;
            cin >> blockCount;
            for(int k=0;k<blockCount;k++){
                int temp;
                cin >> temp;
                end[j].push_back(temp);
            }
        }
        cout << getMinDistanceBidirectional(start, end,blockNum) <<"\n";
    }
    return 0;
}

//State의 표현을 간단하게 해서 메모리를 절약한다
//idx:블록번호, value:기둥번호
int getValue(int bitArr, int idx){
    return (bitArr >> (idx*2)) & 3;
}

int setValue(int bitArr, int idx, int value){
    return (bitArr & ~(3<<(idx*2))) | (value<<(idx*2));
}

int arrToBitArr(const vector<vector<int>> arr){
    int ret=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<arr[i].size();j++){
            ret=setValue(ret, arr[i][j], i);
        }
    }
    return ret;
}

vector<int> getPossibleNext(int cur,int movingBlock,int movingBlocks[]){
    vector<int> ret;
    for(int i=0;i<4;i++){
        if(movingBlock<movingBlocks[i] || movingBlocks[i]==-1){
            int next=setValue(cur,movingBlock,i);
            ret.push_back(next);
        }
    }
    return ret;
}


int getMinDistance(const vector<vector<int>> start, const vector<vector<int>> end, const int disc){
    if(start==end) return 0;
    int startState=arrToBitArr(start);
    int endState=arrToBitArr(end);
    queue<int> q;
    map<int,int> states;
    q.push(startState);
    states[startState]=0;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        int top[4]={-1,-1,-1,-1};
        for(int i=disc;i>=1;i--){
            top[getValue(cur,i)]=i;
        }
        int cost=states[cur];
        for(int i=0;i<4;i++){
            if(top[i]==-1) continue;
            vector<int> possibleNext=getPossibleNext(cur, top[i],top);
            for(int j=0;j<possibleNext.size();j++){
                if(possibleNext[j]==endState) return cost+1;
                if(states.find(possibleNext[j])==states.end()){
                    states[possibleNext[j]]=cost+1;
                    q.push(possibleNext[j]);
                }
            }
        }
    }
    return -1;
}

int increaseCost(int cost){
    return cost > 0 ? cost+1:cost-1;
}

int getSign(int cost){
    return cost >0 ? 1:-1;
}

const int MAX_BLOCK=12;

int getMinDistanceBidirectional(const vector<vector<int>> start, const vector<vector<int>> end, const int disc){
    if(start==end) return 0;
    int startState=arrToBitArr(start);
    int endState=arrToBitArr(end);
    queue<int> q;
    map<int,int> states;
    states[startState]=1;
    states[endState]=-1;
    q.push(startState);
    q.push(endState);
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        int top[4]={-1,-1,-1,-1};
        for(int i=disc;i>=1;i--){
            top[getValue(cur,i)]=i;
        }
        int cost=states[cur];
        for(int i=0;i<4;i++){
            if(top[i]==-1) continue;
            vector<int> possibleNext=getPossibleNext(cur, top[i],top);
            for(int j=0;j<possibleNext.size();j++){
                map<int,int>::iterator it=states.find(possibleNext[j]);
                if(it==states.end()){
                    states[possibleNext[j]]=increaseCost(cost);
                    q.push(possibleNext[j]);
                }
                else if(getSign(states[cur])!=getSign(states[possibleNext[j]])){
                    return abs(states[cur])+abs(states[possibleNext[j]])-1;
                }
            }
        }
    }
    return -1;
}