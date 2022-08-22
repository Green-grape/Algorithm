/*
숫자(0~9의 범위를 가짐)가 줄 지어있는 것을 보기만 하면, 마지막 두 숫자 사이에 '='을 넣고, 나머지 숫자 사이에는 '+' 또는 '-'를 넣어 등식을 만드는데
0<=중간 과정의 결과<=20을 만족해야한다. 이때 올바른 등식의 경우의 수는?
//복습
*/

#include <iostream>
#include <vector>
#include <string.h>

const int MAXN=100;
const int MAX_SUM=20;

using namespace std;

vector<vector<long long>> cache(MAXN, vector<long long>(MAX_SUM+1,-1));
vector<int> nums;

long long getSumCount(int cur, int sum){ // cur부터 연산하여 값이 nums[nums.size()-1] 되는 경우의 수는? sum은 이전 연산 결과
    if(cur==nums.size()-1) return nums[cur]==sum ? 1:0; 
    long long& ret=cache[cur][sum];
    if(ret!=-1) return ret;
    ret=0;
    if(sum+nums[cur]<=MAX_SUM) ret+=getSumCount(cur+1,sum+nums[cur]);
    if(sum-nums[cur]>=0) ret+=getSumCount(cur+1,sum-nums[cur]);
    return ret;
}

long long solve(){
    return getSumCount(1,nums[0]);
}

int main(){
    int numCount;
    cin >> numCount;
    nums.resize(numCount);
    for(int i=0;i<numCount;i++) cin >> nums[i];
    cout << solve() <<"\n";
    return 0;
}

