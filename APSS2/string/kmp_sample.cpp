#include <iostream>
#include <vector>

using namespace std;

vector<int> kmpSearch(const string&, const string&);

int main(){
    string mainString, subString;
    cin >> mainString >> subString;
    vector<int> res=kmpSearch(mainString, subString);
    for(vector<int>::iterator iter=res.begin();iter!=res.end();iter++){
        cout <<*iter<<" ";
    }
    return 0;
}


//arr[i]=str[0~i]의 접두사도 되고 접미사도 되는 문자열의 최대 길이 반환
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

//O(mainString.length()+subString.length())
//약간 변형된 알고리즘
vector<int> kmpSearch(const string& mainString, const string& subString){ 
    vector<int> maxLengthOfPreSubfix=getParialMatch(subString);
    vector<int> ret;
    int mLength=mainString.length(), sLength=subString.length();
    int begin=0, matched=0;
    while(begin<=mLength-sLength){
        if(begin+matched<mLength && mainString[begin+matched]==subString[matched]){
            matched++;
            if(matched==sLength) ret.push_back(begin);
        }else{
            if(matched==0) begin++;
            else{
                begin+=matched-maxLengthOfPreSubfix[matched-1];
                matched=maxLengthOfPreSubfix[matched-1];
            }
        }
    }
    return ret;
}

//논문과 함께 발표된 전통적인 KMP알고리즘 구현
vector<int> kmpSearch2(const string& mainString, const string& subString){
    vector<int> maxLengthOfPreSubfix=getParialMatch(subString);
    vector<int> ret;
    int matched=0;
    for(int i=0;i<mainString.length();i++){
        //matched번 글자가 매칭이 안되면 매칭된 글자 수를 maxLengthOfPreSubfix[match-1]로 줄임
        while(matched>0 && mainString[i]!=subString[matched]){
            matched=maxLengthOfPreSubfix[matched-1];
        }
        if(mainString[i]==subString[matched]){
            matched++;
            if(matched==subString.length()) {
                ret.push_back(i-matched+1);
                matched=maxLengthOfPreSubfix[matched-1];
            }
        }
    }
    return ret;
}