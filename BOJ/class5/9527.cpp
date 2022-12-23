#include <iostream>
#include <vector>

using namespace std;

vector<long long> cntOne; //cntOne[i]=0~2^i까지의 1의 개수의 합

void precal(){
    cntOne.push_back(1);
    long long i=1;
    for(int k=0;k<60;k++){
        cntOne.push_back(cntOne.back()*2+i*2);
        i<<=1;
    }
}

long long getOneSum(long long end){ //0~end까지의 1의 개수의 합
    if(end<=1) return end;
    long long i=2;
    int cntOneIdx=0;
    for(;(i<<1)<=end;i<<=1) cntOneIdx++; 
    //end보다 작은 i까지 1의 개수합+맨 앞에 붙는 1의 개수합+나머지 1의 개수합
    return cntOne[cntOneIdx]+end-i+1+getOneSum(end-i);
}

int main(){
    long long from, to;
    cin >> from >> to;
    precal();
    long long ret=getOneSum(to)-getOneSum(from-1);
    cout << ret <<"\n";
    return 0;
}