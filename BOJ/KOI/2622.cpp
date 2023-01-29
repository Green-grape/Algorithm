#include <iostream>

using namespace std;

int solve(int n){
    int longestLineMax=(n-1)/2, longestLineMin=(n%3==0) ? n/3:n/3+1;
    int ret=0;
    for(int i=longestLineMax;i>=longestLineMin;i--){
        for(int j=1;j<=i;j++){
            int front=j, back=n-i-j;
            if(back>i) continue;
            if(front>back) break;
            ret++;
        }
    }
    return ret;
}

int main(){
    int n;
    cin >> n;
    cout << solve(n) <<"\n";
    return 0;
}