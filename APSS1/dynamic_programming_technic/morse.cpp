#include <iostream>
#include <vector>
#include <string.h>
#include <string>

const int MAX_M=100;
const int MAX_N=100;
const int INF=1000000001;
using namespace std;

int bino[MAX_M+MAX_N+1][MAX_M+MAX_N+1];

void calBinomial();
string getKthString(int n, int m, int k);

int main(){
    int testCase;
    cin >> testCase;
    calBinomial();
    for(int i=0;i<testCase;i++){
        int n,m,k;
        cin >> n >> m >>k;
        cout << getKthString(n,m,k) <<"\n";
    }
    return 0;
}

void calBinomial(){
    memset(bino,-1,sizeof(bino));
    for(int i=0;i<=MAX_M+MAX_N;i++){
        bino[i][0]=bino[i][i]=1;
        for(int j=1;j<i;j++){
            bino[i][j]=min(INF,bino[i-1][j-1]+bino[i-1][j]);
        }
    }
}

//n개의 장점과 m개의 단점이 있을때 k번째 모스부호는?
string getKthString(int n, int m, int k){
    if(n==0) return string(m,'o');
    if(m==0) return string(n,'-'); 
    if(k<=bino[m+n-1][n-1]) return "-"+getKthString(n-1,m,k);
    return "o"+getKthString(n,m-1,k-bino[m+n-1][n-1]);
}