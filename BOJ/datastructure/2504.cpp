/*
‘()’ 인 괄호열의 값은 2이다.
‘[]’ 인 괄호열의 값은 3이다.
‘(X)’ 의 괄호값은 2*값(X) 으로 계산된다.
‘[X]’ 의 괄호값은 3*값(X) 으로 계산된다.
올바른 괄호열 X와 Y가 결합된 XY의 괄호값은 값(XY)= 값(X)+값(Y) 로 계산된다.
*/
#include <string>
#include <stack>
#include <iostream>

using namespace std;

int calString(string brakets){
    stack<char> s;
    for(int i=brakets.length()-1;i>=0;i--) s.push(brakets[i]);
    int ret=0;
    double temp=1;
    while(!s.empty()){
        char top=s.top();
        s.pop();
        if(top=='('){
            if(s.empty() || s.top()==']') return 0;
            if(s.top()==')'){
                ret=ret+2*temp;
                s.pop();
            }else{
                temp*=2;
            }
        }
        else if(top==')'){
            temp/=2;
        }
        if(top=='['){
            if(s.empty() || s.top()==')') return 0;
            if(s.top()==']'){
                ret=ret+3*temp;
                s.pop();
            }else{
                temp*=3;
            }
        }
        else if(top==']'){
            temp/=3;
        }
    }
    if(temp!=1) return 0;
    return ret;
}

int main(){
    string brakets;
    cin >> brakets;
    cout << calString(brakets) <<"\n";
    return 0;
}