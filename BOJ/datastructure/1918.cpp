/*중위 표기식를 후위 표기식으로 변경하시오*/
/*
입력
첫째 줄에 중위 표기식이 주어진다. 
단 이 수식의 피연산자는 알파벳 대문자로 이루어지며 수식에서 한 번씩만 등장한다. 
그리고 -A+B와 같이 -가 가장 앞에 오거나 AB와 같이 *가 생략되는 등의 수식은 주어지지 않는다. 
표기식은 알파벳 대문자와 +, -, *, /, (, )로만 이루어져 있으며, 길이는 100을 넘지 않는다. 
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

int operaterPriority(char op){
    int ret;
    switch (op)
    {
    case '*':
    case '/':
        ret=2;
        break;
    case '+':
    case '-':
        ret=1;
        break;
    default:
        ret=0;
    }
    return ret;
}

//op1의 우선순위가 더 큰가?
bool isFirst(char op1, char op2){
    return operaterPriority(op1)>operaterPriority(op2);
}

string infixToPostfix(string infix){
    stack<char> s;
    string ret="";
    for(int i=0;i<infix.length();i++){
        if(0<=infix[i]-'A' && infix[i]-'A'<=25){
            ret+=infix[i];
        }
        else{
            if(s.empty() || infix[i]=='(' || isFirst(infix[i], s.top())){
                s.push(infix[i]);
            }else if(infix[i]==')'){
                while(!s.empty() && s.top()!='('){
                    ret+=s.top();
                    s.pop();
                }
                s.pop(); //remove '('
            }else if(!isFirst(infix[i], s.top())){
                while(!s.empty() && !isFirst(infix[i],s.top())){
                    ret+=s.top();
                    s.pop();
                }
                s.push(infix[i]);
            }
        }
    }
    while(!s.empty()){
        ret+=s.top();
        s.pop();
    }
    return ret;
}

int main(){
    string infix;
    cin >> infix;
    string postfix=infixToPostfix(infix);
    cout << postfix <<"\n";
    return 0;
}