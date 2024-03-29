/*
원형문자열에서 사전순으로 가장 빠른것을 출력
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string getMinAlphabeticalOrderString(const string&);

int main(){
    string str;
    cin >> str;
    string res=getMinAlphabeticalOrderString(str);
    cout << res <<"\n";
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

//기본적인 생각 -> n개의 후보를 만든뒤 모두 비교 O(n^2)
//원형문자열이므로 문자열을 2개 붙여서 접미사 배열을 만든뒤 접미사 배열중 길이가 n이상인 것중에 제일 앞에 오는 것
//을 찾는다 -> k=2n, O(k(lgk)^2) 
string getMinAlphabeticalOrderString(const string& circularString){
    string doubleString=circularString+circularString;
    vector<int> suffixArray=getSuffixArray(doubleString);
    for(int i=0;i<suffixArray.size();i++){
        if(suffixArray[i]>=circularString.length()){
            return doubleString.substr(suffixArray[i],circularString.length());
        }
    }
    return "OH..";
}

