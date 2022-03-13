#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int MAX_LENGTH=100;

int isMatchToPattern(const string, const string);
int isMatchToPatternFast(const string, const string);
int isMatchToPatternCache[MAX_LENGTH][MAX_LENGTH];
void init();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        string pattern;
        cin >> pattern;
        int nameCount;
        cin >> nameCount;
        for(int j=0;j<nameCount;j++){
            string s;
            cin >> s;
            init();
            if(isMatchToPatternFast(pattern,s)) cout <<s<<"\n";
        }
    }
    return 0;
}

void init(){
    memset(isMatchToPatternCache,-1,sizeof(isMatchToPatternCache));
}


//O(n^3)
int isMatchToPattern(const string pattern, const string str){
    if(isMatchToPatternCache[pattern.size()][str.size()]!=-1) return isMatchToPatternCache[pattern.size()][str.size()];
    int idx=0;
    //*제외하고 모두 처리
    while(idx<pattern.length() && idx<str.length() && (pattern[idx]=='?' || pattern[idx]==str[idx])){
        idx++;
    }
    //기저사례 처리
    if(idx==pattern.length() && idx==str.length()) return isMatchToPatternCache[pattern.size()][str.size()]=1;
    if(pattern[idx]!='*' && pattern[idx]!=str[idx]) return isMatchToPatternCache[pattern.size()][str.size()]=0;

    int ret=0;
    if(pattern[idx]=='*'){
        for(int start=idx;start<=str.length();start++){
            ret=max(isMatchToPattern(pattern.substr(idx+1), str.substr(start)),ret);
        }
    }else return isMatchToPatternCache[pattern.size()][str.size()]=0;
    return isMatchToPatternCache[pattern.size()][str.size()]=ret;
}

//O(n^2) 첫*을 찾고 *가 몇글자에 대응되는지 확인하는 반복문 삭제
int isMatchToPatternFast(const string pattern, const string str){
    int& ret=isMatchToPatternCache[pattern.size()][str.size()];
    if(ret!=-1) return isMatchToPatternCache[pattern.size()][str.size()];

    if(pattern.length()>0 && str.length()>0 && (pattern[0]=='?' || pattern[0]==str[0])){
        return ret=isMatchToPatternFast(pattern.substr(1),str.substr(1));
    }
    //기저사례 처리
    if(pattern.length()==0) return ret=(str.length()==0);
    if(pattern[0]!='*' && pattern[0]!=str[0]) return ret=0;
    
    if(pattern[0]=='*'){
        if(isMatchToPatternFast(pattern.substr(1),str.substr(0)) || (str.length()>0 && isMatchToPatternFast(pattern.substr(0),str.substr(1)))){
            return ret=1;
        }
    }
    return ret=0;
}

