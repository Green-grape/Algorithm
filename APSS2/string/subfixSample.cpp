#include <vector>
#include <string>

using namespace std;

struct Comparator{
    const vector<int>& group;
    int t;
    Comparator(vector<int>& _group, int _t){
        group(_group);
        t(_t);
    }
    bool operator()(int a,int b){
        if(group[a]!=group[b]) return group[a]<group[b];
        return group[a+t]<group[b+t];
    }
}

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
            if(Comparator(suffixArray[i-1],suffixArray[i])){
                newGroup[[suffixArray[i]]]=newGroup[[suffixArray[i-1]]]+1;
            }
            else{
                newGroup[[suffixArray[i]]]=newGroup[[suffixArray[i-1]]];
            }
        }
        group=newGroup;
    }
    return suffixArray;
}