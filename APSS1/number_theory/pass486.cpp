#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string.h>

const int MAX=10000000;
//int minFactor[MAX+1]; //minFactor[i]=i의 가장 작은 약수(1이 아닌)
//int minFactorPower[MAX+1];
int factors[MAX+1];

//void preCal(); 
//int factorCount(int n);
void calFactors();

int main(){
    int testCase;
    std::cin >> testCase;
    calFactors();
    for(int i=0;i<testCase;i++){
        int divisorCount, start, end;
        std::cin >> divisorCount >> start >> end;
        int ret=0;
        for(int n=start;n<=end;n++){
            if(divisorCount==factors[n]) ret++;
        }
        std::cout << ret <<"\n";
    }
    return 0;
}

void calFactors(){
    memset(factors,0,sizeof(factors));
    for(int div=1;div<=MAX;div++){
        for(int mul=div;mul<=MAX;mul+=div){
            factors[mul]++;
        }
    }
}

/*
void preCal(){ 
    //minFactor을 미리 계산
    minFactor[0]=minFactor[1]=-1;
    for(int n=2;n<=MAX;n++){
        minFactor[n]=n;
    }
    int sqrtMAX=int(sqrt(MAX));
    for(int n=2;n<=sqrtMAX;n++){
        if(minFactor[n]==n){
            for(int k=n*n;k<=MAX;k+=n){
                if(minFactor[k]==k) minFactor[k]=n;
            }
        }
    }

    //factors && minFactorPower 계산
    factors[1]=1;
    for(int n=2;n<=MAX;n++){
        if(minFactor[n]==n){
            minFactorPower[n]=1;
            factors[n]=2;
        }
        else{
            int p=minFactor[n];
            int m=n/p;
            if(p!=minFactor[m]) minFactorPower[n]=1;
            else minFactorPower[n]=minFactorPower[m]+1;
            int a=minFactorPower[n];
            factors[n]=(factors[m]/a)*(a+1);
        }
    }
}

int factorCount(int n){
    int ret=1;
    std::vector<int> factor;
    while(n>1){
        factor.push_back(minFactor[n]);
        n/=minFactor[n];
    }
    std::sort(factor.begin(), factor.end());
    int length=factor.size();
    int sameFactor=2;
    for(int i=1;i<length;i++){
        if(factor[i]!=factor[i-1]){
            ret*=sameFactor;
            sameFactor=2;
        }else sameFactor++;
    }
    ret*=sameFactor;
    return ret;
}

*/

