/*
행복 유치원 원장인 태양이는 어느 날 N명의 원생들을 키 순서대로 일렬로 줄 세우고, 총 K개의 조로 나누려고 한다. 각 조에는 원생이 적어도 한 명 있어야 하며, 같은 조에 속한 원생들은 서로 인접해 있어야 한다. 조별로 인원수가 같을 필요는 없다.
이렇게 나뉘어진 조들은 각자 단체 티셔츠를 맞추려고 한다. 
조마다 티셔츠를 맞추는 비용은 조에서 가장 키가 큰 원생과 가장 키가 작은 원생의 키 차이만큼 든다. 
최대한 비용을 아끼고 싶어 하는 태양이는 K개의 조에 대해 티셔츠 만드는 비용의 합을 최소로 하고 싶어한다. 
태양이를 도와 최소의 비용을 구하자.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getMinCost(vector<int>& heights,int team){
    vector<pair<int,int>> dif;
    for(int i=1;i<heights.size();i++){
        dif.push_back(make_pair(heights[i-1]-heights[i],i-1));
    }
    sort(dif.begin(),dif.end());
    vector<int> pivot;
    // for(int i=0;i<dif.size();i++){
    //     cout << dif[i].first <<" "<<dif[i].second<<" ";
    // }
    //cout <<"\n";
    for(int i=0;i<team-1;i++){
        pivot.push_back(dif[i].second);
    }
    sort(pivot.begin(),pivot.end());
    // for(int i=0;i<pivot.size();i++){
    //     cout << pivot[i]<<" ";
    // }
    // cout <<"\n";
    int before=0,ret=0;
    for(int i=0;i<pivot.size();i++){
        ret+=(heights[pivot[i]]-heights[before]);
        before=pivot[i]+1;
    }
    if(before<heights.size())ret+=heights[heights.size()-1]-heights[before];
    return ret;
}

int main(){
    int heightCount, teamCount;
    cin >> heightCount >> teamCount;
    vector<int> heights(heightCount);
    for(int i=0;i<heightCount;i++){
        cin >> heights[i];
    }
    cout << getMinCost(heights,teamCount) <<"\n";
    return 0;
}