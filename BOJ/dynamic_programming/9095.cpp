#include <iostream>
#include <string.h>

const int MAX=10;
int cache[MAX+1];

using namespace std;

int sum123(int n){ //n을 1,2,3의 합으로 나타내는 방법의 수
    if(n==1) return 1;
    if(n==2) return 2;
    if(n==3) return 4;
    int& ret=cache[n];
    if(ret!=-1) return ret;
    return ret=sum123(n-1)+sum123(n-2)+sum123(n-3);
}

int main(){
    int testCase;
    cin >> testCase;
    memset(cache,-1,sizeof(cache));
    for(int i=0;i<testCase;i++){
        int n;
        cin >> n;
        cout << sum123(n) << "\n";
    }
    return 0;
}