#include <iostream>
#include <queue>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

#define LL long long int

vector<LL> maxTree, minTree;

void init(vector<LL>& nums, int start, int end, int treeIdx){
    if(start>end) return;
    if(start==end){
        minTree[treeIdx]=maxTree[treeIdx]=nums[start];
        return;
    }
    int mid=(start+end)/2;
    init(nums,start,mid, treeIdx*2);
    init(nums,mid+1,end,treeIdx*2+1);
    maxTree[treeIdx]=max(maxTree[treeIdx*2], maxTree[treeIdx*2+1]);
    minTree[treeIdx]=min(minTree[treeIdx*2], minTree[treeIdx*2+1]);
}

LL getMax(int start, int end, int treeIdx, int left, int right){
    if(start>end || end<left || right<start) return -1;
    if(left<=start && end<=right) return maxTree[treeIdx];
    if(start!=end){
        int mid=(start+end)/2;
        LL ret=max(getMax(start, mid, treeIdx*2, left, right),getMax(mid+1,end, treeIdx*2+1, left,right));
        return ret;
    }
    return -1;
}

LL getMin(int start, int end, int treeIdx, int left, int right){
    if(start>end || end<left || right<start) return __LONG_LONG_MAX__;
    if(left<=start && end<=right) return minTree[treeIdx];
    if(start!=end){
        int mid=(start+end)/2;
        LL ret=min(getMin(start, mid, treeIdx*2, left, right),getMin(mid+1,end, treeIdx*2+1, left,right));
        return ret;
    }
    return __LONG_LONG_MAX__;
}

int main(){
    int nodeCnt, pairCnt;
    cin >> nodeCnt >> pairCnt;
    int h=((int)log2(nodeCnt+1))+1;
    maxTree=vector<LL>(1<<(h+1));
    minTree=vector<LL>(1<<(h+1));
    vector<LL> nums(nodeCnt+1);
    for(int i=1;i<nums.size();i++){
        scanf("%lld", &nums[i]);
    }
    init(nums, 1, nums.size()-1, 1);
    for(int i=0;i<pairCnt;i++){
        int start, end;
        scanf("%d %d", &start, &end);
        LL maxN=getMax(1,nums.size()-1,1,start, end);
        LL minN=getMin(1,nums.size()-1,1,start,end);
        printf("%lld %lld\n", minN, maxN);
    }
    return 0;
}