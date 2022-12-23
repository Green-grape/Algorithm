#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Comparator
{
    const vector<int>&group;
    int t;
    Comparator(vector<int> &_group, int _t)
    :
        group(_group),
        t(_t)
    {}
    bool operator()(int a, int b)
    {
        if (group[a] != group[b])
            return group[a] < group[b];
        return group[a + t] < group[b + t];
    }
};

vector<int> LCP(const string& s, const vector<int>& sfx){ //모든 위치에서부터 가장 긴 공통 부분 접두사 반환
    int n=s.size();
    vector<int> prevSfx(n),tempLcp(n),ret(n);
    prevSfx[sfx[0]]=-1;
    for(int i=1;i<n;i++) prevSfx[sfx[i]]=sfx[i-1]; //접미사 배열의 이전 접미사 위치
    for(int i=0,common=0;i<n;i++){
        if(prevSfx[i]==-1) tempLcp[i]=0;
        else{
            while(s[i+common]==s[prevSfx[i]+common]) common++;
            tempLcp[i]=common;
            if(common>0) common--;
        }
    }
    for(int i=0;i<n;i++) ret[i]=tempLcp[sfx[i]];
    return ret;
}

// O(nlgn)(정렬)*O(lgn)(반복수)=O(n(lgn)^2)
vector<int> getSuffixArray(const string &s)
{
    int t = 1;
    int n = s.length();
    vector<int> group(n + 1); // group[i]=s[i...]가 속한 그룹번호, n+1인 이유는 길이가 0인 것도 반영
    for (int i = 0; i < n; i++)
        group[i] = s[i];
    group[n] = -1;

    vector<int> suffixArray(n);
    for (int i = 0; i < n; i++)
        suffixArray[i] = i;
    while (t < n)
    {
        Comparator com(group, t);
        sort(suffixArray.begin(), suffixArray.end(), com);
        t *= 2;
        if (t >= n)
            break;

        vector<int> newGroup(n + 1);
        newGroup[n] = -1;
        newGroup[suffixArray[0]] = 0;
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