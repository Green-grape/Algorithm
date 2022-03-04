/*
i~j의 경로상의 경유점중 하나는 추가적인 비용이 필요하다. 따라서 i~j의 경로중에서 최악(경로 상의 경유점 중 가장 높은 비용의 경유점에서 추가 비용이 발생한 경우)인 상황에서 최단 경로를 구하고 싶다.
이때 해당 i~j의 최단경로는?
*/


#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_VERTEX=501;
const int INF=987654321;
bool isFloydRun=false;
int vertexCount, edgeCount;

vector<vector<int>> adj(MAX_VERTEX, vector<int>(MAX_VERTEX,INF));
vector<vector<int>> w(MAX_VERTEX, vector<int>(MAX_VERTEX,INF));
vector<int> vertexCost(MAX_VERTEX,-1);

int getMinDistance(int,int);

int main(){
    cin >> vertexCount >> edgeCount;
    for(int i=1;i<=vertexCount;i++){
        cin >> vertexCost[i];
    }

    for(int i=0;i<edgeCount;i++){
        int start, end, val;
        cin >> start >> end >> val;
        adj[start][end]=val;
        adj[end][start]=val;
    }
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int start, end;
        cin >> start >> end;
        cout << getMinDistance(start,end)<< "\n";
    }
    return 0;
}

void floyd(){
    for(int i=1;i<=vertexCount;i++){
        for(int j=1;j<=vertexCount;j++){
            if(i==j){
                w[i][j]=0;
                adj[i][j]=0;
            } 
            else w[i][j]=adj[i][j];
        }
    }
    vector<pair<int,int>> order;
    for(int i=1;i<=vertexCount;i++){
        order.push_back(make_pair(vertexCost[i], i));
    }
    sort(order.begin(), order.end());
    for(int k=0;k<vertexCount;k++){
        int via=order[k].second;
        for(int i=1;i<=vertexCount;i++){
            if(adj[i][via]==INF) continue;
            for(int j=1;j<=vertexCount;j++){
                adj[i][j]=min(adj[i][j], adj[i][via]+adj[via][j]);
                w[i][j]=min(w[i][j], adj[i][via]+vertexCost[via]+adj[via][j]);
            }
        }
    }
    isFloydRun=true;
}

int getMinDistance(int start, int end){
    if(!isFloydRun) floyd();
    return w[start][end];
}