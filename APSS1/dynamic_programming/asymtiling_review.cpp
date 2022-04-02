#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int MAX_LENGTH=100;
const int MOD=1000000007;
int tilingMethod[MAX_LENGTH+1];

int asymetricTilingMethodCount(int n);
void init();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int n;
        cin >> n;
        init();
        cout << asymetricTilingMethodCount(n) <<"\n";
    }
    return 0;
}

void init(){
    memset(tilingMethod,-1,sizeof(tilingMethod));
}

int tilingMethodCount(int n){
    if(n<=1) return 1;
    if(n==2) return 2;
    int& ret=tilingMethod[n];
    if(ret!=-1) return ret;
    ret=(tilingMethodCount(n-1)+tilingMethodCount(n-2))%MOD;
    return ret;
}

//MOD하면 n이 크다고 항상큰것은 아니다라는 것 주의
int asymetricTilingMethodCount(int n){
    int ret=(tilingMethodCount(n)-tilingMethodCount(n/2)+MOD)%MOD;
    if(n%2==0) ret=(ret-tilingMethodCount(n/2-1)+MOD)%MOD;
    return ret;
}