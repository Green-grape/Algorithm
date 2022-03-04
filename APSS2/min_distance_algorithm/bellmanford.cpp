/*
벨만-포드 알고리즘 구현
*/

#include <vector>
 

using namespace std;

const int V=10;
const int INF=987654321;
vector<pair<int,int>> adj[V];


//V번 반복하여 음수 사이클의 존재도 확인, 음수 사이클이 존재하면 빈 배열 반환
//O(|V||E|)
vector<int> bellmanFord(int start){
    vector<int> upper(V,INF);
    vector<int> parent(V);
    for(int i=0;i<parent.size();i++) parent[i]=i;
    upper[start]=0;
    bool isUpdated;
    for(int i=0;i<V;i++){
        //relaxing
        isUpdated=true;
        for(int cur=0;cur<V;cur++){
            for(int j=0;j<adj[cur].size();j++){
                pair<int,int> next=adj[cur][j];
                 //minDistance[nextVertex]<=minDistance[curVertex]+w(curVertex, nextVertex)임을 이용하자
                 //minDistance[nextVertex]<=minDistance[curVertex]+w(curVertex, nextVertex)<=upper[curVertex]+w(curVertex, nextVertext)<upper[nextVertex]이므로
                 //아래 식이 성립한다.
                if(upper[cur]+next.second<upper[next.first]){
                    upper[next.first]=upper[cur]+next.second;
                    parent[next.first]=cur;
                    isUpdated=true;
                }
            }
        }
        if(!isUpdated) break;
    }
    if(isUpdated) upper.resize(0);
    return upper;
}