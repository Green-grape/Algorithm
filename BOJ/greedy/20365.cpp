/*
neighbor 블로그를 운영하는 일우는 매일 아침 풀고 싶은 문제를 미리 정해놓고 글을 올린다. 
그리고 매일 밤 각각의 문제에 대하여, 해결한 경우 파란색, 해결하지 못한 경우 빨간색으로 칠한다. 
일우는 각 문제를 칠할 때 아래와 같은 과정을 한 번의 작업으로 수행한다.

1. 연속된 임의의 문제들을 선택한다.
2. 선택된 문제들을 전부 원하는 같은 색으로 칠한다.

각 문제를 주어진 색으로 칠할 때 필요한 최소한의 작업 횟수를 구하는 프로그램을 작성하라.
*/

#include <iostream>
#include <string>

using namespace std;

int getMinWork(string s){
    int successiveB=0,successiveR=0;
    char cur=s[0];
    for(int i=1;i<s.length();i++){
        if(s[i]==cur) continue;
        if(cur=='B') successiveB++;
        else successiveR++;
        cur=s[i];
    }
    if(cur=='B') successiveB++;
    else successiveR++;
    return 1+min(successiveR,successiveB);
}

int main(){
    int count;
    cin >> count;
    string s;
    cin >> s;
    cout << getMinWork(s)<<"\n";
    return 0;
}