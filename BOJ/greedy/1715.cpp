/*
소설의 각 장들이 수록되어 있는 파일의 크기가 주어졌을 때, 이 파일들을 하나의 파일로 합칠 때 필요한 최소비용을 계산하는 프로그램을 작성하시오.
이때 비용은 파일 크기의 합이며 한 번에 2개의 파일만을 합칠 수 있다.
*/

#include <stdio.h>
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

long long getMinCostForSum(vector<int>& files){
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for(int i=0;i<files.size();i++) pq.push(files[i]);
    long long cost=0;
    while(pq.size()>1){
        long long c1=pq.top();pq.pop();
        long long c2=pq.top();pq.pop();
        cost+=(c1+c2);
        pq.push(c1+c2);
    }
    return cost;
}

int main(){
    int fileCount;
    scanf("%d", &fileCount);
    vector<int> files(fileCount);
    for(int i=0;i<fileCount;i++) scanf("%d", &files[i]);
    printf("%lld\n", getMinCostForSum(files));
    return 0;
}