#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int MAX_LENGTH=100;

int isMatchToPattern(const string, const string);
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
            if(isMatchToPattern(pattern,s)) cout <<s<<"\n";
        }
    }
    return 0;
}

void init(){
    memset(isMatchToPatternCache,-1,sizeof(isMatchToPatternCache));
}

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