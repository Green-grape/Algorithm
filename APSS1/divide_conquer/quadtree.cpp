#include <iostream>
#include <vector>
#include <string>

using namespace std;

string reverseCompressedString(string::iterator&);

int main(){
    int testCase;
    string tempString;
    vector<string> results;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        cin >> tempString;
        string::iterator start=tempString.begin();
        results.push_back(reverseCompressedString(start));
    }
    for(vector<string>::iterator iter=results.begin();iter!=results.end();iter++){
        cout << *iter << "\n";
    }
    return 0;
}

//iter가 계속 1씩 커진다는 아이디어, b,w가 기저사례
string reverseCompressedString(string::iterator& iter){
    char head=*iter;
    iter++;
    if(head=='b' || head=='w') return string(1,head); //b,w 출력
    string upLeft=reverseCompressedString(iter);
    string upRight=reverseCompressedString(iter);
    string downLeft=reverseCompressedString(iter);
    string downRight=reverseCompressedString(iter);
    return string("x")+downLeft+downRight+upLeft+upRight;
}
