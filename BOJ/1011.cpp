#include <iostream>
#include <cmath>
//Fly me to the Alpha Centauri

//n회 이동시 최대로 이동량
//n=2k -> k^2+k
//n=2k-1 -> k^2을 이용해서 최소한의 n을 구한다
//k^2-k<dis<=k^2 -> 2k
//k^2<dis<=k^2+k ->2k-1
int solve(int dis){
    int kc=ceil(sqrt(dis));
    int kf=floor(sqrt(dis));
    if(kc!=kf && dis<=kf*kf+kf) return 2*kf;
    return 2*kc-1;
}

int main(){
    int testCase;
    std::cin >> testCase;
    while(testCase--){
        int x,y;
        std::cin >> x >> y;
        int dis=y-x;
        std::cout << solve(dis) <<"\n";
    }
    return 0;
}