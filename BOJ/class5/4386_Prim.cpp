#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

const int INF=987654321;
vector<pair<double,double>> stars;
vector<vector<double>> dis;

double getDistance(int sIdx1, int sIdx2){
    return sqrt(pow(stars[sIdx1].first-stars[sIdx2].first,2)+pow(stars[sIdx1].second-stars[sIdx2].second,2));
}

void makeDistance(){
    dis=vector<vector<double>>(stars.size(), vector<double>(stars.size(),INF));
    for(int i=0;i<stars.size();i++){
        for(int j=i+1;j<stars.size();j++){
            dis[i][j]=dis[j][i]=getDistance(i,j);
        }
    }
}

double getMinCost(){
    makeDistance();
    vector<bool> isVisit(stars.size());
    isVisit[0]=true;
    priority_queue<pair<double,int>> pq;
    for(int i=0;i<dis[0].size();i++){
        pq.push({-dis[0][i],i});
    }
    double ret=0;
    while(!pq.empty()){
        double cost=-pq.top().first;
        int cur=pq.top().second;
        pq.pop();
        if(!isVisit[cur]){
            isVisit[cur]=true;
            ret+=cost;
            for(int i=0;i<dis[cur].size();i++){
                if(!isVisit[i]) pq.push({-dis[cur][i],i});
            }
        }
    }
    return ret;
}

int main(){
    int starCnt;
    cin >> starCnt;
    for(int i=0;i<starCnt;i++){
        double x, y;
        cin >> x >> y;
        stars.push_back({x,y});
    }
    double ret=getMinCost();
    printf("%.2lf\n", ret);
    return 0;
}