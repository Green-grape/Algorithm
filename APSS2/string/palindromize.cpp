#include <iostream>
#include <vector>
#include <string>
//palindrome:앞, 뒤로 읽었을 때 똑같은 문자열
//문자열이 주어졌을때 가장 짧은 문자열을 붙여서 palindrome을 만들때 이 최소길이는?

using namespace std;

int getSmalleatPalindromeLength(const string&);

int main(){
    string str;
    cin >> str;
    int length=getSmalleatPalindromeLength(str);
    cout << length << "\n";
    return 0;
}

string getReverseString(string str){
    string ret="";
    for(string::reverse_iterator reviter=str.rbegin();reviter!=str.rend();reviter++){
        ret+=(*reviter);
    }
    return ret;
}

vector<int> getParialMatch(const string& str){
    //자기 자신에 대한 kmpSearch 수행
    int begin=1, matched=0;
    vector<int> p(str.length(),0);
    while(begin+matched<str.length()){
        if(str[begin+matched]==str[matched]){
            p[begin+matched]=matched+1;
            matched++;
        }else{
            if(matched==0) begin++;
            else{
                begin+=matched-p[matched-1];
                matched=p[matched-1];
            }
        }
    }
    return p;
}

int getSmalleatPalindromeLength(const string& str){
    string reverseStr=getReverseString(str);
    int begin=0, matched=0, maxMatched=0;
    vector<int> partialMatch=getParialMatch(reverseStr);
    while(begin+matched<str.length()){
        if(str[begin+matched]==reverseStr[matched]){
            matched++;
            maxMatched=max(maxMatched,matched);
        }
        else{
            if(matched==0) begin++;
            else{
                begin+=matched-partialMatch[matched-1];
                matched=partialMatch[matched-1];
            }
        }
    }
    return 2*str.length()-maxMatched;
}


