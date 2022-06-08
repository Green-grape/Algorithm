/*
0과 1로 이루어진 길이가 무한한 문자열 X가 있다. 이 문자열은 다음과 같은 과정으로 만들어진다.

X는 맨 처음에 "0"으로 시작한다. 
X에서 0을 1로, 1을 0으로 뒤바꾼 문자열 X'을 만든다.
X의 뒤에 X'를 붙인 문자열을 X로 다시 정의한다. 
2~3의 과정을 무한히 반복한다.
자연수 k가 주어졌을 때 X의 k번째에는 무슨 문자가 오는지 구하여라. (1 ≤ k ≤ 10^18)
*/

/*
Xn=Xn-1+Xn-1'이라 하자(X0=1, Xk'은 Xk를 뒤집은 것(0->1, 1->0))
*/

#include <cmath>
#include <iostream>

using namespace std;

double logN(int base, long long n){
    return log((double)n)/log(base);
}

int getNum(int n, long long k){ //Xn에서 k번째 문자열의 값
    if(n<=1){
        if(k==0) return 0;
        else return 1;
    }
    long long pivot=(long long)pow(2,n-1);
    if(pivot<=k) return !getNum(n-1,k-pivot);
    else return getNum(n-1,k);
}

int solve(long long k){
    double logk=logN(2,k);
    if(logk!=(int)logk) logk++;
    return getNum((int)logk,k-1);
}

int main(){
    long long k;
    cin >> k;
    cout << solve(k) <<"\n";
}