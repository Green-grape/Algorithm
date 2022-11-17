#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

pair<int,int> solve(vector<int>& arr){
    sort(arr.begin(), arr.end());
    //모두 양, 음 일때 처리
    if(0<=arr[0] && 0<=arr[1]) return {arr[0],arr[1]};
    if(arr[arr.size()-2]<=0 && arr[arr.size()-1]<=0) return {arr[arr.size()-2],arr[arr.size()-1]};
    
    pair<int,int> ret;
    int retValue=INT32_MAX;
    for(int i=0;i<arr.size()-1;i++){
        int target=-arr[i];
        int left=i+1,right=arr.size()-1;
        int mid;
        while(left<=right){
            mid=(left+right)/2;
            if(arr[mid]>target) right=mid-1;
            if(arr[mid]<target) left=mid+1;
            if(arr[mid]==target) break;
        }
        int cand=mid, temp=arr[i]+arr[mid];
        if(mid+1<=arr.size()-1 && abs(temp)>abs(arr[i]+arr[mid+1])){
            cand=mid+1;
            temp=arr[i]+arr[mid+1];
        }
        if(i+1<=mid-1 && abs(temp)>abs(arr[i]+arr[mid-1])){
            cand=mid-1;
            temp=arr[i]+arr[mid-1];
        }
        if(abs(temp)<retValue){
            retValue=abs(temp);
            ret.first=arr[i];
            ret.second=arr[cand];
        }
    }
    return ret;
}

int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }
    pair<int,int> ret=solve(arr);
    cout << ret.first << " "<<ret.second<<"\n";
    return 0;
}