#include <iostream>
#include <map>
#include <vector>

const int MAXN=1000;

using namespace std;
vector<int> cache(MAXN,-1);
vector<pair<string,int>> removableString;
string s;

int getMaxScore(int i){ //i에서 부터 문자열을 지워서 얻을 수 있는 최대 점수는?
    if(i==s.length()) return 0;
    int& ret=cache[i];
    if(ret!=-1) return ret;
    ret=0;
    for(int idx=0;idx<removableString.size();idx++){
        string::size_type start=s.find(removableString[idx].first,i);
        if(start==i){
            ret=max(ret,removableString[idx].second+getMaxScore(i+removableString[idx].first.length()));
        }
    }
    ret=max(ret,1+getMaxScore(i+1));
    return ret;
}

int main(){
    cin >> s;
    int removeCount;

    cin >> removeCount;
    for(int i=0;i<removeCount;i++){
        string removeString;
        int removeScore;
        cin >> removeString >> removeScore;
        removableString.push_back(make_pair(removeString,removeScore));
    }
    cout << getMaxScore(0) <<"\n";
    return 0;
}
