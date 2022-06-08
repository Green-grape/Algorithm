#include <iostream>
#include <vector>

using namespace std;

const int MAX_WEIGHT=100000;
const int MAX_N=100;
vector<vector<int>> cache(MAX_WEIGHT+1,vector<int>(MAX_N,-1));
vector<pair<int,int>> items;

int getMaxValue(int remainWeight, int use){
    if(remainWeight==0 || use<0) return 0;
    int& ret=cache[remainWeight][use];
    if(ret!=-1) return ret;
    ret=getMaxValue(remainWeight,use-1);
    if(remainWeight>=items[use].second) ret=max(ret,items[use].first+getMaxValue(remainWeight-items[use].second,use-1));
    return ret;
}

int solve(int totalWeight){
    return getMaxValue(totalWeight,items.size()-1);
}

int main(){
    int itemCount,bagWeight;
    cin >> itemCount >> bagWeight;
    for(int i=0;i<itemCount;i++){
        int value,weight;
        cin >> weight >> value;
        items.push_back(make_pair(value,weight));
    }
    cout << solve(bagWeight) <<"\n";
    return 0;
}