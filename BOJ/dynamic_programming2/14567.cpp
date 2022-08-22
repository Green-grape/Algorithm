/*
선수과목 조건을 지킬 경우 각각의 전공과목을 언제 이수할 수 있는지 각각 출력하라 편의를 위해서 다음과 같은 조건이 주어진다.
1.한 학기에 들을 수 있는 과목 수에는 제한이 없다.
2.모든 과목은 매 학기 항상 개설된다.
*/

#include <iostream>
#include <vector>

using namespace std;

const int MAX_PRE=500000;

vector<vector<int>> pre; //pre[i]=i번째 과목의 선수 과목 목록
vector<int> cache(MAX_PRE+1,-1);

int preSemeter(int i){ //i번째 과목을 듣기위해서 들어야하는 학기의 수
    if(pre[i].size()==0) return 1;
    int& ret=cache[i];
    if(ret!=-1) return ret;
    ret=1;
    for(int j=0;j<pre[i].size();j++){
        ret=max(ret,1+preSemeter(pre[i][j]));
    }
    return ret;
}

vector<int> solve(){
    vector<int> ret;
    for(int i=0;i<pre.size();i++){
        ret.push_back(preSemeter(i));
    }
    return ret;
}

int main(){
    int subjectCount, preCount;
    cin >> subjectCount >> preCount;
    pre.resize(subjectCount);
    for(int i=0;i<preCount;i++){
        int preSubject, subject;
        cin >> preSubject >> subject;
        pre[subject-1].push_back(preSubject-1);
    }
    vector<int> ret=solve();
    for(int i=0;i<ret.size();i++) cout << ret[i] <<" ";
    return 0;
}

