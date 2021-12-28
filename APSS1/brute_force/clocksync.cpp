#include <iostream>
#include <vector>

#define CLOCK_NUM 16
#define SWITCH_NUM 10
#define INF 987654321

int getSmallestClickSwitch(int);
//-1 -> 빈칸
const int switchs[10][5]={
    {0,1,2,-1,-1},
    {3,7,9,11,-1},
    {4,10,14,15,-1},
    {0,4,5,6,7},
    {6,7,8,10,12},
    {0,2,14,15,-1},
    {3,14,15,-1,-1},
    {4,5,7,14,15},
    {1,2,3,4,5},
    {3,4,5,9,13}
};
int clicks[CLOCK_NUM]={0,};
using namespace std;

int main(){
    int testCase,clock;
    vector<int> results;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        for(int j=0;j<CLOCK_NUM;j++){
            cin >> clock;
            //12,3,6,9 -> 0,1,2,3
            int nomalizedClock=(clock%12)/3;
            clicks[j]= nomalizedClock;
        }
        results.push_back(getSmallestClickSwitch(0));
    }
    for(vector<int>::iterator iter=results.begin();iter!=results.end();iter++){
        cout << (*iter) <<"\n";
    }
    return 0;
}

int getSmallestClickSwitch(int targetSwitch){
    //기저사례
    bool allZero=true;
    for(int i=0;i<CLOCK_NUM;i++){
        if(clicks[i]!=0) allZero=false;
    }
    if(targetSwitch==SWITCH_NUM) return allZero ? 0 : INF; 

    int count=INF;
    for(int i=0;i<4;i++){
        //click
        int temp[5];
        for(int j=0;j<5;j++){
            if(switchs[targetSwitch][j]==-1) break;
            temp[j]=clicks[switchs[targetSwitch][j]];
            clicks[switchs[targetSwitch][j]]=(clicks[switchs[targetSwitch][j]]+i)%4;
        }
        count=min(count, i+getSmallestClickSwitch(targetSwitch+1));
        for(int j=0;j<5;j++){
            if(switchs[targetSwitch][j]==-1) break;
            clicks[switchs[targetSwitch][j]]=temp[j];
        }
    }
    return count;
}