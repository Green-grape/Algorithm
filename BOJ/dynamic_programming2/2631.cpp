/*
N개의 숫자가 주어질때 숫자들간의 교환으로 오름차순 정렬을 하려면 최소한 몇번을 옮겨야하는가? (2<=N<=200)
//LIS!!
*/

#include <iostream>
#include <vector>
#include <cmath>

const int MAXN=200;

using namespace std;

vector<int> nums;
vector<int> cache(MAXN,-1);

int lisFrom(int start){
    if(start==nums.size()-1) return 1;
    int& ret=cache[start];
    if(ret!=-1) return ret;
    ret=1;
    for(int i=start+1;i<nums.size();i++){
        if(nums[start]<nums[i]) ret=max(ret,1+lisFrom(i));
    }
    return ret;
}

int solve(){
    int lis=1;
    for(int i=0;i<nums.size();i++) lis=max(lis,lisFrom(i));
    return nums.size()-lis;
}

int main(){
    int n;
    cin >> n;
    nums.resize(n);
    for(int i=0;i<n;i++) cin >> nums[i];
    cout << solve() <<"\n";
    return 0;
}