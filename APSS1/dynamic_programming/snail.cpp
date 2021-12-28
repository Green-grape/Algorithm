#include <iostream>
#include <vector>
#include <string>

#define MAX_DAYS (100)
using namespace std;

double canGoUpToTop[MAX_DAYS][2*MAX_DAYS+1];
int totalDays;
int height;

double climb(int, int);

int main(){

}

double climb(int days,int sum){
    double& ret=canGoUpToTop[days][sum];
    if(days==totalDays-1){
        if(sum>=height-1) return 1;
        else if(sum>=height-2) return 0.75;
        else return 0;
    }
    if(ret!=-1) return ret;
    return ret=0.25*climb(days+1,sum+1)+0.75*climb(days+1,sum+2);
}