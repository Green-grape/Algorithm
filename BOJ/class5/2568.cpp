#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

//너무 복잡하게 생각하지 말자
//lis 복습

int setLoc(int val, vector<int>& lis){
    if(lis.empty() || lis.back()<val){
        lis.push_back(val);
        return lis.size()-1;
    }
    int idx=lower_bound(lis.begin(),lis.end(),val)-lis.begin();
    lis[idx]=val;
    return idx;
}

vector<int> solve(vector<pair<int,int>>& lines){
    vector<pair<pair<int,int>,int>> sortedLines(lines.size());
    for(int i=0;i<lines.size();i++){
        sortedLines[i]={lines[i],i};
    }
    sort(sortedLines.begin(),sortedLines.end());
    vector<int> loc(sortedLines.size());
    vector<int> lis;
    for(int i=1;i<sortedLines.size();i++){
        loc[sortedLines[i].second]=setLoc(sortedLines[i].first.second, lis);
    }
    int idx=lis.size()-1;
    vector<bool> isUsed(sortedLines.size());
    for(int i=sortedLines.size()-1;i>=1;i--){
        if(loc[sortedLines[i].second]==idx){
            isUsed[sortedLines[i].second]=true;
            idx--;
        }   
    }
    vector<int> ret;
    for(int i=1;i<isUsed.size();i++){
        if(!isUsed[i]) ret.push_back(lines[i].first);
    }
    return ret;
}

int main(){
    int pairCnt;
    cin >> pairCnt;
    vector<pair<int,int>> lines(pairCnt+1);
    for(int i=1;i<=pairCnt;i++){
        int start, end;
        scanf("%d %d", &start, &end);
        lines[i]={start,end};
    }
    vector<int> ret=solve(lines);
    cout << ret.size() <<"\n";
    for(int i=0;i<ret.size();i++){
        printf("%d\n", ret[i]);
    }
    return 0;
}