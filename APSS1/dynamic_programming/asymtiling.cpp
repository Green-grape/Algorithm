#include <iostream>
#include <vector>
#include <string>
#include "string.h"

#define MOD 1000000007
#define MAX_WIDTH 100

using namespace std;

int kindOfTilingAtWidth[MAX_WIDTH+1];

int getSymTiling(int);
int getTiling(int);
int getAsymTiling(int);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int width;
        cin >> width;
        memset(kindOfTilingAtWidth,-1,sizeof(kindOfTilingAtWidth));
        int res=getAsymTiling(width);
        cout << res <<"\n";
    }
    return 0;
}

int getTiling(int width){
    int& ret=kindOfTilingAtWidth[width];
    if(ret!=-1) return ret;
    if(width==0) return 1;
    if(width==1) return 1;
    return ret=(getTiling(width-1)+getTiling(width-2))%MOD;
}

int getSymTiling(int width){
    int ret=0;
    if(width%2==0) ret+=getTiling((width/2)-1);
    ret+=getTiling(width/2);
    return ret%MOD;
}

int getAsymTiling(int width){
    return (getTiling(width)-getSymTiling(width)+MOD)%MOD;
}

