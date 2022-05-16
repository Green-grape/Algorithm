#include <queue>
#include <iostream>
#include <vector>

using namespace std;

const int MAX_IMPORTANCE=9;

vector<int> importances; //importances[i]=중요도가 i인 doc의 개수
queue<pair<int,int>> docs;

int solve(int nth);

int main(){
    int testCase;
    cin >> testCase;
    while(testCase--){
        int docCount, nth;
        cin >> docCount >> nth;
        importances.resize(MAX_IMPORTANCE+1);
        for(int i=0;i<docCount;i++){
            int importance;
            cin >> importance;
            docs.push(make_pair(i,importance));
            importances[importance]++;
        }
        cout << solve(nth) <<"\n";
        importances.resize(0);
        queue<pair<int,int>> empty;
        docs.swap(empty);
    }
    return 0;
}

bool isCanPrint(int importance){
    for(int i=importance+1;i<=MAX_IMPORTANCE;i++){
        if(importances[i]!=0) return false;
    }
    return true;
}

int solve(int nth){
    int count=1;
    while(true){
        pair<int,int> doc=docs.front();
        if(isCanPrint(doc.second)){
            docs.pop();
            importances[doc.second]--;
            if(doc.first==nth) return count;
            count++;
        }else{
            docs.pop();
            docs.push(doc);
        }
    }
    return -1;
}