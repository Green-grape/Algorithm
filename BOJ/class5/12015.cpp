#include <iostream>
#include <vector>

using namespace std;

//이분 탐색은 항상 양쪽을 생각하자

int lcs(vector<int>& arr){
    vector<int> ret;
    ret.reserve(arr.size());
    ret.push_back(arr[0]);
    for(int i=1;i<arr.size();i++){
        if(ret[ret.size()-1]<arr[i]){
            ret.push_back(arr[i]);
        }else if(ret[ret.size()-1]>arr[i]){
            int left=0,right=ret.size()-1;
            int mid;
            while(left<=right){
                mid=(left+right)/2;
                if(ret[mid]>arr[i]) right=mid-1;
                else if(ret[mid]<arr[i]) left=mid+1;
                else break;
            }
            int cand=mid;
            if(mid+1<ret.size() && ret[mid]<arr[i] && arr[i]<=ret[mid+1]){
                cand=mid+1;
            }
            ret[cand]=arr[i];
        }
        // for(int j=0;j<ret.size();j++){
        //     cout << ret[j] <<" ";
        // }
        // cout << "\n";
    }
    return ret.size();
}

int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }
    cout << lcs(arr) <<"\n";
    return 0;
}