#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include "string.h"

#define MAX_ARR_LENGTH 101

using namespace std;

long long numMin=numeric_limits<long long>::min();
int cache[MAX_ARR_LENGTH][MAX_ARR_LENGTH];
int jlis(vector<int>&, vector<int>&);
int jlisSolution(vector<int>&, vector<int>&, int, int);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        vector<int> arr1, arr2;
        int arr1Length, arr2Length,temp;
        cin >> arr1Length >> arr2Length;
        for(int j=0;j<arr1Length;j++){
            cin >> temp;
            arr1.push_back(temp);
        }
        for(int j=0;j<arr2Length;j++){
            cin >> temp;
            arr2.push_back(temp);
        }
        memset(cache, -1, sizeof(cache));
        int ret=jlis(arr1,arr2);
        cout << ret <<"\n";
    }
}

int jlis(vector<int>& arr1, vector<int>& arr2){
    int ret=0;
    int arr1Length=arr1.size();
    int arr2Length=arr2.size();
    for(int i=-1;i<arr1Length;i++){
        for(int j=-1;j<arr2Length;j++){
            ret=max(ret,jlisSolution(arr1,arr2,i,j));
        }
    }
    return ret;
}

// arr1[arr1Index], arr2[arr2Index]부터 시작하는 joined lis의 길이를 반환
// arr1[-1], arr2[-1]은 arr1,arr2의 길이가 0인 경우를 고려한다.
int jlisSolution(vector<int>& arr1, vector<int>& arr2, int arr1Index, int arr2Index){
    int& ret=cache[arr1Index+1][arr2Index+1];
    if(ret!=-1) return ret;
    ret=0;
    long long a=(arr1Index==-1) ? numMin:arr1[arr1Index];
    long long b=(arr2Index==-1) ? numMin:arr2[arr2Index];
    long long maxElement=max(a,b);
    for(int i=arr1Index+1;i<arr1.size();i++){
        if(maxElement<arr1[i]) ret=max(ret, 1+jlisSolution(arr1,arr2,i,arr2Index));
    }
    for(int i=arr2Index+1;i<arr2.size();i++){
        if(maxElement<arr2[i]) ret=max(ret, 1+jlisSolution(arr1,arr2,arr1Index,i));
    }
    return ret;
}