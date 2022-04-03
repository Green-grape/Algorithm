#include <vector>
#include <iostream>
#include <algorithm>

int getMaxWin(const std::vector<int>&, const std::vector<int>&);

int main(){
    int testCase;
    std::cin >> testCase;
    for(int i=0;i<testCase;i++){
        int playerCount,player;
        std::vector<int> opponent;
        std::vector<int> our;
        std::cin >> playerCount;
        for(int j=0;j<playerCount;j++){
            std::cin>>player;
            opponent.push_back(player);
        }
        for(int j=0;j<playerCount;j++){
            std::cin>>player;
            our.push_back(player);
        }
        std::cout << getMaxWin(opponent, our) <<"\n";
    }
    return 0;
}

int getMaxWin(const std::vector<int>& opponent, const std::vector<int>& our){
    std::vector<int> sortedOpponent=opponent, sortedOur=our;
    sort(sortedOpponent.begin(),sortedOpponent.end());
    sort(sortedOur.begin(), sortedOur.end());
    int opIdx=0, ourIdx=0, ret=0;;
    while(opIdx<sortedOpponent.size() && ourIdx<sortedOur.size()){
        if(sortedOur[ourIdx]>=sortedOpponent[opIdx]){
            ret++;
            opIdx++;
        }
        ourIdx++;
    }
    return ret;
}