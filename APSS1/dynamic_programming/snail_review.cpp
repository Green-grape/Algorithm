#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>

using namespace std;

const int MAX_HEIGHT=1000;
const int MAX_PASSEDDAYS=1000;
double cache[MAX_HEIGHT+1][MAX_PASSEDDAYS+1];

double getProbabilityToGo(int,int);
void init();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int height,passedDays;
        cin >> height >> passedDays;
        init();
        printf("%.10f\n",getProbabilityToGo(passedDays,height));
    }
    return 0;
}

void init(){
    for(int i=0;i<MAX_HEIGHT+1;i++){
        for(int j=0;j<MAX_PASSEDDAYS+1;j++){
            cache[i][j]=-1;
        }
    }
}


//passedDays가 지났을때 height에 도달할 확률 반환
double getProbabilityToGo(int passedDays, int height){
    if(height<=0) return 1.0;
    double& ret=cache[height][passedDays];
    if(ret!=-1) return ret;
    if(passedDays==1){
        if(height>2) return ret=0.0;
        else if(height>1) return ret=0.75;
        else return ret=1.0;
    }
    ret=0.75*getProbabilityToGo(passedDays-1,height-2)+0.25*getProbabilityToGo(passedDays-1,height-1);
    return ret;
}