#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

#define LL long long int

vector<LL> sums;

//세그먼트 트리 복습

LL init(vector<LL>& nums, int start, int end, int nodeIdx){
    if(start>end) return 0;
    if(start==end){
        sums[nodeIdx]=nums[start];
        return sums[nodeIdx];
    }
    int mid=(start+end)/2;
    return sums[nodeIdx]=init(nums, start,mid, nodeIdx*2)+init(nums,mid+1,end,nodeIdx*2+1);
}

//start, end: 탐색할 전체 구간, numIdx: 변경할 위치
//nodeIdx: 집어 넣을 위치
void update(int start, int end, int nodeIdx, LL dif, int numIdx){
    if(!(start<=numIdx && numIdx<=end)) return;
    sums[nodeIdx]+=dif;
    if(start!=end){
        int mid=(start+end)/2;
        update(start, mid, nodeIdx*2, dif,numIdx);
        update(mid+1,end,nodeIdx*2+1,dif,numIdx);
    }
}


//start, end: 탐색할 전체 구간, left,right: 찾을 구간
LL getSum(int start, int end, int left, int right, int nodeIdx){
    if(start>end || end<left || right<start) return 0;
    if(left<=start && end<=right) return sums[nodeIdx];
    int mid=(start+end)/2;
    return getSum(start, mid, left, right, nodeIdx*2)+getSum(mid+1,end,left,right, nodeIdx*2+1);
};

void printSum(int start, int end, int nodeIdx){
    if(start>end) return;
    int mid=(start+end)/2;
    cout << start <<"~"<<end<<": "<< sums[nodeIdx] <<"\n";
    if(start<end){
        printSum(start, mid,nodeIdx*2);
        printSum(mid+1, end, nodeIdx*2+1);
    }
}

int main(){
    int numCnt, modCnt, sumCnt;
    cin >> numCnt >> modCnt >> sumCnt;
    vector<LL> nums(numCnt+1);
    int h=(int)ceil(log2(numCnt+1));
    sums=vector<LL>(1<<(h+1));
    for(int i=1;i<nums.size();i++){
        scanf("%lld", &nums[i]);
    }
    init(nums, 1, nums.size()-1, 1);
    for(int i=0;i<modCnt+sumCnt;i++){
        int a,b;LL c;
        scanf("%d %d %lld", &a, &b, &c);
        if(a==1){
            LL dif=c-nums[b];
            update(1,nums.size()-1,1,dif,b);
            //printSum(1, nums.size()-1,1);
            nums[b]=c;
        }else if(a==2){
            LL sum=getSum(1,nums.size()-1, b,c,1);
            cout << sum <<"\n";
        }
    }
    return 0;
}