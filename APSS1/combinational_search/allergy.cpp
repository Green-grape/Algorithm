#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

const int INF=987654321;
int friendCount, foodCount;
std::vector<std::string> friends;
std::map<std::string,int> friendsIndex;
std::vector<std::vector<int>> eatableFoods;
std::vector<std::vector<int>> foodEaters;
int best;

int solve();

int main(){
    int testCase;
    std::cin>> testCase;
    for(int i=0;i<testCase;i++){
        std::cin >> friendCount >> foodCount;
        for(int j=0;j<friendCount;j++){
            std::string friendName;
            std::cin >> friendName;
            friends.push_back(friendName);
            friendsIndex[friendName]=j;
        }
        eatableFoods.resize(friendCount);
        foodEaters.resize(foodCount);
        for(int j=0;j<foodCount;j++){
            int eatableCount;
            std::cin >> eatableCount;
            for(int k=0;k<eatableCount;k++){
                std::string friendName;
                std::cin >> friendName;
                int fIndex=friendsIndex[friendName];
                eatableFoods[fIndex].push_back(j);
                foodEaters[j].push_back(fIndex);
            }
        }
        std::cout << solve() <<"\n";
        friends.resize(0);
        friendsIndex.clear();
        eatableFoods.resize(0);
        foodEaters.resize(0);
    }
}

void search(std::vector<std::pair<int,int>>& sortedEater, std::vector<bool>& eatingState, int chosen){
    if(chosen>=best) return;
    int start=-1;
    for(int i=0;i<sortedEater.size();i++){
        int eater=sortedEater[i].second;
        if(!eatingState[eater]){
            start=eater;
            break;
        }
    }
    if(start==-1){
        best=std::min(best,chosen);
        return;
    }
    for(int i=0;i<eatableFoods[start].size();i++){
        int food=eatableFoods[start][i];
            std::vector<int> changed;
            for(int j=0;j<foodEaters[food].size();j++){
                int eater=foodEaters[food][j];
                if(!eatingState[eater]){
                    changed.push_back(eater);
                    eatingState[eater]=true;
                }
            }
            search(sortedEater, eatingState, chosen+1);
            for(int j=0;j<changed.size();j++){
                eatingState[changed[j]]=false;
            }
    }
    
}

bool compare(int idx1,int idx2){
    return foodEaters[idx1].size()>foodEaters[idx2].size();
}

int solve(){
    best=INF;
    std::vector<bool> foodState(foodCount,false);
    std::vector<bool> eatingState(friendCount,false);
    std::vector<std::pair<int,int>> sortedEater;
    for(int i=0;i<friendCount;i++){
        sortedEater.push_back(std::make_pair(eatableFoods[i].size(), i));
    }
    std::sort(sortedEater.begin(),sortedEater.end());
    for(int i=0;i<eatableFoods.size();i++){
        std::sort(eatableFoods[i].begin(),eatableFoods[i].end(),compare);
    }
    search(sortedEater, eatingState,0);
    return best;
}