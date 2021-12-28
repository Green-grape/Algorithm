#include <iostream>
#include "string.h"

#define MAX_SQUARE 100
#define MOD 10000000

using namespace std;

int monotonePoliominoWithHeight[MAX_SQUARE+1][MAX_SQUARE+1];
int getMonotonePoliomino(int);
int p(int,int);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int numSquare;
        cin >> numSquare;
        int res=getMonotonePoliomino(numSquare);
        cout << res <<"\n";
    }
    return 0;
}

/*
p(numSquare,firstH):총 블럭의 수가 numSquare개 이고 맨 앞의 높이가 first_h인 경우 세로 단조 폴리오미노의 개수
total=for(int k=1;k<=n;k++) +p(n,k)
p(n,h)=for(int k=1;k<=n-h;k++) +p(n-h,k)*(h-k+1)
*/
int p(int numSquare, int firstH){
    int& res=monotonePoliominoWithHeight[numSquare][firstH];
    if(res!=-1) return res;
    if(numSquare<=2) return 1;
    if(numSquare==firstH) return 1;
    res=0;
    for(int k=1;k<=numSquare-firstH;k++){
        res=(res+p(numSquare-firstH,k)*(firstH+k-1))%MOD;
    }
    return res;
}

int getMonotonePoliomino(int numSquare){
    memset(monotonePoliominoWithHeight,-1,sizeof(monotonePoliominoWithHeight));
    int res=0;
    for(int i=1;i<=numSquare;i++){
        res=(res+p(numSquare,i))%MOD;
    }
    return res;
}


