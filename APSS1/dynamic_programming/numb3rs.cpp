#include <iostream>
#include <vector>
#include "string.h"

#define MAX_VILLAGE 50
#define MAX_DATE 100

using namespace std;

bool isHaveLoad[MAX_VILLAGE+1][MAX_VILLAGE+1];
double prob[MAX_VILLAGE+1][MAX_VILLAGE+1][MAX_DATE+1];
double prob2[MAX_VILLAGE+1][MAX_DATE+1];
int deg[MAX_VILLAGE+1];
int villageCount,passedDays,prisonNum, villageNum;

double getProbabilityMove(int,int);
double getProbabilityToEnd(int,int,int);
double getProbabilityToEnd2(int,int);
double getProbabilityToEnd3(int,int);
void init();
void init2();

int main(){
    cout.precision(8);

    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        cin >> villageCount >> passedDays >> prisonNum;
        memset(deg,0,sizeof(deg));
        for(int j=0;j<villageCount;j++){
            for(int k=0;k<villageCount;k++){
                int temp;
                cin >> temp;
                if(temp){
                    isHaveLoad[j][k]=true;
                    deg[j]++;
                }
                else isHaveLoad[j][k]=false;
            }
        }
        int calVillageCount;
        cin >> calVillageCount;
        for(int j=0;j<calVillageCount;j++){
            cin >> villageNum;
            init2();
            double res=getProbabilityToEnd3(villageNum,passedDays);
            cout <<res <<" ";
        } 
        cout << "\n";
    }
    return 0;
}

void init(){
    for(int i=0;i<MAX_VILLAGE+1;i++){
        for(int j=0;j<MAX_VILLAGE+1;j++){
            for(int k=0;k<MAX_DATE+1;k++){
                prob[i][j][k]=-1;
            }
        }
    }
}

void init2(){
    for(int i=0;i<MAX_VILLAGE+1;i++){
        for(int j=0;j<MAX_DATE+1;j++){
            prob2[i][j]=-1;
        }
    }
}

double getProbabilityMove(int x, int y){
    int count=0;
    if(!isHaveLoad[x][y]) return 0.0;
    for(int i=0;i<villageCount;i++){
        if(isHaveLoad[x][i]) count++;
    }
    return 1.0/count;
}

double getProbabilityToEnd(int start, int end, int count){
    double& ret=prob[start][end][count];
    if(ret!=-1){
        return ret;
    }
    if(count==1){
        if(start==end){
            ret=0.0;
            return ret;
        }
        else{  
            ret=getProbabilityMove(start,end);
            return ret;
        }
    }
    ret=0;
    for(int i=0;i<villageCount;i++){
        for(int j=1;j<passedDays;j++){
            ret+=(getProbabilityToEnd(start,i,j)*getProbabilityToEnd(i,end, passedDays-j));
        }
    }
    return ret;
}

//가정:days에 start에 있음
//start으로부터 villageNum에 passedDays에 도착할 확률
double getProbabilityToEnd2(int start, int days){
    if(days==passedDays) return start==villageNum ? 1.0 : 0.0;
    double& ret=prob2[start][days];
    if(ret>-0.5) return ret;
    ret=0.0;
    for(int i=0;i<villageCount;i++){
        if(isHaveLoad[start][i]) ret+=(getProbabilityToEnd2(i,days+1)/deg[start]);
    }
    return ret;
}

//탈옥후 days일때 cur에 숨어있을 확률 
double getProbabilityToEnd3(int cur, int days){
    if(days==0) return cur==prisonNum? 1.0:0.0;
    double& ret=prob2[cur][days]; 
    if(ret>-0.5) return ret;
    ret=0;
    for(int i=0;i<villageCount;i++){
        if(isHaveLoad[i][cur]) ret+=getProbabilityToEnd3(i,days-1)/deg[i];
    }
    return ret;
}