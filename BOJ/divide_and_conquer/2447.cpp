
/*
재귀적인 패턴으로 별을 찍어 보자. N이 3의 거듭제곱(3, 9, 27, ...)이라고 할 때, 크기 N의 패턴은 N×N 정사각형 모양이다.

크기 3의 패턴은 가운데에 공백이 있고, 가운데를 제외한 모든 칸에 별이 하나씩 있는 패턴이다.
N이 3보다 클 경우, 크기 N의 패턴은 공백으로 채워진 가운데의 (N/3)×(N/3) 정사각형을 크기 N/3의 패턴으로 둘러싼 형태이다. 
*/

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

vector<string> printStar(int n){
    vector<string> ret;
    if(n==3){
        ret.push_back("***");
        ret.push_back("* *");
        ret.push_back("***");
        return ret;
    }
    ret.resize(n);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i==1 && j==1){
                for(int k=n/3;k<2*n/3;k++){
                    ret[k]+=string(n/3,' ');
                }
            }else{
                vector<string> add=printStar(n/3);
                for(int k=i*(n/3);k<(i+1)*(n/3);k++){
                    ret[k]+=add[k-i*(n/3)];
                }
            }
        }
    }
    return ret;
}

int main(){
    int n;
    scanf("%d", &n);
    vector<string> ret=printStar(n);
    for(int i=0;i<ret.size();i++){
        cout << ret[i] <<"\n";
    }
    return 0;
}