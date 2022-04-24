#include <iostream>
#include <vector>

std::vector<int> solve(std::vector<int> r, std::vector<int> p);

int main(){
    int testCase;
    std::cin >> testCase;
    for(int i=0;i<testCase;i++){
        int n;
        std::cin >> n;
        std::vector<int> r(n),p(n);
        for(int j=0;j<n;j++) std::cin >> r[j];
        for(int j=0;j<n;j++) std::cin >> p[j];
        std::vector<int> ret=solve(r,p);
        for(int j=0;j<n;j++) std::cout << ret[j] <<" ";
        std::cout << "\n";
    }
    return 0;
}

int gcd(int a,int b){
    if(b==0) return a;
    return gcd(b, a%b);
}

int gcd(std::vector<int> v){
    int length=v.size();
    if(v.size()==1) return v[0];
    int totalGcd=gcd(v[0],v[1]);
    for(int i=2;i<length;i++){
        totalGcd=gcd(totalGcd,v[i]);
    }
    return totalGcd;
}

//모든 i에 대해서 p[i]/r[i]의 최대보다 같거나 크고 r[i]*a/b가 정수인 가장 작은 유리수 a/b를 구하자
//이때 b를 gcd로 두면 a=mul를 정수 취급하고 빠르게 구할수 있다.
std::vector<int> solve(std::vector<int> r, std::vector<int> p){
    int totalGcd=gcd(r);
    int n=r.size();
    std::vector<int> ret(n);
    int mul=totalGcd;
    //mul>=max(put[i]/receipe[i]*b) 모든 i에 대하여
    for(int i=0;i<n;i++){
        mul=std::max(mul, (p[i]*totalGcd+r[i]-1)/r[i]); 
    }
    for(int i=0;i<n;i++){
        ret[i]=r[i]*mul/totalGcd-p[i];
    }
    return ret;
}

std::vector<int> solveWithSimulation(std::vector<int> receipe, std::vector<int> put){
    std::vector<int> original=put;
    int n=receipe.size();
    std::vector<int> ret(n);
    for(int i=0;i<n;i++){ //최소치를 집어 넣음
        ret[i]=std::max(receipe[i]-put[i],0);
        put[i]+=ret[i];
    }
    int iter=0;
    while(true){
        iter++;
        bool isEnd=true;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                int required=(put[i]*receipe[j]+receipe[i]-1)/receipe[i];
                if(required>put[j]){
                    ret[j]+=required-put[j];
                    put[j]=required;
                    isEnd=false;
                }
            }
        }
        if(isEnd) break;
    }
    return ret;
}