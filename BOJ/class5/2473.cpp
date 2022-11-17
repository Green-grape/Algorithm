#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> solve(vector<int> solutions){
    sort(solutions.begin(),solutions.end());
    if(solutions[solutions.size()-1]<=0) return vector<int>(solutions.begin()+solutions.size()-3,solutions.end());
    if(solutions[0]>=0) return vector<int>(solutions.begin(), solutions.begin()+3);
    int ret=INT32_MAX;
    vector<int> retV;
    for(int i=0;i<solutions.size()-2;i++){
        for(int j=i+1;j<solutions.size()-1;j++){
            int target=(solutions[i]+solutions[j])*-1;
            int left=j+1,right=solutions.size()-1;
            int mid;
            while(left<=right){
                mid=(left+right)/2;
                if(target<solutions[mid]) right=mid-1;
                else if(target>solutions[mid]) left=mid+1;
                else break;
            }
            int temp=solutions[mid]-target;
            int cand=-1;
            if(ret>abs(temp)){
                ret=abs(temp);
                cand=mid;
            }
            if(j+1<=mid-1 && ret>abs(solutions[mid-1]-target)){
                ret=abs(solutions[mid-1]-target);
                cand=mid-1;
            }
            if(mid+1<=solutions.size()-1 && ret>abs(solutions[mid+1]-target)){
                ret=abs(solutions[mid+1]-target);
                cand=mid+1;
            }
            if(cand!=-1){
                retV={solutions[i],solutions[j],solutions[cand]};
            }
        }
    }
    return retV;
}

int main(){
    int n;
    cin >> n;
    vector<int> solutions(n);
    for(int i=0;i<n;i++){
        scanf("%d", &solutions[i]);
    }
    vector<int> ret=solve(solutions);
    for(int i=0;i<ret.size();i++){
        cout << ret[i] <<" ";
    }
    return 0;
}