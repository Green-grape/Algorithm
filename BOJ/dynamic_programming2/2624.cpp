/*입력으로 지폐의 금액 T, 동전의 가지 수 k, 각 동전 하나의 금액 pi와 개수 ni가 주어질 때 (i=1, 2,…, k) 
지폐를 동전으로 교환하는 방법의 가지 수를 계산하는 프로그램을 작성하시오.*/

#include <iostream>
#include <vector>

using namespace std;

const int MAX_MONEY=10000;
const int MAX_COIN=100;

vector<pair<int,int>> coins;
vector<vector<int>> cache(MAX_MONEY+1,vector<int>(MAX_COIN,-1));

int divCount(int money, int from){
    if(money==0) return 1;
    if(from>=coins.size()) return 0;
    int& ret=cache[money][from];
    if(ret!=-1) return ret;
    ret=0;
    for(int use=0;use<=coins[from].second;use++){
        if(money-use*coins[from].first>=0) ret+=divCount(money-use*coins[from].first,from+1);
    }
    return ret;
}

int main(){
    int money,coinKind;
    cin >> money;
    cin >> coinKind;
    for(int i=0;i<coinKind;i++){
        int coinValue, coinCount;
        cin >> coinValue >> coinCount;
        coins.push_back(make_pair(coinValue,coinCount));
    }
    cout << divCount(money, 0) <<"\n";
    return 0;
}