#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

const int MAX_BUDGET=1e7;
vector<pair<int,int>> sushi;//price, need
int budget;
int c[201];

int getMaxNeed();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int sushiCount;
        cin >> sushiCount >> budget;
        budget/=100;
        for(int j=0;j<sushiCount;j++){
            int price, need;
            cin >> price >> need;
            sushi.push_back(make_pair(price/100, need));
        }
        cout << getMaxNeed() << "\n";
        sushi.resize(0);
    }
}

int getMaxNeed(){
    int ret=0;
    c[0]=0;
    for(int i=1;i<=budget;i++){
        int tempRet=0;
        for(int j=0;j<sushi.size();j++){
            if(i>=sushi[j].first){
                tempRet=max(tempRet,c[(i-sushi[j].first)%201]+sushi[j].second);
            }
        }
        c[i%201]=tempRet;
    }
    return c[budget%201];
}