#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

const int INF=987654321;
int V,E;
vector<vector<pair<int,int>>> adj;
vector<int> weights; //정렬된 모든 가중치 목록

//시작점과 끝점을 잇는 경로중에서 사용 가중치 범위가 [lo,hi]인 경로가 있는가?
bool hasPath(int lo, int hi){
    queue<int> q;
    vector<bool> isVisit(adj.size());
    q.push(0);
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=0;i<adj[cur].size();i++){
            int next=adj[cur][i].first, cost=adj[cur][i].second;
            if(!isVisit[next] && lo<=cost && cost<=hi){
                isVisit[next]=true;
                q.push(next);
            }
        }
    }
    return isVisit[adj.size()-1];
}

//가중치가 weights[low]이상인 간선으로 시작점과 끝점을 연결하는 경로를 만들기 위해 필요한 경로의 최소 상한
//연결 X:INF
int binaryMinUpperBound(int low){ 
    int lo=low-1, hi=weights.size();
    while(lo+1<hi){
        int mid=(lo+hi)/2;
        if(hasPath(weights[low],weights[mid])){
            hi=mid;
        }else{
            lo=mid;
        }
    }
    if(hi==weights.size()) return INF;
    return weights[hi];
}

//O(E^2LgE)
int minWeightDifference(){
    int ret=INF;
    for(int i=0;i<weights.size();i++){
        ret=min(ret, binaryMinUpperBound(i)-weights[i]);
    }
    return ret;
}

//O(E^2)
int optimized_brute(){
    int ret=INF, foundPathUsing=0;
    for(int lo=0;lo<weights.size();lo++){
        bool foundPath=false;
        for(int hi=foundPathUsing;hi<weights.size();hi++){
            if(hasPath(weights[lo],weights[hi])){ //최대 2*E번 호출
                ret=min(ret, weights[hi]-weights[lo]);
                foundPath=true;
                foundPathUsing=hi; //상한이 내려갈 이유가 없다.
                break;
            }
        }
    }
    return ret;
}


//brute의 hasPath 반환값에 따라 반복문이 수행된다는 것에 따라 깔끔하게 변형한것
int scanning(){
    int lo=0,hi=0,ret=INF;
    while(lo<weights.size() && hi<weights.size()){
        if(hasPath(weights[lo],weights[hi])){
            ret=min(ret, weights[hi]-weights[lo]);
            lo++;
        }else{
            hi++;
        }
    }
    return ret;
}

int main(){

}