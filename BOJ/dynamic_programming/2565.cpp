/*
두 전봇대 A와 B 사이에 하나 둘씩 전깃줄을 추가하다 보니 전깃줄이 서로 교차(시작점을 a1,a2 도착점을 b1,b2일때 a1<a2 && b1>b2인 경우)하는 경우가 발생하였다. 
합선의 위험이 있어 이들 중 몇 개의 전깃줄을 없애 전깃줄이 교차하지 않도록 만들려고 한다.

이때 없애야하는 최소한의 전깃줄의 수는?
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF=987654321;
const int MAXN=100;

vector<pair<int,int>> lines;
vector<int> cache(MAXN,-1);

int lis(int start){
    if(start==lines.size()-1) return 1;
    int& ret=cache[start];
    if(ret!=-1) return ret;
    ret=1;
    for(int i=start+1;i<lines.size();i++){
        if(lines[start].second<lines[i].second){
            ret=max(ret,1+lis(i));
        }
    }
    return ret;
}

int solve(){
    sort(lines.begin(),lines.end());
    int bLis=0;
    for(int i=0;i<lines.size();i++){
        bLis=max(bLis, lis(i));
    }
    return lines.size()-bLis;
}


int main(){
    int lineCount;
    cin >> lineCount;
    lines.resize(lineCount);
    for(int i=0;i<lines.size();i++){
        int posA,posB;
        cin >> posA >> posB;
        lines[i]=make_pair(posA,posB);
    }
    cout << solve() <<"\n";
    return 0;
}