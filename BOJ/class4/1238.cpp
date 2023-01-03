#include <iostream>
#include <vector>

using namespace std;

const int INF=987654321;
vector<vector<int>> dis;

void makeTable(){ //플로이드-와샬 알고리즘으로 minDisTable 생성
    for(int k=1;k<dis.size();k++){
        for(int i=1;i<dis.size();i++){
            for(int j=1;j<dis.size();j++){
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }
}

int getMaxDis(int endPoint){
    makeTable();
    int ret=0;
    for(int v=1;v<dis.size();v++){
        ret=max(ret, dis[v][endPoint]+dis[endPoint][v]);
    }
    return ret;
}

int main(){
    int nodeCnt, edgeCnt, endPoint;
    cin >> nodeCnt >> edgeCnt >> endPoint;
    dis=vector<vector<int>>(nodeCnt+1, vector<int>(nodeCnt+1,INF));
    for(int i=1;i<=nodeCnt;i++) dis[i][i]=0;
    for(int i=0;i<edgeCnt;i++){
        int v1,v2,cost;
        scanf("%d %d %d", &v1, &v2, &cost);
        dis[v1][v2]=cost;
    }
    cout << getMaxDis(endPoint) <<"\n";
    return 0;
}