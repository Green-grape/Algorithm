/*
세준이는 양수와 +, -, 그리고 괄호를 가지고 식을 만들었다. 그리고 나서 세준이는 괄호를 모두 지웠다.
그리고 나서 세준이는 괄호를 적절히 쳐서 이 식의 값을 최소로 만들려고 한다.
괄호를 적절히 쳐서 이 식의 값을 최소로 만드는 프로그램을 작성하시오.

조건 
식은 ‘0’~‘9’, ‘+’, 그리고 ‘-’만으로 이루어져 있고, 가장 처음과 마지막 문자는 숫자이다. 
그리고 연속해서 두 개 이상의 연산자가 나타나지 않고, 5자리보다 많이 연속되는 숫자는 없다. 
수는 0으로 시작할 수 있다. 입력으로 주어지는 식의 길이는 50보다 작거나 같다.
*/

#include <iostream>
#include <string>

const int INF=987654321;
const int PLUS=0;
const int MINUS=2;

using namespace std;

int getMinRet(string expression){
    string num="";
    int ret=INF;bool isMinusExist=false;
    int beforeOperator=-1;
    for(int i=0;i<expression.length();i++){
        if('0'<=expression[i] && expression[i]<='9') num+=expression[i];
        else{
            if(beforeOperator==-1){
                ret=stoi(num);
                beforeOperator=expression[i]-'+';
            }
            else{
                if(isMinusExist) ret-=stoi(num);
                else{
                    if(beforeOperator==PLUS) ret+=stoi(num);
                    else{
                        ret-=stoi(num);
                        isMinusExist=true;
                    }
                }
                beforeOperator=expression[i]-'+';
            }
            num="";
        }
    }
    if(beforeOperator==-1){
        ret=stoi(num);
    }
    else{
        if(isMinusExist) ret-=stoi(num);
        else{
            if(beforeOperator==PLUS) ret+=stoi(num);
            else{
                ret-=stoi(num);
                isMinusExist=true;
            }
        }
    }
    return ret;
}

int main(){
    string exp;
    cin >> exp;
    cout << getMinRet(exp) <<"\n";
    return 0;
}


