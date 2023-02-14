#include <vector>
#include <queue>

using namespace std;

const int INF=987654321;
int V;
vector<vector<pair<int,int>>> edges;//edges[i][j]=first: i->j로 흘러가는 유량, second: i->j로 보낼수 있는 총량
int networkFlow(int start, int end){
    int totalFlow=0;
    while(true){
        vector<int> parent(V,-1);
        queue<int> q;
        parent[start]=start;
        q.push(start);
        while(!q.empty() && parent[end]==-1){
            int cur=q.front();
            q.pop();
            for(int next=0;next<V;next++){
                if(edges[cur][next].second>edges[cur][next].first && parent[next]==-1){ //흐를 수 있는 경우
                    q.push(next);
                    parent[next]=cur;
                }
            }
        }
        if(parent[end]==-1){ //더 이상 유량 최적화 불가능
            break;
        }
        int amount=INF; //유량을 얼마나 더 보낼수 있는가
        for(int p=end;p!=start;p=parent[p]){
            amount=min(amount, edges[parent[p]][p].second-edges[parent[p]][p].first);
        }
        for(int p=end;p!=start;p=parent[p]){
            edges[parent[p]][p].first+=amount;
            edges[p][parent[p]].first-=amount;
        }
        totalFlow+=amount;
    }
    return totalFlow;
}