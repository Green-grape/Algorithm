#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAXN=100000;

int adj(int idx, int cur){
    if(idx==0) return cur+1;
    if(idx==1) return cur-1;
    if(idx==2) return cur*2;
    return -1;
}

//1. 먼저 빼고 나중에 곱하는게 더 작다
//2. 다른 방법으로 같은 곳에 오는 것이 가능한 경우 최적화 여부 체크

pair<int,int> bfs(int start, int end){
    if(start==end){
        return make_pair(0,1);
    }
    vector<int> visitCnt(MAXN+1);
    vector<int> visitTime(MAXN+1);
    queue<int> q;
    //visit[start]=true;
    q.push(start);
    visitTime[start]=0;
    visitCnt[start]=1;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=0;i<3;i++){
            int next=adj(i,cur);
            if(next<0 || visitCnt.size()<=next) continue;
            if(visitCnt[next]==0){
                visitCnt[next]=1;
                visitTime[next]=visitTime[cur]+1;
                q.push(next);
            }else if(visitTime[next]>=visitTime[cur]+1){ //최적화 여지 있음(다른 방법으로 같은 숫자에 오는것이 가능함)
                visitTime[next]=visitTime[cur]+1;
                visitCnt[next]++;
                q.push(next);
            }
        }
    }
    return make_pair(visitTime[end],visitCnt[end]);
}

int main(){
    int start, end;
    cin >> start >> end;
    pair<int,int> ret=bfs(start, end);
    cout << ret.first <<"\n"<<ret.second<<"\n";
    return 0;
}