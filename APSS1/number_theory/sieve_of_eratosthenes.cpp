#include <string.h>
#include <vector>
#include <cmath>

const int MAX_N=1000;
int n;
bool isPrime[MAX_N+1];
int minFactor[MAX_N+1]; //minFactor[i]=i의 가장 작은 소인수

void eratosthenes(){
    memset(isPrime,1,sizeof(isPrime));
    isPrime[0]=isPrime[1]=false;
    int sqrtN=int(sqrt(MAX_N));
    for(int i=2;i<=sqrtN;i++){
        if(isPrime[i]){
            for(int j=i*i;j<=n;j+=i){
                isPrime[j]=false;
            }
        }
    }
}

void eratosthenes2(){
    minFactor[0]=minFactor[1]=-1;//없음
    int sqrtN=int(sqrt(MAX_N));
    for(int i=2;i<=MAX_N;i++){
        minFactor[i]=i;
    }
    for(int i=2;i<=sqrtN;i++){
        if(minFactor[i]==i){
            for(int j=i*i;j<=n;j+=i){
                if(minFactor[j]==j) minFactor[j]=i;
            }
        }
    }
}

//주어진 정수 n을 소인수 분해
std::vector<int> factorSimple(int n){ //sqrt(n)이하의 모든 수 확인 
    std::vector<int> ret;
    int sqrtN=int(sqrt(n));
    for(int div=2;div<=sqrtN;div++){
        while(n%div==0){
            n/=div;
            ret.push_back(div);
        }
    }
    if(n>1) ret.push_back(n);
    return ret;
}

std::vector<int> factorFast(int n){ //소수들만 확인
    std::vector<int> ret;
    while(n>1){
        ret.push_back(minFactor[n]);
        n/=minFactor[n];
    }
    return ret;
}

