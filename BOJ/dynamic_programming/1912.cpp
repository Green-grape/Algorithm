/*
n개의 정수로 이루어진 임의의 수열이 주어진다. 우리는 이 중 연속된 몇 개의 수를 선택해서 구할 수 있는 합 중 가장 큰 합을 구하려고 한다. 단, 수는 한 개 이상 선택해야 한다.
1<=n<=100000, -1000<=정수<=1000
*/ 

#include <stdio.h>
#include <vector>
#include <string.h>

using namespace std;

const int INF=987654321;
const int MAX_LENGTH=100000;
vector<int> arr;

//kadane's algorithm
int solve(){
    int ret=arr[0];
    int tempRet=arr[0];
    for(int i=1;i<arr.size();i++){
        tempRet=max(arr[i],arr[i]+tempRet);
        if(tempRet>ret){
            ret=tempRet;
        }
    }
    return ret;
}

vector<int> cache(MAX_LENGTH+1);

int maxSuccessiveSum(int end){
    if(end==0) return arr[0];
    int& ret=cache[end];
    if(ret!=-INF) return ret;
    ret=max(arr[end],arr[end]+maxSuccessiveSum(end-1));
    return ret;
}

int solve_dp(){
    fill(cache.begin(), cache.end(), -INF);
    int ret=-INF;
    for(int i=arr.size()-1;i>=0;i--){
        ret=max(ret,maxSuccessiveSum(i));
    }
    return ret;
}

int main(){
    int n;
    scanf("%d", &n);
    arr.resize(n);
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }
    printf("%d\n", solve_dp());
    return 0;
}