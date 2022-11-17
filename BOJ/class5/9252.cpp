#include <iostream>
#include <string>
#include <vector>

using namespace std;

string str1, str2;
vector<vector<int>> cache;
//str1.substring(start1), str2.substring(start2)의 가장 긴 부분 수열의 길이
int lcs(int start1, int start2){
    if(start1==str1.length() || start2==str2.length()) return 0;
    int& ret=cache[start1][start2];
    if(ret!=-1) return ret;
    ret=0;
    if(str1[start1]==str2[start2]){
        ret=1+lcs(start1+1,start2+1);
    }
    int cand=lcs(start1+1,start2);
    if(ret<cand){
        ret=cand;
    }
    cand=lcs(start1,start2+1);
    if(ret<cand){
        ret=cand;
    }
    return ret;
}

void reconstruct(string& ret, int cur1, int cur2){
    if(cur1==str1.length() || cur2==str2.length()) return;
    if(str1[cur1]==str2[cur2] && lcs(cur1,cur2)==1+lcs(cur1+1,cur2+1)){
        ret.push_back(str1[cur1]);
        reconstruct(ret, cur1+1, cur2+1);
    }else if(lcs(cur1,cur2)==lcs(cur1+1,cur2)){
        reconstruct(ret,cur1+1,cur2);
    }else if(lcs(cur1,cur2)==lcs(cur1,cur2+1)){
        reconstruct(ret, cur1, cur2+1);
    }
}

string solve(){
    lcs(0,0);
    string ret="";
    reconstruct(ret, 0,0);
    return ret;
}

int main(){
    cin >> str1 >> str2;
    cache=vector<vector<int>>(str1.length(), vector<int>(str2.length(),-1));
    string ret=solve();
    cout << ret.length() <<"\n"<<ret<<"\n";
    return 0;
}