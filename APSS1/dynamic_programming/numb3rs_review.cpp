#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

const int MAX_VILLAGE_COUNT=50;
const int MAX_PASSED_DAY=100;
int villageCount, passedDay, prison;
int adj[MAX_VILLAGE_COUNT][MAX_VILLAGE_COUNT];
double cache[MAX_VILLAGE_COUNT][MAX_PASSED_DAY+1];

double getProbabilityOfExistence(int village, int passedDay);
void init();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        cin >> villageCount >> passedDay >> prison;
        for(int j=0;j<villageCount;j++){
            for(int k=0;k<villageCount;k++){
                cin >> adj[j][k];
            }
        }
        int printCount;
        cin >> printCount;
        init();
        for(int j=0;j<printCount;j++){
            int village;
            cin >> village;
            printf("%.10f\n", getProbabilityOfExistence(village,passedDay));
        }
    }
    return 0;
}

void init(){
    for(int i=0;i<MAX_VILLAGE_COUNT;i++){
        for(int j=0;j<MAX_PASSED_DAY+1;j++){
            cache[i][j]=-1;
        }
    }
}

//passedDay만큼 지났을때 village에 있을 확률
double getProbabilityOfExistence(int village, int passedDay){
    double& ret=cache[village][passedDay];
    if(ret!=-1) return ret;
    if(passedDay==1){
        if(adj[village][prison]==0) return ret=0;
        int nextToPrisonCount=0;
        for(int i=0;i<villageCount;i++){
            if(adj[i][prison]) nextToPrisonCount++;
        }
        return ret=1.0/nextToPrisonCount;
    }
    ret=0;
    for(int i=0;i<villageCount;i++){
        if(adj[i][village]){
            double p=0;
            for(int j=0;j<villageCount;j++){
                if(adj[i][j]) p++;
            }
            p=1.0/p;
            ret+=p*getProbabilityOfExistence(i,passedDay-1);
        }
    }
    return ret;
}