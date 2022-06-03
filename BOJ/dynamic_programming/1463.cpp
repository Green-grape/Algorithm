#include <iostream>
#include <string.h>

const int MAX=1e6;
int cache[MAX+1];

using namespace std;

int minCal(int n){
    if(n==1) return 0;
    int& ret=cache[n];
    if(ret!=-1) return ret;
    ret=1+minCal(n-1);
    if(n%2==0) ret=min(ret,1+minCal(n/2));
    if(n%3==0) ret=min(ret,1+minCal(n/3));
    return ret;
}

int main(){
    int n;
    cin >> n;
    memset(cache,-1,sizeof(cache));
    cout << minCal(n) <<"\n";
}