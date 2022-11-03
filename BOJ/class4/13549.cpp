#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAXN=100000;
const int INF=987654321;

int bfs(int start, int end){
    vector<int> visitTime(MAXN+1,INF);
    queue<int> q;
    q.push(start);
    visitTime[start]=0;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        if(cur!=0){
            for(int next=cur*2;next<=MAXN;next*=2){
                if(visitTime[next]>visitTime[cur]){
                    visitTime[next]=visitTime[cur];
                    q.push(next);
                }
            }
        }
        int next=cur-1;
        if(visitTime[next]>visitTime[cur]+1){
            visitTime[next]=visitTime[cur]+1;
            q.push(next);
        }
        next=cur+1;
        if(visitTime[next]>visitTime[cur]+1){
            visitTime[next]=visitTime[cur]+1;
            q.push(next);
        }
    }
    return visitTime[end];
}

int main(){
    int start, end;
    cin >> start >> end;
    cout << bfs(start, end) <<"\n";
    return 0;
}