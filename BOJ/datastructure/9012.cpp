#include <iostream>
#include <queue>

using namespace std;

int solve(string ps){
    queue<int> q;
    for(int i=0;i<ps.length();i++){
        if(ps[i]=='(') q.push(1);
        else{
            if(q.empty()) return 0;
            q.pop();
        } 
    }
    return q.empty();
}

int main(){
    int testCase;
    cin >> testCase;
    while(testCase--){
        string ps;
        cin >> ps; //괄호 문자열
        if(solve(ps)) cout <<"YES"<<"\n";
        else cout <<"NO"<<"\n";
    }
    return 0;
}