#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;

vector<string> parseInput(string input){
    vector<string> ret;
    string cur="";
    for(int i=1;i<input.size()-1;i++){
        if(input[i]!=',') cur+=input[i];
        else{
            ret.push_back(cur);
            cur="";
        }
    }
    if(cur.size()!=0) ret.push_back(cur);
    return ret;
}

//reverse는 O(n)임을 주의하자 

deque<string> solve(const string op, const vector<string>& parsedInput){
    deque<string> ret;
    for(int i=0;i<parsedInput.size();i++){
        ret.push_back(parsedInput[i]);
    }
    bool isReverse=false;
    for(int i=0;i<op.size();i++){
        if(op[i]=='R'){
            isReverse=!isReverse;
        }
        else if(op[i]=='D'){
            if(ret.size()==0) return deque<string>(1,"error");
            if(isReverse) ret.pop_back();
            else ret.pop_front();
        }
    }
    if(isReverse) reverse(ret.begin(),ret.end());
    return ret;
}

string formating(deque<string> parsed){
    string ret="[";
    ret.reserve(parsed.size()*6+2);
    for(int i=0;i<parsed.size();i++){
        ret+=parsed[i];
        if(i!=parsed.size()-1){
            ret+=',';
        }
    }
    ret+="]";
    return ret;
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        string op, input;
        cin >> op;
        int numCount;
        cin >> numCount >> input;
        vector<string> parsedInput=parseInput(input);
        deque<string> ret=solve(op, parsedInput);
        if(ret.size()!=0 && ret[0].compare("error")==0) cout << "error" <<"\n";
        else{
            cout << formating(ret) <<"\n";
        }
    }
    return 0;
}