#include <iostream>
#include <vector>

using namespace std;

//arr[0]=n, 1<=arr[1]<=n인 양의 정수, arr[i]=arr[i-2]-arr[i]이고 arr[i]>=0임을 만족해야한다.
//이때 arr의 최대길이는?
vector<int> getMaxArr(int n){
    vector<int> ret;
    for(int i=0;i<=n;i++){
        vector<int> cand(1,n);
        cand.push_back(i);
        while(true){
            int next=cand[cand.size()-2]-cand[cand.size()-1];
            if(next<0) break;
            cand.push_back(next);
        }
        if(ret.size()<cand.size()) ret=cand;
    }
    return ret;
}

int main(){
    int n;
    cin >> n;
    vector<int> ret=getMaxArr(n);
    cout << ret.size() <<"\n";
    for(int i=0;i<ret.size();i++){
        cout << ret[i]<<" ";
    }
    cout <<"\n";
    return 0;
}