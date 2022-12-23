#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

double ccw(pair<double,double> pivot, pair<double,double> v1, pair<double,double> v2){
    double temp=(v1.first-pivot.first)*(v2.second-pivot.second)-(v2.first-pivot.first)*(v1.second-pivot.second);
    if(temp>0) return 1;
    else if(temp==0) return 0;
    else return -1;
}

bool isCross(pair<pair<double,double>, pair<double,double>> line1, pair<pair<double,double>,pair<double,double>> line2){
    double d1=ccw(line1.first, line1.second, line2.first);
    double d2=ccw(line1.first, line1.second, line2.second);
    double d3=ccw(line2.first, line2.second, line1.first);
    double d4=ccw(line2.first, line2.second, line1.second);
    if(d1*d2<=0 && d3*d4<=0){
        if(d1*d2==0 && d3*d4==0){
            pair<double,double> p1=min(line1.first, line1.second);
            pair<double,double> p2=max(line1.first, line1.second);
            pair<double,double> p3=min(line2.first, line2.second);
            pair<double,double> p4=max(line2.first, line2.second);
            return (p1<=p4 && p3<=p2);
        }
        return true;
    }
    return false;
}

int getParent(int cur, vector<int>& parent){
    if(parent[cur]==cur) return cur;
    return parent[cur]=getParent(parent[cur],parent);
}

void unionLine(int i, int j, vector<int>& parent){
    int p1=getParent(i,parent), p2=getParent(j,parent);
    if(p1<p2) parent[p2]=p1;
    else parent[p1]=p2;
}

pair<int,int> solve(vector<pair<pair<double,double>,pair<double,double>>>& lines){
    vector<int> parent(lines.size());
    for(int i=0;i<parent.size();i++) parent[i]=i;
    for(int i=0;i<lines.size();i++){
        for(int j=i+1;j<lines.size();j++){
            if(isCross(lines[i], lines[j])){
                unionLine(i,j,parent);
            }
        }
    }
    vector<int> parentCnt(lines.size());
    int maxParentCnt=0, parentKind=0;
    for(int i=0;i<parent.size();i++){
        parentCnt[getParent(i,parent)]++;
        if(maxParentCnt<parentCnt[getParent(i,parent)]) maxParentCnt=parentCnt[getParent(i,parent)];
        if(parentCnt[getParent(i,parent)]==1) parentKind++;
    }
    return {parentKind, maxParentCnt};
}

int main(){
    int lineCnt;
    cin >> lineCnt;
    vector<pair<pair<double,double>,pair<double,double>>> lines(lineCnt);
    for(int i=0;i<lineCnt;i++){
        double x1,y1,x2,y2;
        scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
        lines[i]={{x1,y1},{x2,y2}};
    }
    pair<int,int> ret=solve(lines);
    cout << ret.first <<"\n"<<ret.second <<"\n";
    return 0;
}