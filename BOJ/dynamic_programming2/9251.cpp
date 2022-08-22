/*
LCS(Longest Common Subsequence, 최장 공통 부분 수열)문제는 두 수열이 주어졌을 때, 모두의 부분 수열이 되는 수열 중 가장 긴 것의 길이를 구해라
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_LENGTH=1000;
vector<vector<int>> cache(MAX_LENGTH, vector<int>(MAX_LENGTH,-1));
string a,b;

int lcs(int i, int j){
    if(i>=a.size() || j>=b.size()) return 0;
    int& ret=cache[i][j];
    if(ret!=-1) return ret;
    if(a[i]==b[j]) return ret=1+lcs(i+1,j+1);
    return ret=max(lcs(i+1,j),lcs(i,j+1));
}

int main(){
    cin >> a >> b;
    cout << lcs(0,0) <<"\n";
    return 0;
}