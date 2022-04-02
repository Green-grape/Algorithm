#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <string.h>

using namespace std;
const int MAX_ITEM_COUNT=100;
const int MAX_TOTAL_WEIGHT=1000;
int cache[MAX_TOTAL_WEIGHT+1][MAX_ITEM_COUNT];
int itemCount, totalWeight;
vector<pair<int,int>> itemInfo;
vector<string> itemName;

int getMaxNeed(int weight, int start);
void reconstruct(int weight,int item,vector<string>& ret);
void init();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        cin >> itemCount >> totalWeight;
        init();
        for(int j=0;j<itemCount;j++){
            string name;
            int need, weight;
            cin >> name >> weight >> need;
            itemInfo.push_back(make_pair(weight,need));
            itemName.push_back(name);
        }
        int ret=getMaxNeed(totalWeight,0);
        vector<string> items;
        reconstruct(totalWeight,0,items);
        cout << ret << " " <<items.size()<<"\n";
        for(int i=0;i<items.size();i++){
            cout << items[i] <<"\n";
        }
    }
    return 0;
}

void init(){
    memset(cache,-1,sizeof(cache));
    itemInfo.resize(0);
    itemName.resize(0);
}


//남은 무게 weight에 대하여 start~itemCount-1까지를 선택해서 얻을 수 있는 Need의 최대값
int getMaxNeed(int weight, int start){
    if(start>=itemCount) return 0;
    int& ret=cache[weight][start];
    if(ret!=-1) return ret;
    int startSelect=0;
    if(weight-itemInfo[start].first>=0) startSelect=itemInfo[start].second+getMaxNeed(weight-itemInfo[start].first,start+1);
    int startNotSelect=getMaxNeed(weight,start+1);
    ret=max(startSelect,startNotSelect);
    return ret;
}

//답이 가능한 경우가 2개만 존재하는 것을 이용한다.
void reconstruct(int weight,int item,vector<string>& ret){
    if(item==itemCount) return;
    if(getMaxNeed(weight,item)==getMaxNeed(weight,item+1)) reconstruct(weight,item+1,ret);
    else{
        ret.push_back(itemName[item]);
        reconstruct(weight-itemInfo[item].first,item+1,ret);
    }
}