/*
한 갤러리에 CCTV를 설치하면 그 갤러리와 통로로 연결된 모든 갤러리는 감시가 가능하다.
이때 모든 갤러리를 감시하는 감사카메라의 개수의 최소 개수는?
*/
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<bool> isVisited;

void initialize(int);
int getMinCCTVCount();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int galleryCount, hallwayCount;
        cin >> galleryCount >> hallwayCount;
        int g1,g2;
        initialize(galleryCount);
        for(int j=0;j<hallwayCount;j++){
            cin >> g1 >> g2;
            adj[g1].push_back(g2);
            adj[g2].push_back(g1);
        }
        cout << getMinCCTVCount() << "\n";
    }
    return 0;
}

void initialize(int galleryCount){
    adj=vector<vector<int>>(galleryCount, vector<int>());
    isVisited=vector<bool>(galleryCount,false);
}

const int UNWATCHED=0;
const int WATCHED=1;
const int INSTALLED=2;
int installed=0;
int dfs(int i){
    isVisited[i]=true;
    int type[3]={0,0,0};
    for(int j=0;j<adj[i].size();j++){
        int next=adj[i][j];
        if(!isVisited[next]){
            ++type[dfs(next)];
        }
    }
    if(type[UNWATCHED]){
        installed++;
        return INSTALLED;
    }
    if(type[INSTALLED]){
        return WATCHED;
    }
    return UNWATCHED;
}

int getMinCCTVCount(){
    int galleryCount=adj.size();
    installed=0;
    for(int i=0;i<galleryCount;i++){
        if(!isVisited[i] && dfs(i)==UNWATCHED) installed++;
    }
    return installed;
}