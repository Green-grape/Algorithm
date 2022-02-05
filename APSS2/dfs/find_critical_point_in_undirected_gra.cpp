#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<int> discovered;
vector<bool> isCriticalVertex;
int counter;

//무향 그래프에서 절단점 찾기
//절단점이 아닌 경우
//어떤 서브트리의 루트의 자손들의 모두 역방향 간선을 가지면 절단점X
//루트의 자손의 개수가<=1 인 경우 절단점x

void initialize(const int vertexCount){
    discovered=vector<int>(vertexCount,-1);
    isCriticalVertex=vector<bool>(vertexCount,false);
    counter=0;
}

//i로부터 시작하는 서브트리에 있는 절단점 찾기
//반환값=서브트리의 역방향 간선으로 갈 수 있는 정점 중 가장 먼저 발견된 정점의 순서
int findCriticalVertex(int i,bool isRoot){
    discovered[i]=counter++;
    int children=0;
    int ret=discovered[i];
    for(int j=0;j<adj[i].size();j++){
        int next=adj[i][j];
        if(discovered[next]==-1){
            children++;
            int firstDiscoveredBackVertex=findCriticalVertex(next,false);
            if(!isRoot && firstDiscoveredBackVertex>=discovered[i]){
                isCriticalVertex[i]=true;
            }
            ret=min(ret,firstDiscoveredBackVertex);
        }
        else ret=min(ret,discovered[next]);
    }
    if(isRoot) isCriticalVertex[i]= (children>=2);
    return ret;
}
