/*
수열 A가 주어졌을 때, 가장 긴 증가하는 부분 수열을 구하는 프로그램을 작성하시오.
1<=A의 길이<=1000, 1<=각 원소<=1000
*/

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

const int MAX_LENGTH=1000;

int cache[MAX_LENGTH];
vector<double> arr;
int n;

int maxStrictlyIncreasingArrLength(int start){ //start에서부터 시작하는 가장 긴 증가하는 부분 수열의 길이는?
    if(start==n) return 1;
    int& ret=cache[start];
    if(ret!=-1) return ret;
    ret=1;
    for(int i=start+1;i<=n;i++){
        if(arr[start]<arr[i]) ret=max(ret,1+maxStrictlyIncreasingArrLength(i));
    }
    return ret;
}

int solve(){
    memset(cache,-1,sizeof(cache));
    return maxStrictlyIncreasingArrLength(0)-1;
}

int main(){
    cin >> n;
    arr.resize(n+1);
    arr[0]=-1;
    for(int i=1;i<=n;i++){
        cin >> arr[i];
    }
    cout << solve() <<"\n";
    return 0;
}