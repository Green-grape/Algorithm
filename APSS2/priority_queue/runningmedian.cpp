#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX_ARR_LENGTH 200000
#define START 1983
#define MOD 20090711

using namespace std;

struct RandomGenerator{
    int seed, a,b;
    RandomGenerator(int _a,int _b):a(_a),b(_b),seed(START){}
    int next(){
       int ret=seed;
       seed=((seed*(long long)a)+b)%MOD;
       return ret;
    }
};

int getTotalRunningMedian(int,int,int);

int main(){
    int testCase;
    vector<int> results;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int arrLength, a,b;
        cin >> arrLength >> a >>b;
        int res=getTotalRunningMedian(arrLength,a,b);
        results.push_back(res);
    }
    for(int i=0;i<results.size();i++){
        cout << results[i]<<"\n";
    }
    return 0;
}

int getTotalRunningMedian(int arrLength,int a,int b){
    priority_queue<int,vector<nt>,less<int>> maxHeap;
    priority_queue<int,vector<int>, greater<int>> minHeap;
    RandomGenerator* rg=new RandomGenerator(a,b);

    int ret=0;
    //maxHeap.top()<=minHeap.top()
    //maxHeap.size()==minHeap.size() or minHeap.size()+1
    for(int i=0;i<arrLength;i++){
        if(maxHeap.size()==minHeap.size()) maxHeap.push(rg->next());
        else minHeap.push(rg->next());
        if(!maxHeap.empty() && !minHeap.empty() && maxHeap.top()>minHeap.top()){
            int a=maxHeap.top(),b=minHeap.top();
            maxHeap.pop();maxHeap.push(b);
            minHeap.pop();minHeap.push(a);
        }
        int median=maxHeap.top();
        ret=(ret+median)%MOD;
    }
    //release
    delete rg;
    return ret;
}