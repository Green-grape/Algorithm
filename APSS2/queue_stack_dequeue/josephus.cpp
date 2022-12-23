#include <iostream>
#include <queue>
#include <vector>

using namespace std;

pair<int,int> getRemainTwo(int totalCnt, int nth){
    queue<int> q;
    for(int i=1;i<=totalCnt;i++) q.push(i);
    q.pop();
    while(q.size()>2){
        for(int i=0;i<nth-1;i++){
            int cur=q.front();
            q.pop();
            q.push(cur);
        }
        q.pop();
    }
    return {q.front(), q.back()};
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        int totalCnt, nth;
        cin >>  totalCnt >> nth;
        pair<int,int> ret=getRemainTwo(totalCnt, nth);
        cout << ret.first<<" "<<ret.second<<"\n";
    }
    return 0;
}