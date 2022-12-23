#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool isWellPaired(string brakets){
    string opens="({[",closes=")}]";
    stack<char> s;
    for(int i=0;i<brakets.size();i++){
        if(opens.find(brakets[i])!=-1){ //여는 괄호
            s.push(brakets[i]);
        }else if(closes.find(brakets[i])!=-1){ //닫는 괄호
            if(s.empty()) return false;
            if(opens[closes.find(brakets[i])]==s.top()){
                s.pop();
            }else return false;
        }
    }
    return s.empty();
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        string brackets;
        cin >> brackets;
        if(isWellPaired(brackets)) cout <<"YES"<<"\n";
        else cout <<"NO"<<"\n";
    }
    return 0;
}

























// #include <iostream>
// #include <string>
// #include <stack>

// using namespace std;

// bool isWellMatchedBrackets(string s);

// int main(){
//     int testCase;
//     cin >> testCase;
//     for(int i=0;i<testCase;i++){
//         string str;
//         cin >> str;
//         if(isWellMatchedBrackets(str)) cout <<"YES\n";
//         else cout <<"NO\n";
//     }
//     return 0;
// }

// bool isWellMatchedBrackets(string s){
//     string openBrackets("({["), endBrakets(")}]");  
//     stack<char> openBracketStack;
//     for(int i=0;i<s.length();i++){
//         if(openBrackets.find(s[i])!=-1){
//             openBracketStack.push(s[i]);
//         }
//         else{
//             if(openBracketStack.empty()) return false;
//             else if(openBrackets.find(openBracketStack.top())!=endBrakets.find(s[i])){
//                 return false;
//             }
//             openBracketStack.pop();
//         }
//     }
//     return openBracketStack.empty();
// }