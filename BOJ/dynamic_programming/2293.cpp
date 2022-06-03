/*
n가지 종류의 동전이 있다. 각각의 동전이 나타내는 가치는 다르다.
이 동전을 적당히 사용해서, 그 가치의 합이 k원이 되도록 하고 싶다. 그 경우의 수를 구하시오. 각각의 동전은 몇 개라도 사용할 수 있다.
사용한 동전의 구성이 같은데, 순서만 다른 것은 같은 경우이다.
1<=n<=100, 1<=k<=10000
*/

#include <iostream>
#include <vector>
#include <string.h>

const int MAX_VALUE=10000;
/*복습*/

using namespace std;
vector<int> coinValue;
//int cache[MAX_VALUE+1];
int cache[2][MAX_VALUE+1]={0,};

// int solve(int value){
//     cache[0]=1; //기저값(cache[0]처리)
//     for(int i=1;i<coinValue.size();i++){ //동전을 사용하는 가지수 증가
//         for(int j=coinValue[i];j<=value;j++){ //cache[j]=cache[j]+cache[j-coinValue[i]];
//             cache[j]+=cache[j-coinValue[i]];
//         }
//     }
//     return cache[value];
// }


int solve_re(int value){//end까지 사용해서 value를 만드는 경우의 수는?
    cache[0][0]=cache[1][0]=1;
    for(int i=1;i<coinValue.size();i++){
        for(int j=1;j<=value;j++){
            cache[i%2][j]=cache[(i+1)%2][j];
            if(j>=coinValue[i]) cache[i%2][j]+=cache[i%2][j-coinValue[i]];
        }
    }
    return cache[(coinValue.size()-1)%2][value];
}

int main(){
    int n,value;
    cin >> n >> value;
    coinValue.resize(n+1);
    for(int i=1;i<=n;i++){
        cin >> coinValue[i];
    }
    cout << solve_re(value) <<"\n";
    return 0;
}