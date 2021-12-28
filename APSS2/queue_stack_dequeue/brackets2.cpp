#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isWellMatchedBrackets(string s);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        string str;
        cin >> str;
        if(isWellMatchedBrackets(str)) cout <<"YES\n";
        else cout <<"NO\n";
    }
    return 0;
}

bool isWellMatchedBrackets(string s){
    string openBrackets("({["), endBrakets(")}]");  
    stack<char> openBracketStack;
    for(int i=0;i<s.length();i++){
        if(openBrackets.find(s[i])!=-1){
            openBracketStack.push(s[i]);
        }
        else{
            if(openBracketStack.empty()) return false;
            else if(openBrackets.find(openBracketStack.top())!=endBrakets.find(s[i])){
                return false;
            }
            openBracketStack.pop();
        }
    }
    return openBracketStack.empty();
}