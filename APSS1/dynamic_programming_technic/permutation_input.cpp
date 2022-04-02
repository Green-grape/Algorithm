#include <iostream>
#include <vector>

const int MAX_N=10;
int factorial[MAX_N+1];
using namespace std;

void calFactorial();

int main(){

}

void calFactorial(){
    for(int i=0;i<=MAX_N;i++){
        if(i==0 || i==1) factorial[i]=1;
        else factorial[i]=factorial[i-1]*i;
    }
}

//순열 p이 사전순으로 몇번째인지 반환한다.p의 범위 [1,MAX_N]
int getIndex(const vector<int>& p){
    int ret=0;
    for(int i=0;i<p.size();i++){
        int lessThan=0;
        for(int j=i+1;j<p.size();j++){
            if(p[j]<p[i]) lessThan++;
        }
        ret+=factorial[p.size()-i-1]*lessThan;
    }
    return ret;
}