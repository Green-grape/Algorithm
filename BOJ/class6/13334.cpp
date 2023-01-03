#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

//정렬문제는 항상 정렬을 어떻게 수행할 것인지 생각하고 스위핑 문제 복습

bool com(const pair<int,int>& p1, const pair<int,int>& p2){
    if(p1.second==p2.second) return p1.first<p2.first;
    return p1.second<p2.second;
}

struct cmp{
    bool operator()(const pair<int,int>& p1, const pair<int,int>& p2){
        if(p1.first==p2.first) return p1.second>p2.second;
        return p1.first>p2.first;
    }
};

int getMaxCover(vector<pair<int,int>>& lines, int rangeLength){
    sort(lines.begin(),lines.end(),com);
    int startIdx=-1;
    for(int i=0;i<lines.size();i++){
        if(lines[i].second-lines[i].first<=rangeLength){
            startIdx=i;
            break;
        }
    }
    if(startIdx==-1) return 0;
    int ret=1;
    priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> pq;
    for(int i=startIdx;i<lines.size();i++){
        if(lines[i].second-lines[i].first>rangeLength) continue;
        pq.push(lines[i]);
        int lineStart=lines[i].second-rangeLength;
        while(!pq.empty()){
            if(lineStart>pq.top().first){
                pq.pop();
            }else break;
        }
        ret=max(ret,(int)pq.size());
    }
    return ret;
}

int main(){
    int lineCnt;
    cin >> lineCnt;
    vector<pair<int,int>> lines(lineCnt);
    for(int i=0;i<lines.size();i++){
        int v1,v2;
        scanf("%d %d", &v1, &v2);
        if(v1>v2) swap(v1,v2);
        lines[i]={v1,v2};
    }
    int rangeLength;
    cin >> rangeLength;
    cout << getMaxCover(lines, rangeLength)<<"\n";
    return 0;
}