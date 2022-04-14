#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string.h>
#include <stdio.h>

const int MAX_CITY=20;
const double INF=1e200;

double length[MAX_CITY][MAX_CITY];
//std::vector<std::pair<int,int>> nearest[MAX_CITY]; //nearest[i]=도시들을 i에서 가까운 순서대로 정렬해둔것
std::vector<std::pair<double,std::pair<int,int>>> edges;
int cityCount;

double best=INF;
double solve();

int main(){
    int testCase;
    std::cin >> testCase;
    for(int i=0;i<testCase;i++){
        std::cin >> cityCount;
        for(int j=0;j<cityCount;j++){
            for(int k=0;k<cityCount;k++){
                std::cin >> length[j][k];
                if(j!=k){
                    //nearest[j].push_back(std::make_pair(length[j][k],k));
                    edges.push_back(std::make_pair(length[j][k],std::make_pair(j,k)));
                }
            }
            //sort(nearest[j].begin(), nearest[j].end());
        }
        std::sort(edges.begin(),edges.end());
        printf("%.10f\n",solve());
    }
    return 0;
}

// double simplerHeuristic(std::vector<bool> visited){
//     double ret=0;
//     for(int i=0;i<cityCount;i++){
//         if(!visited[i]) ret+=nearest[i][0].first;
//     }
//     return ret;
// }
//MST(Minimun Spaning Tree) 휴리스틱을 이용한 가지치기
class DisjointSet{
private:
    std::vector<int> set;
public:
    DisjointSet(int n){//크기가 n인 disjoint set 생성
        set.resize(n);
        for(int i=0;i<n;i++) set[i]=i;
    }
    int find(int here){ //here가 포함된 집합의 대표를 반환
        if(set[here]==here) return here;
        return set[here]=find(set[here]);
    }
    bool merge(int a,int b){//a가 포함된 집합과 b가 포함된 집합 합치기
        a=find(a);
        b=find(b);
        if(a==b) return false;
        if(a<b) set[a]=b; //더 작은 부모로 결합
        else set[b]=a;
        return true;
    }
};

double mstHeuristic(int here, int visited){
    DisjointSet sets(cityCount);
    double taken=0;
    for(int i=0;i<edges.size();i++){
        int a=edges[i].second.first,b=edges[i].second.second;
        if(a!=0 && a!=here && (visited & (1<<a))) continue;
        if(b!=0 && b!=here && (visited & (1<<b))) continue;
        if(sets.merge(a,b)){
            taken+=edges[i].first;
        }
    }
    return taken;
}

//path의 마지막 네 개의 도시중 가운데 있는 두 도시의 순서를 바꾸었을때 경로가 더 짧아지는가?
//p a b q -> p b a q
//경로가 하나 추가 될때 마다 시행되므로 굳이 모든 path를 검색할 필요 없다.
bool pathSwapPruning(const std::vector<int>& path){
    if(path.size()<4) return false;
    int p=path[path.size()-4];
    int a=path[path.size()-3];
    int b=path[path.size()-2];
    int q=path[path.size()-1];
    return length[p][a]+length[b][q]>length[p][b]+length[a][q];
}

//시작과 끝을 제외한 path의 모든 길이의 부분 경로를 뒤집어 보고 더 짧아지는지 반환
//p {a b c d} q -> q d c b a p
//p a {b c d} q -> p q d c b q
//..
bool pathReversePruning(const std::vector<int>& path){
    if(path.size()<4) return false;
    int q=path[path.size()-2];
    int d=path[path.size()-1];
    for(int i=0;i+3<path.size();i++){
        int p=path[i];
        int a=path[i+1];
        if(length[p][a]+length[d][q]>length[q][d]+length[a][p]) return true;
    }
    return false;
}

//남은 도시의 수가 CACHED_DEPTH이하면 동적 계획법으로 바꾼다.
const int CACHED_DEPTH=5; //-> 결정하는 쉬운 방법 존재 X, map접근 시간과 메모리를 모두 고려해야한다.
std::map<int, double> cache[MAX_CITY][CACHED_DEPTH+1];
double dp(int here, int visited){
    if(visited==(1<<cityCount)-1) return 0.0;
    int remaining=cityCount-__builtin_popcount(visited); //__builtin_pop_count: g++ 내장함수로 주어진 숫자의 이진수 표현에서 1의 개수를 센다
    double& ret=cache[here][remaining][visited];
    if(ret>0) return ret;
    ret=INF;
    for(int next=0;next<cityCount;next++){
        if(visited & (1<<next)) continue;
        ret=std::min(ret, dp(next, visited | (1<<next))+length[here][next]);
    }
    return ret;
}

//path:지금까지 만든 경로, currentLength: 지금까지 만든 경로의 길이, visited: 각 도시의 방문 여부
//나머지 도시들을 모두 방문하는 경로를 만들어보고 가능하면 최적해 갱신
void search(std::vector<int>& path, int visited, double currentLength){
    int cur=path.back();
    if(path.size()==cityCount){
       best=std::min(best, currentLength);
       return;
    }
    //if(pathReversePruning(path)) return;
    //if(best<=currentLength) return; //가장 간단한 최적화(생각보다 효과가 큼(cityCount=12일때 30배정도 빨라짐))
    //if(best<=currentLength+simplerHeuristic(visited)) return; //위에 것보다 수십 배 빠름
    if(path.size()+CACHED_DEPTH>=cityCount){
        best=std::min(best, currentLength+dp(cur,visited));
        return;
    }
    if(best<=currentLength+mstHeuristic(cur, visited)) return;
    for(int next=0;next<cityCount;next++){
        if(visited & (1<<next)) continue;
        path.push_back(next);
        search(path, visited | (1<<next), currentLength+length[cur][next]);
        path.pop_back();
    }
    // for(int i=0;i<nearest[cur].size();i++){
    //     int next=nearest[cur][i].second;
    //     if(visited & (1<<next)) continue;
    //     path.push_back(next);
    //     search(path, visited | (1<<next), currentLength+nearest[cur][i].first);
    //     path.pop_back();
    // }
}

double solve(){
    for(int i=0;i<MAX_CITY;i++){
        for(int j=0;j<=CACHED_DEPTH;j++){
            cache[i][j].clear();
        }
    }
    for(int i=0;i<cityCount;i++){
        std::vector<int> path(1,i);
        search(path,1<<i,0.0);
    }
    return best;
}


