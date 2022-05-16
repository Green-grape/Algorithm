#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <sstream>


/*
getline, split 구현 복습할것 2022/05/12
*/
using namespace std;

vector<int> queue;

void push(int x){
    queue.push_back(x);
}

int pop(){
    if(queue.size()==0) return -1;
    int ret=queue[queue.size()-1];
    queue.pop_back();
    return ret;
}

int size() {return queue.size();}

int empty(){
    if(queue.size()==0) return 1;
    else return 0;
}

int top(){
    if(queue.size()==0) return -1;
    else return queue[queue.size()-1];
}

vector<string> split(string str, char Delimiter) {
    istringstream iss(str);             // istringstream에 str을 담는다.
    string buffer;                      // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼
 
    vector<string> result;
 
    // istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
    while (getline(iss, buffer, Delimiter)) {
        result.push_back(buffer);               // 절삭된 문자열을 vector에 저장
    }
 
    return result;
}

int main(){
    string commandCount;
    getline(cin,commandCount);
    int count=stoi(commandCount);
    while(count--){
        string command;
        getline(cin,command);
        vector<string> s_command=split(command, ' ');
        if(s_command[0]=="push"){
            push(stoi(s_command[1]));
        }
        if(s_command[0]=="top") cout << top() <<"\n";
        if(s_command[0]=="size") cout << size() <<"\n";
        if(s_command[0]=="empty") cout << empty() <<"\n";
        if(s_command[0]=="pop") cout <<pop()<<"\n";
    }
    return 0;
}