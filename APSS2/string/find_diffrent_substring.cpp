//문자열에서 서로 다른 부분 문자열의 개수는?
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int getDiffSubstringCount(const string&);

int main(){
    string str;
    cin >> str;
    int count=getDiffSubstringCount(str);
    cout << count << "\n";
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

//기본적인 생각 n^2개의 부분 문자열이 있는지 확인하면서 비교 Hash써도 O(n^3) (모든 부분 문자열 n^2, 문자열 비교 n)
//모든 부분 문자열은 문자열의 접미사들의 접두사로 표현할 수 있다. 이때 서로 겹치는 것은 자기보다 번호가 하나 앞선 접미사 배열을 참고해서 빼준다.
//접미사 배열 만드는데 O(n(lgn)^2), 비교하는데 O(n^2) -> O(n^2) 

int getCommonPrefix(const string& s, int i, int j){
    int ret=0;
    while(i<s.length() && j<s.length() && s[i]==s[j]){
        i++;j++;ret++;
    }
    return ret;
}

int getDiffSubstringCount(const string& str){
    vector<int> suffixArray=getSuffixArray(str);
    int ret=0;
    for(int i=0;i<str.length();i++){
        int commonPrefixs=0;
        if(i!=0) commonPrefixs=getCommonPrefix(str,suffixArray[i-1],suffixArray[i]);
        ret+=(str.length()-suffixArray[i])-commonPrefixs;
    }
    return ret;
}