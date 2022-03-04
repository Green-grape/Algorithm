/*
두 정점까지의 최단(음수 포함), 최장 거리의 값은?
무한한 경우 INFINITY
도달이 불가능 한 경우 UNREACHABLE 출력 
*/

#include <iostream>
#include <vector>

using namespace std;

const int MAX_GALAXY_COUNT=100;
const int MAX_WORMHOLE_COUNT=1000;
const int MIN_WORMHOLE_VALUE=-1000;
const int INF=987654321;

vector<vector<pair<int,int>>> adj;

vector<int> getMinMaxDistance(int, int);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int galaxyCount, wormholeCount;
        cin >> galaxyCount >> wormholeCount;
        adj.resize(0);
        adj.resize(galaxyCount);
        for(int j=0;j<wormholeCount;j++){
            int start,end,val;
            cin >> start >> end >> val;
            adj[start].push_back(make_pair(end,val));
        }
        vector<int> minMaxDistance=getMinMaxDistance(0,1);
        if(minMaxDistance.size()==0) cout<<"UNREACHABLE";
        else{
            for(int j=0;j<minMaxDistance.size();j++){
                if(minMaxDistance[j]==INF) cout <<"INFINITY ";
                else cout << minMaxDistance[j]<<" ";
            }
        }
        cout <<"\n";
    }
    return 0;
}

vector<int> bellmanford(int start){
    int vertexCount=adj.size();
    vector<int> upper(vertexCount,INF);
    upper[start]=0;
    bool isUpdated;
    for(int i=0;i<vertexCount;i++){
        isUpdated=false;
        for(int j=0;j<vertexCount;j++){
            for(int k=0;k<adj[j].size();k++){
                pair<int,int> next=adj[j][k];
                if(upper[j]+next.second<upper[next.first]){
                    upper[next.first]=upper[j]+next.second;
                    isUpdated=true;
                }
            }
        }
        if(!isUpdated) break;
    }
    if(isUpdated) upper.resize(0);
    return upper;
}

//해당 최단 경로가 존재하지 않을때에도 완화과정이 일어날수 있으므로 일어날수 있는 최대 완화에 대해서 고려
bool isHaveRoad(const vector<int>& distance, const int end){
    if(distance[end]<INF+(MAX_GALAXY_COUNT-1)*MAX_WORMHOLE_COUNT*MIN_WORMHOLE_VALUE) return true;
    return false;
}

void reverseAdjSign(){
    for(int i=0;i<adj.size();i++){
        for(int j=0;j<adj[i].size();j++){
            adj[i][j].second*=-1;
        }
    }
}

vector<int> getMinMaxDistance(int start, int end){
    vector<int> ret;
    vector<int> minDistance=bellmanford(start);
    if(minDistance.size()==0) ret.push_back(INF);
    else ret.push_back(minDistance[end]);

    if(minDistance.size()!=0 && !isHaveRoad(minDistance,end)) return vector<int>();
    reverseAdjSign();
    vector<int> maxDistance=bellmanford(start);
    if(maxDistance.size()==0) ret.push_back(INF);
    else ret.push_back(-maxDistance[end]);
    return ret;
}

