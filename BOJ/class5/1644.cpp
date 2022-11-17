#include <iostream>
#include <vector>

using namespace std;

const int MAXN=4000000;
vector<int> primes; //MAXN보다 작거나 같은 소수들
vector<long long> primeSum; //primeSum[i]=0~i번째까지의 소수들의 합

void precal(){
    vector<int> isPrime(MAXN+1, -1);
    //에라토스네테스의 체
    for(int i=2;i<isPrime.size();i++){
        if(isPrime[i]!=-1) continue;
        isPrime[i]=1;
        primes.push_back(i);
        for(int j=i*2;j<isPrime.size();j+=i){
            isPrime[j]=0;
        }
    }
    primeSum.resize(primes.size());
    primeSum[0]=primes[0];
    for(int i=1;i<primes.size();i++){
        primeSum[i]=primeSum[i-1]+(long long)primes[i];
    }
}

long long getPrimesum(int start, int end){
    return primeSum[end]-primeSum[start]+primes[start];
}

long long solve(int n){
    long long ret=0;
    for(int i=0;i<primeSum.size();i++){
        for(int j=i;j<primeSum.size();j++){
            long long cand=getPrimesum(i,j);
            if(cand>n) break;
            if(cand==n) ret++;
        }
    }
    return ret;
}

int main(){
    int n;
    cin >> n;
    precal();
    cout << solve(n) <<"\n";
    return 0;
}