/*
0부터 N까지의 정수 K개를 더해서 그 합이 N이 되는 경우의 수를 구하는 프로그램을 작성하시오.
덧셈의 순서가 바뀐 경우는 다른 경우로 센다(1+2와 2+1은 서로 다른 경우). 또한 한 개의 수를 여러 번 쓸 수도 있다.
N(1 ≤ N ≤ 200), K(1 ≤ K ≤ 200) 2개가 주어짐
*/

#include <iostream>
#include <vector>

using namespace std;

const int MAXN=200;
const int MAXK=200;
const int MOD=1e9;

vector<vector<int>> cache(MAXN+1,vector<int>(MAXK+1,-1));

int getSumCount(int n, int k){ //0~n까지의 정수를 k개 더해서 그 합이 n이 되는 경우의 수는?
    if(n==0 || k==1) return 1;
    int& ret=cache[n][k];
    if(ret!=-1) return ret;
    ret=0;
    for(int i=0;i<=n;i++) ret=(ret%MOD+getSumCount(n-i,k-1)%MOD)%MOD;
    return ret;
}

int main(){
    int n,k;
    cin >> n >> k;
    cout << getSumCount(n,k) <<"\n";
    return 0;
}

