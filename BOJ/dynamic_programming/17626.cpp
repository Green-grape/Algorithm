#include <iostream>
#include <string.h>
#include <cmath>

const int MAX=50000;
int cache[MAX+1];

using namespace std;

int minSquare(int n){//n이 최소 몇개의 제곱수 합꼴로 표현되는가?
    if(n==pow((int)sqrt(n),2)) return 1;
    int& ret=cache[n];
    if(ret!=-1) return ret;
    ret=5; //4개 이하라는게 이미 증명됨
    for(int i=1;i*i<=n;i++){
        ret=min(ret,1+minSquare(n-i*i));
    }
    return ret;
}

int main(){
    int n;
    cin >> n;
    memset(cache,-1,sizeof(cache));
    cout << minSquare(n) <<"\n";
    return 0;
}