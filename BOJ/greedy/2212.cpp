#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getMinCost(vector<int>& position,int team){
    vector<pair<int,int>> dif;
    for(int i=1;i<position.size();i++){
        dif.push_back(make_pair(position[i-1]-position[i],i-1));
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
        ret+=(position[pivot[i]]-position[before]);
        before=pivot[i]+1;
    }
    if(before<position.size())ret+=position[position.size()-1]-position[before];
    return ret;
}

int main(){
    int positionCount, teamCount;
    cin >> positionCount >> teamCount;
    vector<int> position(positionCount);
    for(int i=0;i<positionCount;i++){
        cin >> position[i];
    }
    sort(position.begin(),position.end());
    position.erase(unique(position.begin(),position.end()),position.end());
    cout << getMinCost(position,min(teamCount,(int)position.size())) <<"\n";
    return 0;
}