#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<pair<double, double>> stars;

double getDistance(int sIdx1, int sIdx2){
    return sqrt(pow(stars[sIdx1].first-stars[sIdx2].first,2)+pow(stars[sIdx1].second-stars[sIdx2].second,2));
}

vector<pair<double,pair<int,int>>> makeStarLines(){
    vector<pair<double,pair<int,int>>> ret;
    for(int i=0;i<stars.size();i++){
        for(int j=i+1;j<stars.size();j++){
            ret.push_back({getDistance(i,j),{i,j}});
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

int getParent(int cur, vector<int>& parent){
    if(parent[cur]==cur) return cur;
    return parent[cur]=getParent(parent[cur],parent);
}
void unify(int c1, int c2, vector<int>& parent){
    int p1=getParent(c1,parent),p2=getParent(c2,parent);
    if(p1<p2) parent[p2]=p1;
    else parent[p1]=p2;
}

double getMinCost(){
    vector<pair<double,pair<int,int>>> starLines=makeStarLines();
    double ret=0;
    vector<int> parent(stars.size());
    for(int i=0;i<parent.size();i++) parent[i]=i;
    for(int i=0;i<starLines.size();i++){
        double cost=starLines[i].first;
        int s1=starLines[i].second.first, s2=starLines[i].second.second;
        int p1=getParent(s1,parent), p2=getParent(s2,parent);
        if(p1!=p2){
            unify(s1,s2,parent);
            ret+=cost;
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