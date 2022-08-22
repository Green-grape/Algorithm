/*비트마스크로 에라토스 테네스의 채 알고리즘 구현*/

#include <string.h>
#include <cmath>

int n;
const int MAX_N=100000;
unsigned char sieve[(MAX_N+7)/8];

bool isPrime(int k){
    return sieve[k>>3] & (1<<(k & 7));
}

void setComposite(int k){ //소수가 아니라고 표시
    sieve[k>>3]=(sieve[k>>3] & ~(1<<(k & 7)));
}

void eratosthenes(){
    memset(sieve,255,sizeof(sieve));
    setComposite(0);
    setComposite(1);
    int sqrtN=int(sqrt(n));
    for(int i=2;i<=sqrtN;i++){
        if(isPrime(i)){
            for(int j=i*i;j<=n;j+=i) setComposite(j);
        }
    }
}