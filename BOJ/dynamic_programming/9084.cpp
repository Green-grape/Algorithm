/*
동전의 종류가 주어질 때에 주어진 금액을 만드는 모든 방법을 세는 프로그램을 작성하시오.
동전 금액은 정수로서 1원부터 10000원, 개수는 최대 20개이며 만들어야하는 가격은 최대 10000이다
*/

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int MAX_VALUE=10000;
const int MAX_COIN=20;

int cache[MAX_VALUE+1][MAX_COIN];
vector<int> coinValue;

int countKind(int value, int start){ //start부터 동전을 사용해서 value를 만드는 방법의 가짓수는?
    if(value==0) return 1;
    if(value<0 || start>=coinValue.size()) return 0;
    int& ret=cache[value][start];
    if(ret!=-1) return ret;
    ret=0;
    for(int mul=0;mul*coinValue[start]<=value;mul++){
        ret+=countKind(value-mul*coinValue[start],start+1);
    }
    return ret;
}

int solve(int totalValue){
    memset(cache,-1,sizeof(cache));
    return countKind(totalValue,0);
}

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int coinCount;
        cin >> coinCount;
        coinValue.resize(coinCount);
        for(int j=0;j<coinCount;j++){
            cin >> coinValue[j];
        }
        int totalValue;
        cin >> totalValue;
        cout << solve(totalValue) <<"\n";
        coinValue.resize(0);
    }
    return 0;
}