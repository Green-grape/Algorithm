/*
같은 양의 두 용액을 혼합한 용액의 특성값은 혼합에 사용된 각 용액의 특성값의 합으로 정의한다
특성값은 모두 -1,000,000,000 이상 1,000,000,000 이하이다. 
이 중 두 개의 서로 다른 용액을 혼합하여 특성값이 0에 가장 가까운 용액을 만들어내는 두 용액을 찾는 프로그램을 작성하시오.
*/

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;


vector<int> ph;

//복습

pair<int,int> getSumCloesdToZero(){
    sort(ph.begin(),ph.end());
    int firstNotNeg=-1;
    for(int i=0;i<ph.size();i++){
        if(ph[i]>=0){
            firstNotNeg=i;
            break;
        }
    }
    if(firstNotNeg==-1){ //all neg
        return make_pair(ph.size()-2,ph.size()-1);
    }
    else if(firstNotNeg==0){ //all not neg
        return make_pair(0,1);
    }
    int neg=0,pos=ph.size()-1;
    int minN=2000000001;
    pair<int,int> ret1(neg,pos);
    while(neg<pos){
        if(ph[neg]+ph[pos]<0){
            if(abs(ph[neg]+ph[pos])<minN){
                minN=abs(ph[neg]+ph[pos]);
                ret1.first=neg;
                ret1.second=pos;
            }
            neg++;
        }else if(ph[neg]+ph[pos]>0){
            if(abs(ph[neg]+ph[pos])<minN){
                minN=abs(ph[neg]+ph[pos]);
                ret1.first=neg;
                ret1.second=pos;
            }
            pos--;
        }else{
            ret1.first=neg;
            ret1.second=pos;
            break;
        }
    }
    return ret1;
}

int main(){
    int phCount;
    scanf("%d", &phCount);
    ph.resize(phCount);
    for(int i=0;i<ph.size();i++){
        scanf("%d", &ph[i]);
    }
    pair<int,int> ret=getSumCloesdToZero();
    printf("%d %d", ph[ret.first], ph[ret.second]);
    return 0;
}

