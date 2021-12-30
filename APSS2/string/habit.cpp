//문자열에서 k번 이상 등장하는 부분 문자열의 최대길이는?
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int getMaxSubstringLengthWithFrequence(const string&, int);
int getMaxSubstringLengthWithFrequence2(const string&, int);


int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int k;
        string s;
        cin >> k;
        cin >> s;
        cout << getMaxSubstringLengthWithFrequence2(s,k) <<"\n";
    }
    return 0;
}

struct Comparator{
    vector<int>& group;
    int t;
    Comparator(vector<int>& _group, int _t): group(_group), t(_t) {}
    bool operator()(int a,int b){
        if(group[a]!=group[b]) return group[a]<group[b];
        return group[a+t]<group[b+t];
    }
};

//O(nlgn)(정렬)*O(lgn)(반복수)=O(n(lgn)^2)
vector<int> getSuffixArray(const string& s){
    int t=1;
    int n=s.length();
    vector<int> group(n+1); //group[i]=s[i...]가 속한 그룹번호, n+1인 이유는 길이가 0인 것도 반영
    for(int i=0;i<n;i++) group[i]=s[i];
    group[n]=-1;

    vector<int> suffixArray(n);
    for(int i=0;i<n;i++) suffixArray[i]=i;
    while(t<n){
        Comparator com(group,t);
        sort(suffixArray.begin(), suffixArray.end(), com);
        t*=2;
        if(t>=n) break;

        vector<int> newGroup(n+1);
        newGroup[n]=-1;
        newGroup[suffixArray[0]]=0;
        for(int i=1;i<n;i++){
            if(com(suffixArray[i-1],suffixArray[i])){
                newGroup[suffixArray[i]]=newGroup[suffixArray[i-1]]+1;
            }
            else{
                newGroup[suffixArray[i]]=newGroup[suffixArray[i-1]];
            }
        }
        group=newGroup;
    }
    return suffixArray;
}


int getCommonPrefixCount(const string& str, vector<int> idxs){
    int ret=0;
    while(true){
        bool isEndOfStr=false;
        bool isAllSame=true;
        for(int i=0;i<idxs.size();i++){
            if(idxs[i]>=str.length()){
                isEndOfStr=true;
                break;
            }
            else{
                if(i!=0 && str[idxs[i-1]]!=str[idxs[i]]){
                    isAllSame=false;
                    break;
                }
            }
        }
        if(isEndOfStr || !isAllSame) break;
        for(int i=0;i<idxs.size();i++) idxs[i]++;
        ret++;
    }
    return ret;
}

//find_diffrent_substring을 통해서 2번이상 출현하는 경우는 바로 앞의 접미사 배열과의 공통 접두사의 최대 길이를 알면되었다.
//k번이상 출현하는 경우는? -> 앞의 k-1개와 비교 -> 시간초과
int getMaxSubstringLengthWithFrequence(const string& s, int k){
    vector<int> suffixArray=getSuffixArray(s);
    int ret=0;
    for(int i=k;i<s.length();i++){
        vector<int> idxs(suffixArray.begin()+(i-k),suffixArray.begin()+i);
        int commonPrefix=getCommonPrefixCount(s, idxs);
        ret=max(ret,commonPrefix);
    }
    return ret;
}

int getCommonPrefix(const string& s, int i, int j){
    int ret=0;
    while(i<s.length() && j<s.length() && s[i]==s[j]){
        i++;j++;ret++;
    }
    return ret;
}

int getMaxSubstringLengthWithFrequence2(const string& str, int k){
    vector<int> suffixArray=getSuffixArray(str);
    int ret=0;
    for(int i=k-1;i<str.length();i++){
        ret=max(ret, getCommonPrefix(str,suffixArray[i-(k-1)],suffixArray[i]));
    }
    return ret;
}