#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void solve(vector<long long>& lines, long long needCount){
    long long left=1,right=INT32_MAX,ret=0;
    while(left<=right){
        long long mid=(left+right)/2;
        long long cand=0;
        for(int i=0;i<lines.size();i++){
            cand+=(lines[i]/mid);
        }
        if(cand>=needCount){ //값 계속 갱신
            left=mid+1;
            ret=mid;
        }else if(cand<needCount){
            right=mid-1;
            ret=mid-1;
        }
    }
    cout << ret <<"\n";
}

int main(){
    int lineCount, needCount;
    cin >> lineCount >> needCount;
    vector<long long> lines(lineCount);
    for(int i=0;i<lineCount;i++){
        scanf("%lld", &lines[i]);
    }
    solve(lines, needCount);
    return 0;
}