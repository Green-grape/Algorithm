#include <iostream>

using namespace std;

int gcd(int a, int b){
    if(b==0) return a;
    return gcd(b,a%b);
}

int lcm(int a, int b){
    return a*b/gcd(a,b);
}

int m,n,x,y;
//year=am+x=bn+y를 만족하는 (a,b)쌍이 존재하는가 ? 0<=a,b인 정수
//단, year는 m,n의 최소공배수보다 작다.
int solve(){
    int maxYear=lcm(m,n);
    for(int year=x;year<=maxYear;year+=m){
        int b=(year-y)/n;
        int b_ceil=(year-y+n-1)/n;
        if(year>=y && b>=0 && b==b_ceil) return year;
    }
    return -1;
}

int main(){
    int testCase;
    cin >> testCase;
    while(testCase--){
        cin >> m >> n >> x >> y;
        cout << solve() <<"\n";
    }
    return 0;
}