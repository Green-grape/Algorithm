#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

int getMinLengthOfJoinedStr(const std::vector<int>&);

int main(){
    int testCase;
    std::cin >> testCase;
    for(int i=0;i<testCase;i++){
        int stringCount;
        std::cin >> stringCount;
        std::vector<int> stringLength(stringCount);
        for(int j=0;j<stringCount;j++){
            std::cin >> stringLength[j];
        }
        std::cout << getMinLengthOfJoinedStr(stringLength) <<"\n";
    }
    return 0;
}

int getMinLengthOfJoinedStr(const std::vector<int>& stringLength){
    std::priority_queue<int,std::vector<int>,std::greater<int>> stringLengthQueue;
    for(int i=0;i<stringLength.size();i++){
        stringLengthQueue.push(stringLength[i]);
    }
    int ret=0;
    while(stringLengthQueue.size()>=2){
        int minString1=stringLengthQueue.top();
        stringLengthQueue.pop();
        int minString2=stringLengthQueue.top();
        stringLengthQueue.pop();
        ret+=(minString1+minString2);
        stringLengthQueue.push(minString1+minString2);
    }
    return ret;
}