#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

using namespace std;

const int INF=987654321;
const int MAX_COST=1000;
const int MAX_CITY=20;
vector<pair<int,int>> promoteInfo; //promoteInfo[i]=i번째 도시에 홍보할때 드는비용/비용에 따라 늘어나는 인원수

int cache[MAX_COST+1][MAX_CITY];

bool cmp(pair<int,int> p1, pair<int,int> p2){
    return p1.second/(double)p1.first>p2.second/(double)p2.first;
}

int getMinCost(int targetCount, int start){ //start부터 넣어서 targetCount에 도달하기 위한 최소의 비용은?
    if(start>=promoteInfo.size()) return INF;
    int& ret=cache[targetCount][start];
    if(ret!=-1) return ret;
    int mul=0;
    ret=INF;
    while(true){
        if(promoteInfo[start].second*mul>=targetCount) break;
        ret=min(ret,promoteInfo[start].first*mul+getMinCost(targetCount-promoteInfo[start].second*mul,start+1));
        mul++;
    }
    return ret=min(ret,promoteInfo[start].first*mul);
}

int solve(int targetCount){
    sort(promoteInfo.begin(), promoteInfo.end(), cmp);
    memset(cache,-1,sizeof(cache));
    return getMinCost(targetCount,0);
}

int main(){
    int targetCount, cityCount;
    cin >> targetCount >> cityCount;
    for(int i=0;i<cityCount;i++){
        int cost, count;
        cin >> cost >> count;
        promoteInfo.push_back(make_pair(cost,count));
    }
    cout << solve(targetCount) <<"\n";
    return 0;
}