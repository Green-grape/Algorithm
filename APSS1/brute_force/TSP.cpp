#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <stdio.h>

const int MAX_CITY_COUNT=15;
const int INF=987654321;
double length[MAX_CITY_COUNT+1][MAX_CITY_COUNT+1];
int isVisit[MAX_CITY_COUNT];
double cacheLength[MAX_CITY_COUNT+1][1<<MAX_CITY_COUNT];
int cityCount;

using namespace std;

void init();
double getSmallestPath(int start);
double getSmallestPath2(int start, int visit);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        cin >> cityCount;
        for(int j=1;j<=cityCount;j++){
            for(int k=1;k<=cityCount;k++){
                cin >> length[j][k];
            }
        }
        init();
        printf("%.10f\n", getSmallestPath2(0,0));
    }
    return 0;
}

void init(){
    memset(isVisit,0,sizeof(isVisit));
    for(int i=0;i<=MAX_CITY_COUNT;i++){
        length[i][0]=length[0][i]=0;
        for(int j=0;j<(1<<MAX_CITY_COUNT);j++){
            cacheLength[i][j]=-1;
        }
    }
}

//start부터 시작하는 경로중에서 가장 작은 경로의 길이를 반환한다.
double getSmallestPath(int start){
    double ret=INF;
    for(int i=1;i<=cityCount;i++){
        if(!isVisit[i]){
            isVisit[i]=1;
            ret=min(ret,length[start][i]+getSmallestPath(i));
            isVisit[i]=0;
        }
    }
    if(ret==INF) return 0;
    return ret;
}

//책 답안: 지금까지 만든 path가 주어질때 이 경로를 연장해 나머지 도시들을 방문하는 모든 경로중 최소 길이 반환
//O(n!) 모든 path 검색
double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength){
    if(path.size()==cityCount) return currentLength;
    double ret=INF;
    for(int next=0;next<cityCount;next++){
        if(visited[next]) continue;
        visited[next]=true;
        int cur=path.back();
        path.push_back(next);
        ret=min(ret,shortestPath(path,visited,currentLength+length[cur][next]));
        visited[next]=false;
        path.pop_back();
    }
    return ret;
}

//start부터 시작하는 가장 작은 경로를 반환한다. 이때 visited는 이미 방문한 경로
//O(n*2^n)<<<<O(n!)
double getSmallestPath2(int start, int visit){
    if(visit==((1<<cityCount)-1)) return 0;
    double& ret=cacheLength[start][visit];
    if(ret>=0) return ret;
    ret=INF;
    for(int i=1;i<=cityCount;i++){
        if(!(visit & (1<<(i-1)))){
            ret=min(ret,length[start][i]+getSmallestPath2(i,(visit | (1<<(i-1)))));
        }
    }
    return ret;
}