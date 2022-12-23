#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long solve(vector<int> front, vector<int> back, int target){
    vector<int> sumFront, sumBack;
    for(int select=1;select<(1<<front.size());select++){
        int sum=0;
        for(int i=0;i<front.size();i++){
            if(select & (1<<i)){
                sum+=front[i];
            }
        }
        sumFront.push_back(sum);
    }
    for(int select=1;select<(1<<back.size());select++){
        int sum=0;
        for(int i=0;i<back.size();i++){
            if(select & (1<<i)){
                sum+=back[i];
            }
        }
        sumBack.push_back(sum);
    }
    sort(sumFront.begin(),sumFront.end());
    sort(sumBack.begin(),sumBack.end());
    vector<pair<int,int>> sumFrontCnt,sumBackCnt;
    if(sumFront.size()>=1) sumFrontCnt.push_back({sumFront[0],1});
    for(int i=1;i<sumFront.size();i++){
        if(sumFront[i]==sumFrontCnt[sumFrontCnt.size()-1].first){
            sumFrontCnt[sumFrontCnt.size()-1].second++;
        }else{
            sumFrontCnt.push_back({sumFront[i],1});
        }
    }
    sumBackCnt.push_back({sumBack[0],1});
    for(int i=1;i<sumBack.size();i++){
        if(sumBack[i]==sumBackCnt[sumBackCnt.size()-1].first){
            sumBackCnt[sumBackCnt.size()-1].second++;
        }else{
            sumBackCnt.push_back({sumBack[i],1});
        }
    }
    long long ret=0;
    for(int i=0;i<sumFrontCnt.size();i++){
        int left=0,right=sumBackCnt.size()-1;
        while(left<=right){
            int mid=(left+right)/2;
            if(sumFrontCnt[i].first+sumBackCnt[mid].first<target) left=mid+1;
            else if(sumFrontCnt[i].first+sumBackCnt[mid].first>target) right=mid-1;
            else{
                ret+=sumFrontCnt[i].second*(long long)sumBackCnt[mid].second;
                break;
            }
        }
    }
    int left=0,right=sumFrontCnt.size()-1;
    while(left<=right){
        int mid=(left+right)/2;
        if(sumFrontCnt[mid].first<target) left=mid+1;
        else if(sumFrontCnt[mid].first>target) right=mid-1;
        else{
            ret+=sumFrontCnt[mid].second;
            break;
        }
    }
    left=0;right=sumBackCnt.size()-1;
    while(left<=right){
        int mid=(left+right)/2;
        if(sumBackCnt[mid].first<target) left=mid+1;
        else if(sumBackCnt[mid].first>target) right=mid-1;
        else{
            ret+=sumBackCnt[mid].second;
            break;
        }
    }
    return ret;
}

int main(){
    int n, target;
    cin >> n >> target;
    vector<int> front(n/2),back(n-n/2);
    for(int i=0;i<n/2;i++){
        scanf("%d", &front[i]);
    }
    for(int i=0;i<n-(n/2);i++){
        scanf("%d", &back[i]);
    }
    cout << solve(front,back,target) <<"\n";
    return 0;
}