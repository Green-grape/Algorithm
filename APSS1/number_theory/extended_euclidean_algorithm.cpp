//확장 유클리드 알고리즘 구현

#include <vector>
#include <iostream>

/*
gcd(a,b)=c일때 ax+by=c를 만족하는 정수 x,y가 반드시 존재하며 아래 알고리즘은 해당 x,y,c를 구한다.
return pair(c,pair(x,y))
*/
std::pair<int,std::pair<int,int>> getEEV(int a, int b){
    int rCur=a, rNext=b;
    int xCur=1, xNext=0;
    int yCur=0, yNext=1;
    int q=0;// ri/ri+1
    int temp=0;
    while(rNext){
        q=rCur/rNext;
        temp=rNext;
        rNext=rCur-rNext*q;
        rCur=temp;

        temp=xNext;
        xNext=xCur-xNext*q;
        xCur=temp;

        temp=yNext;
        yNext=yCur-yNext*q;
        yCur=temp;
    }
    return std::make_pair(rCur,std::make_pair(xCur,yCur));
}


//위의 소스를 이용한 모듈러 연산에서 곱셈의 역원 구하기
//모듈러 연산에서 m에대한 a의 곱셈의 역원 a^-1 구하기
//(a*a^-1)MODm=1, a*a^-1=my+1, ax-my=1 (x=a^-1)
int modInverse(int a, int m){
    std::pair<int, std::pair<int,int>> eev=getEEV(a,m);
    return (eev.second.first+m)%m;
}

int main(){
    int a=5, m=6;
    std::cout << modInverse(a,m)<<"\n";
    return 0;
}
