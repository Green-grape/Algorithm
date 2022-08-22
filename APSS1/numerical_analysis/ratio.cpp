#include <iostream>
#include <random>

const long long MAX=2000000000;

class RandomGenerator{
private:
    long long maxNum;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis;
public:
    RandomGenerator(long long _maxNum){
        maxNum=_maxNum;
        gen=std::mt19937(rd());
        dis=std::uniform_int_distribution<int>(0,maxNum);
    }
    std::pair<long long, long long> getRandomPair(){
        long long ran1=dis(gen);
        long long ran2=dis(gen);
        if(ran1<ran2) std::swap(ran1,ran2);
        return std::make_pair(ran1,ran2);
    }
};

int getMinWinCount(long long winCount, long long playCount, int curWinRate);
int getMinWinCount2(long long winCount, long long playCount, int curWinRate);
int winRate(long long winCount, long long playCount);

int main(){
    int testCase;
    std::cin >> testCase;
    RandomGenerator rng(MAX);
    for(int i=0;i<testCase;i++){
        long long playCount, winCount;
        std::cin >> playCount >> winCount;
        int res1=getMinWinCount(winCount, playCount, winRate(winCount, playCount));
        std::cout << res1 <<"\n";
    }
    return 0;
}

int winRate(long long winCount, long long playCount){
    return (winCount*100)/playCount;
}

int getMinWinCount2(long long winCount, long long playCount,int curWinRate){
    if(winRate(winCount+MAX,playCount+MAX)==curWinRate) return -1;
    int ret=0;
    while(winRate(winCount+ret,playCount+ret)==curWinRate){
        ret++;
    }
    return ret;

}

int getMinWinCount(long long winCount, long long playCount, int curWinRate){
    if(winRate(winCount+MAX,playCount+MAX)==curWinRate) return -1;
    long long left=0,right=MAX;
    while(left+1<right){
        long long mid=(left+right)/2;
        if(winRate(winCount+mid, playCount+mid)==curWinRate){
            left=mid;
        }
        else{
            right=mid;
        }
    }
    return right;
}