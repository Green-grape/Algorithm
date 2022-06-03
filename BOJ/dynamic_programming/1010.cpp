#include <iostream>
#include <string.h>

const int MAX=30;
int cache[MAX+1][MAX+1];

using namespace std;

int binomial(int n, int r){
    if(r==0 || n==r) return 1;
    if(r==1) return n;
    int& ret=cache[n][r];
    if(ret!=-1) return ret;
    return ret=binomial(n-1,r)+binomial(n-1,r-1);
}

int main(){
    int testCase;
    cin >> testCase;
    memset(cache,-1,sizeof(cache));
    for(int i=0;i<testCase;i++){
        int r,n;
        cin >> r >> n;
        cout << binomial(n,r) <<"\n";
    }
    return 0;
}