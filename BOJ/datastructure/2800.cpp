#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;
int openCount=0,closedCount=0;;
vector<pair<int,int>> brackets;

vector<string> possibleFomulas(string formula){//formula에서 괄호를 제거해서 나올수 있는 모든 수식 반환
    vector<string> ret;
    int maxIter=pow(2,brackets.size());//비트마스크를 이용한 집합 순회
    for(int i=1;i<maxIter;i++){
        string f="";
        vector<int> remove(formula.length());
        for(int j=0;j<brackets.size();j++){ //해당 괄호는 제거
            if(i & (1<<j)){
                remove[brackets[j].first]=1;
                remove[brackets[j].second]=1;
            }
        }
        for(int j=0;j<formula.length();j++){
            if(!remove[j]) f+=formula[j];
        }
        ret.push_back(f);
    }
    return ret;
}


int main(){
    string formula;
    cin >> formula;
    int n=formula.length();
    stack<int> s;
    for(int i=0;i<n;i++){
        if(formula[i]=='('){
            s.push(i);
        }
        else if(formula[i]==')'){
            brackets.push_back(make_pair(s.top(),i));
            s.pop();
        }
    }
    vector<string> ret=possibleFomulas(formula);
    sort(ret.begin(),ret.end());
    ret.erase(unique(ret.begin(),ret.end()),ret.end());
    for(int i=0;i<ret.size();i++){
        cout << ret[i] <<"\n";
    }
    return 0;
}