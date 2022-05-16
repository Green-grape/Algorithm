#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <iomanip>

using namespace std;

double solve(vector<string> postfix){
    stack<double> s;
    for(int i=0;i<postfix.size();i++){
        if(postfix[i]=="*" || postfix[i]=="+" || postfix[i]=="/" || postfix[i]=="-"){
            double b=s.top();
            s.pop();
            double a=s.top();
            s.pop();
            if(postfix[i]=="*") s.push(a*b);
            if(postfix[i]=="+") s.push(a+b);
            if(postfix[i]=="/") s.push(a/b);
            if(postfix[i]=="-") s.push(a-b);
        }
        else{
            s.push(stod(postfix[i]));
        }
    }
    return s.top();
}

int main(){
    int numberCount;
    cin >> numberCount;
    string postfix;
    cin >> postfix;
    vector<string> form;
    vector<string> num(numberCount);
    for(int i=0;i<numberCount;i++){
        cin >> num[i];
    }
    for(int i=0;i<postfix.size();i++){
        if(0<=postfix[i]-'A' && postfix[i]-'A'<numberCount){
            form.push_back(num[postfix[i]-'A']);
        }
        else{
            form.push_back(string(1,postfix[i]));
        }
    }
    cout<<fixed;
    cout.precision(2);
    cout << solve(form) <<"\n";
    return 0;

}