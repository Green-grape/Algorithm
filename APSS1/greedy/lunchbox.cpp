#include <vector>
#include <iostream>
#include <algorithm>
//한 번에 음식은 여러개를 먹을 수 있지만 조리는 한 가지밖에 하지 못하며 조리된 직후에 음식을 먹는다고 가정하자
//이때 음식의 조리시간과 먹는 시간이 주어질때 최소의 점심시간은?
//식사시간: 모든 음식의 조리와 먹는 것이 종료되는 시간

int getMinLunchTime(const std::vector<int>&, const std::vector<int>&);

int main(){
    int testCase;
    std::cin >> testCase;
    for(int i=0;i<testCase;i++){
        int lunchBoxCount;
        std::cin >> lunchBoxCount;
        std::vector<int> cookingTime(lunchBoxCount);
        std::vector<int> eatingTime(lunchBoxCount);
        for(int j=0;j<lunchBoxCount;j++){
            std::cin >> cookingTime[j];
        }
        for(int j=0;j<lunchBoxCount;j++){
            std::cin >> eatingTime[j];
        }
        std::cout<<getMinLunchTime(cookingTime, eatingTime)<<"\n";
    }
    return 0;
}

int getMinLunchTime(const std::vector<int>& cookingTime, const std::vector<int>& eatingTime){
    std::vector<std::pair<int,int>> sortedEatingTime(eatingTime.size());
    for(int i=0;i<eatingTime.size();i++){
        sortedEatingTime[i]=std::make_pair(eatingTime[i],i);
    }
    std::sort(sortedEatingTime.begin(),sortedEatingTime.end(),std::greater<std::pair<int,int>>());
    int ret=-1;
    int sumCookingTime=0;
    for(int i=0;i<sortedEatingTime.size();i++){
        int eatingTime=sortedEatingTime[i].first;
        int index=sortedEatingTime[i].second;
        sumCookingTime+=cookingTime[index];
        ret=std::max(ret, sumCookingTime+eatingTime);
    }
    return ret;
}