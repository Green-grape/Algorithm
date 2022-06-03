/*수열 A가 주어졌을 때, 그 수열의 증가 부분 수열 중에서 합이 가장 큰 것을 구하는 프로그램을 작성하시오.
A의 크기 N (1 ≤ N ≤ 1,000), (1 ≤ Ai ≤ 1,000)
*/

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

const int MAX_LENGTH=1000;

int cache[MAX_LENGTH+1];
vector<int> arr;
int n;

int maxStrictlyIncreasingArrSum(int start){ //start에서부터 시작하는 증가하는 부분 수열의 최대합은?
    if(start==n-1) return arr[start];
    int& ret=cache[start];
    if(ret!=-1) return ret;
    ret=arr[start];
    for(int i=start+1;i<n;i++){
        if(arr[start]<arr[i]) ret=max(ret,arr[start]+maxStrictlyIncreasingArrSum(i));
    }
    return ret;
}

int solve(){
    memset(cache,-1,sizeof(cache));
    int ret=0;
    for(int i=0;i<arr.size();i++){
        ret=max(ret,maxStrictlyIncreasingArrSum(i));
    }
    return ret;
}

int main(){
    cin >> n;
    arr.resize(n);
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    cout << solve() <<"\n";
    return 0;
}