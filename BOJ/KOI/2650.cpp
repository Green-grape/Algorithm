#include <iostream>
#include <vector>

using namespace std;

bool isInRange(pair<int,int> start, pair<int,int> end, pair<int,int> v){
    if(start.first==end.first){
        if(start.second>end.second) swap(start,end);
        return v.first==start.first && start.second<=v.second && v.second<=end.second;
    }
    if(start.first>end.first) return isInRange(end,start,v);
    if(start.first==1 && end.first==2){
        return v.first==3 || (v.first==1 && v.second<=start.second) || (v.first==2 && v.second<=end.second);
    }
    if(start.first==1 && end.first==3){
        return (v.first==1 && v.second<=start.second) || (v.first==3 && v.second<=end.second);
    }
    if(start.first==1 && end.first==4){
        return (v.first==1 && v.second>=start.second) || (v.first==4 && v.second<=end.second);
    }
    if(start.first==2 && end.first==3){
        return (v.first==2 && v.second<=start.second) || (v.first==3 && v.second>=end.second);
    }
    if(start.first==2 && end.first==4){
        return (v.first==2 && v.second>=start.second) || (v.first==4 && v.second>=end.second);
    }
    if(start.first==3 && end.first==4){
        return v.first==1 || (v.first==3 && v.second<=start.second) || (v.first==4 && v.second<=end.second);
    }
    return false;
}

pair<int,int> solve(vector<pair<pair<int,int>,pair<int,int>>>& lines){
    vector<int> maxJoin(lines.size());
    int totalJoin=0;
    for(int i=0;i<lines.size();i++){
        for(int j=i+1;j<lines.size();j++){
            if(isInRange(lines[i].first, lines[i].second, lines[j].first) ^ isInRange(lines[i].first,lines[i].second,lines[j].second)){
                maxJoin[i]++;
                maxJoin[j]++;
                totalJoin++;
            }
        }
    }
    pair<int,int> ret={totalJoin, 0};
    for(int i=0;i<maxJoin.size();i++){
        ret.second=max(ret.second, maxJoin[i]);
    }
    return ret;
}

int main(){
    int n;
    cin >> n;
    vector<pair<pair<int,int>,pair<int,int>>> lines;
    int p1,l1,p2,l2;
    while(scanf("%d %d %d %d", &p1, &l1, &p2, &l2)!=EOF){
        lines.push_back({{p1,l1},{p2,l2}});
    }
    pair<int,int> ret=solve(lines);
    cout << ret.first <<"\n"<<ret.second <<"\n";
    return 0;
}