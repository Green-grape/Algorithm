#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "string.h"

#define MAX_STRING_LENGTH 101

using namespace std;

int matchFileNameAndPattern(const string& , const string&);
int cache[MAX_STRING_LENGTH][MAX_STRING_LENGTH];
bool compare(const string&, const string&);

int main(){
    int testCase;
    string pattern;
    int fileNameNum;
    cin >> testCase;
    vector<string> res;
    for(int i=0;i<testCase;i++){
        string tempStr;
        vector<string> tempRes;
        cin >> pattern;
        cin >> fileNameNum;
        vector<string> fileNames;
        for(int j=0;j<fileNameNum;j++){
            cin >> tempStr;
            fileNames.push_back(tempStr);
        }
        for(int j=0;j<fileNameNum;j++){
            memset(cache, -1, sizeof(cache));
            if(matchFileNameAndPattern(fileNames[j],pattern)){
                tempRes.push_back(fileNames[j]);
            }
        }
        sort(tempRes.begin(),tempRes.end(),compare);
        for(int j=0;j<tempRes.size();j++) res.push_back(tempRes[j]);
    }
    for(int i=0;i<res.size();i++){
        cout <<res[i]<<"\n";
    }
    return 0;
}

bool compare(const string& str1, const string& str2){
    for(int i=0;(i<str1.length() && i<str2.length());i++){
        if(str1[i]!=str2[i]) return str1[i]<str2[i];
    }
    return str1.length() < str2.length();
}

//*를 제외하고 패턴과 파일이름을 매치한 후 *는 모든 문자열과 대응된다는 것을 이용한 완전탐색을 하는 함수
int matchFileNameAndPattern(const string& fileName, const string& pattern){
    int cacheCodeX=fileName.length(), cacheCodeY=pattern.length();
    if(cache[cacheCodeX][cacheCodeY]!=-1) return cache[cacheCodeX][cacheCodeY];
    int pos=0;
    //*전 까지 비교
    while(pos<fileName.length() && pos<pattern.length() && 
        (pattern[pos]=='?' || fileName[pos]==pattern[pos])){
            pos++;
    }
    //파일이름 끝에 도달 -> 패턴이 더 길다 -> 이후 모두 *여야함
    if(pos==fileName.length()){
        cache[cacheCodeX][cacheCodeY]=1;
        for(;pos<pattern.length();pos++){
            if(pattern[pos]!='*') cache[cacheCodeX][cacheCodeY]=0;
        }
        return cache[cacheCodeX][cacheCodeY];
    }
    if(pos==pattern.length()){ //*이 없다 -> 문자열이 더 길다 -> 길이가 같아야만 같음
       return cache[cacheCodeX][cacheCodeY]=(fileName.length()==pattern.length());
    }
    //pos 위치의 패턴과 문자열이 다른 경우 *만 가능하다.
    if((fileName[pos]!=pattern[pos]) && (pattern[pos]!='*')){
        cache[cacheCodeX][cacheCodeY]=0;
        return cache[cacheCodeX][cacheCodeY];
    }

    //pattern[pos]=='*'인 경우 매칭되는 문자열의 길이를 하나씩 늘려가면서 완전 탐색
    cache[cacheCodeX][cacheCodeY]=0;
    for(int pass=0;pass+pos<=fileName.length();pass++){
        if(matchFileNameAndPattern(fileName.substr(pos+pass), pattern.substr(pos+1))){
            cache[cacheCodeX][cacheCodeY]=1;
            break;
        }
    }
    return cache[cacheCodeX][cacheCodeY];
}