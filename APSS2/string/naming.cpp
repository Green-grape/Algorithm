#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> getPrefixSubfixLength(const string&);

int main(){
    string str;
    cin >> str;
    vector<int> prefixSubfixLengths=getPrefixSubfixLength(str);
    for(int i=0;i<prefixSubfixLengths.size();i++){
        cout << prefixSubfixLengths[i]<<" ";
    }
    return 0;
}

//arr[i]=str[0~i]의 접두사도 되고 접미사도 되는 문자열의 최대 길이 반환
vector<int> getPartialMatch(const string& str){
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

vector<int> getPrefixSubfixLength(const string& str){
    vector<int> ret, partialMatch=getPartialMatch(str);
    int res=str.length();
    while(res>0){
        ret.push_back(res);
        res=partialMatch[res-1];
    }
    return ret;
}