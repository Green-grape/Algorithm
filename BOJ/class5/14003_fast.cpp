#include <bits/stdc++.h>

using namespace std;

int setLoc(int val, vector<int>& lis){
    if(lis.empty() || lis[lis.size()-1]<val){
        lis.push_back(val);
        return lis.size()-1;
    }
    int idx=lower_bound(lis.begin(),lis.end(),val)-lis.begin();
    lis[idx]=val;
    return idx;
}

vector<int> solve(vector<int>& arr){ 
    vector<int> lis, loc(arr.size()); //loc[i]=arr[i]가 lis에서 가지는 위치
    for(int i=0;i<arr.size();i++){
        loc[i]=setLoc(arr[i],lis);
    }
    int idx=lis.size()-1;
    vector<int> ret;
    for(int i=arr.size()-1;i>=0;i--){
        if(loc[i]==idx){
            ret.push_back(arr[i]);
            idx--;
        }
    }
    reverse(ret.begin(),ret.end());
    return ret;
}

int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }
    vector<int> ret=solve(arr);
    cout << ret.size() <<"\n";
    for(int i=0;i<ret.size();i++){
        cout << ret[i]<<" ";
    }
    return 0;
}
