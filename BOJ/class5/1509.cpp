#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int INF=987654321;

vector<vector<bool>> palindroms;
vector<int> cache;

void precal(string s){
    palindroms=vector<vector<bool>>(s.size(), vector<bool>(s.size()));
    //홀수 팰린드롬
    for(int i=0;i<s.length();i++){
        int left=i,right=i;
        while(0<=left && right<s.length() && s[left]==s[right]){
            palindroms[left][right]=true;
            left--;
            right++;
        }
    }
    //짝수 팰린드롬
    for(int i=0;i<s.length()-1;i++){
        int left=i,right=i+1;
        while(0<=left && right<s.length() && s[left]==s[right]){
            palindroms[left][right]=true;
            left--;
            right++;
        }
    }

}

int getMinPartition(int cur){
    if(cur==palindroms.size()) return 0;
    int& ret=cache[cur];
    if(ret!=-1) return ret;
    ret=INF;
    for(int i=0;i<palindroms[cur].size();i++){
        if(palindroms[cur][i]){
            ret=min(ret, 1+getMinPartition(i+1));
        }
    }
    return ret;
}

int solve(string s){
    precal(s);
    cache=vector<int>(s.size(),-1);
    return getMinPartition(0);
}

int main(){
    string s;
    cin >> s;
    cout << solve(s) <<"\n";
    return 0;
}