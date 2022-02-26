/*
주어진 순열은 어차피 순서만 비교하면 되므로 정규화 시키고
정규화된 배열이 가질수 있는 모든 순열에 대해서 미리 거리를 구해놓는 방법을 사용한다
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

int getMinReverseToSort(const vector<int>);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int arrLength;
        cin >> arrLength;
        vector<int> arr;
        for(int j=0;j<arrLength;j++){
            int num;
            cin >> num;
            arr.push_back(num);
        }
        cout << getMinReverseToSort(arr) <<"\n";
    }
    return 0;
}

//[0,n-1]로부터 가능한 모든 순열까지의 뒤집기 횟수를 미리 계산
//최악 8!*8^2
map<vector<int>,int> getPreCalMinCost(int n){
    map<vector<int>, int> ret;
    vector<int> perm(n);
    for(int i=0;i<n;i++) perm[i]=i;
    queue<vector<int>> q;
    q.push(perm);
    ret[perm]=0;
    while(!q.empty()){
        vector<int> cur=q.front();
        q.pop();
        int cost=ret[cur];
        for(int i=0;i<n;i++){
            for(int j=i+2;j<=n;j++){
                reverse(cur.begin()+i,cur.begin()+j);
                if(ret.count(cur)==0){
                    ret[cur]=cost+1;
                    q.push(cur);
                }
                reverse(cur.begin()+i,cur.begin()+j);
            }
        }
    }
    return ret;
}

int getMinReverseToSort(const vector<int> arr){
    int n=arr.size();
    map<vector<int>,int> minCost=getPreCalMinCost(n);
    //arr을 [0,n-1]순열로 변환한다.
    vector<int> normalize(n);
    for(int i=0;i<n;i++){
        int smallers=0;
        for(int j=0;j<n;j++){
            if(arr[j]<arr[i]) smallers++;
        }
        normalize[i]=smallers;
    }
    return minCost[normalize];
}