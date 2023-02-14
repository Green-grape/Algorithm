#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_DIF=199;

int getMinDrawTime(vector<int>& recA, vector<int>& recB){
    vector<int> dif(recA.size()); for(int i=0;i<dif.size();i++) dif[i]=recA[i]-recB[i];
    vector<int> minCost(2*(MAX_DIF+1), INT32_MAX); //minCost[i]=점수차가 i+MAX_DIF일때 B가 최소한으로 수행한 운동시간의 합
    priority_queue<pair<int,int>> pq;
    for(int i=0;i<dif.size();i++){
        minCost[dif[i]+MAX_DIF]=min(minCost[dif[i]+MAX_DIF], recB[i]);
        pq.push({-minCost[dif[i]+MAX_DIF],dif[i]});
    }
    while(!pq.empty()){
        pair<int,int> top=pq.top();
        int cost=-top.first, curDif=top.second;
        pq.pop();
        if(MAX_DIF<curDif || curDif<-MAX_DIF) continue; //절댓값이 200이상인 지점은 확인할 필요가 없다.
        if(minCost[curDif+MAX_DIF]<cost) continue;
        for(int i=0;i<recB.size();i++){
            int nextCost=cost+recB[i], nextDif=curDif+dif[i];
            if(-MAX_DIF<=nextDif && nextDif<=MAX_DIF){
                if(nextCost<minCost[nextDif+MAX_DIF]){
                    minCost[nextDif+MAX_DIF]=nextCost;
                    pq.push({-nextCost, nextDif});
                }
            }
        }
    }
    if(minCost[MAX_DIF]==INT32_MAX) return -1;
    return minCost[MAX_DIF];
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        int nodeCnt;
        cin >> nodeCnt;
        vector<int> recA(nodeCnt), recB(nodeCnt);
        for(int i=0;i<nodeCnt;i++){
            cin >> recA[i] >> recB[i];
        }
        int ret=getMinDrawTime(recA, recB);
        if(ret==-1) cout <<"IMPOSSIBLE"<<"\n";
        else cout <<ret <<"\n";
    }
    return 0;
}