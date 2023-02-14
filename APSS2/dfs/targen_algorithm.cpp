#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int>> adj; //그래프
vector<int> discovered; //각 노드의 방문 순서
vector<int> scc; //각 노드의 scc 번호
int vertexId,sccId; //현재 노드 방문 순서
stack<int> notDeterminated; //아직 scc가 구성되지 않은 것들의 집합


//cur을 루트로 하는 서브트리에서 역방향 간선이나 교차 간선을 통해서 갈 수 있는 정점 중 최소 발견 순서 반환
int make_scc(int cur){
    int ret=discovered[cur]=vertexId++;
    notDeterminated.push(cur);
    for(int i=0;i<adj[cur].size();i++){
        int next=adj[cur][i];
        if(discovered[next]==-1){ //아직 탐색 안됨
            ret=min(ret, make_scc(next));
        }else if(scc[next]==-1){ //아직 scc가 구성이 안됨
            ret=min(ret, scc[next]);
        }
    }
    if(ret==discovered[cur]){ //현재 노드가 루트 노드인 경우
        while(true){
            int v=notDeterminated.top();
            notDeterminated.pop();
            scc[v]=sccId;
            if(v==cur) break;
        }
        sccId++;
    }
    return ret;
}

vector<int> tarjan(){
    scc=discovered=vector<int>(adj.size(),-1);
    sccId=vertexId=0;
    for(int i=0;i<adj.size();i++) if(discovered[i]==-1) make_scc(i);
    return scc;
}