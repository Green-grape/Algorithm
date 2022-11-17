#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

vector<int> a,b;
vector<long long> sumA,sumB; //sumA[i]=0~i까지의 합
vector<pair<long long,int>> sumsA,sumsB; //sumsA=a의 모든 부배별의 합들

long long getSubsumA(int start, int end){
    if(start==end) return a[end];
    return sumA[end]-sumA[start]+a[start];
}

long long getSubsumB(int start, int end){
    if(start==end) return b[end];
    return sumB[end]-sumB[start]+b[start];
}

void precal(){
    sumA.resize(a.size());sumB.resize(b.size());
    sumA[0]=a[0];sumB[0]=b[0];
    for(int i=1;i<a.size();i++) sumA[i]=sumA[i-1]+a[i];
    for(int i=1;i<b.size();i++) sumB[i]=sumB[i-1]+b[i];
    vector<long long> tempSums;
    for(int i=0;i<a.size();i++){
        for(int j=i;j<a.size();j++){
            tempSums.push_back(getSubsumA(i,j));
        }
    }
    sort(tempSums.begin(),tempSums.end());
    sumsA.push_back({tempSums[0],1});
    for(int i=1;i<tempSums.size();i++){
        if(tempSums[i]==sumsA[sumsA.size()-1].first){
            sumsA[sumsA.size()-1].second++;
        }else{
            sumsA.push_back({tempSums[i],1});
        }
    }
    tempSums.resize(0);
    for(int i=0;i<b.size();i++){
        for(int j=i;j<b.size();j++){
            tempSums.push_back(getSubsumB(i,j));
        }
    }
    sort(tempSums.begin(),tempSums.end());
    sumsB.push_back({tempSums[0],1});
    for(int i=1;i<tempSums.size();i++){
        if(tempSums[i]==sumsB[sumsB.size()-1].first){
            sumsB[sumsB.size()-1].second++;
        }else{
            sumsB.push_back({tempSums[i],1});
        }
    }
    // for(int i=0;i<sumsA.size();i++){
    //     cout << sumsA[i].first << "cnt: " <<sumsA[i].second <<"\n";
    // }
    // for(int i=0;i<sumsB.size();i++){
    //     cout << sumsB[i].first << "cnt: " <<sumsB[i].second <<"\n";
    // }
}

long long solve(int target){
    precal();
    long long ret=0;
    for(int i=0;i<sumsA.size();i++){
        long long curTarget=(long long)target-sumsA[i].first;
        int left=0,right=sumsB.size()-1;
        int mid;
        bool isFind=false;
        while(left<=right){
            mid=(left+right)/2;
            if(sumsB[mid].first>curTarget) right=mid-1;
            else if(sumsB[mid].first<curTarget) left=mid+1;
            else {
                isFind=true;
                break;
            }
        }
        if(isFind){
            ret+=sumsA[i].second*(long long)sumsB[mid].second;
        }
    }
    return ret;
}

int main(){
    int target, aSize, bSize;
    cin >> target;
    cin >> aSize;
    a.resize(aSize);
    for(int i=0;i<aSize;i++){
        scanf("%d", &a[i]);
    }
    cin >> bSize;
    b.resize(bSize);
    for(int i=0;i<bSize;i++){
        scanf("%d", &b[i]);
    }
    cout << solve(target) <<"\n";
    return 0;
}