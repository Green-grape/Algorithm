#include <iostream>
#include <string>
#include <map>

const int MAX_GENERATION=50;
const int SEED_COUNT=3;
const int MAX_START=1e9+1;
using namespace std;
int dragonCurveLength[MAX_GENERATION+1];
int skip;
void dragonCurve(string,int);
void calDragonCurveLength();
char getDragonCurveAt(const string& dragonCurve, const int generations, int skip);

int main(){
    int testCase;
    cin >> testCase;
    calDragonCurveLength();
    for(int i=0;i<testCase;i++){
        int generation, start, wordCount;
        cin >> generation >> start >> wordCount;
        for(int j=start-1;j<start-1+wordCount;j++){
            cout << getDragonCurveAt("FX" ,generation, j);
        }
    }
    return 0;
}

void calDragonCurveLength(){
    for(int i=0;i<=MAX_GENERATION;i++){
        if(i==0) dragonCurveLength[i]=1;
        else dragonCurveLength[i]=min(MAX_START,2*dragonCurveLength[i-1]+2);
    }
}

void dragonCurve(string seed, int generation){
    if(skip<0) return;
    if(generation==0){
        if(skip<seed.length()){
            cout << seed[skip];
            skip=-1;
            return;
        }
        else skip-=seed.length();
        return;
    }
    for(int i=0;i<seed.length();i++){
        if(seed[i]=='X') dragonCurve("X+YF", generation-1);
        else if(seed[i]=='Y') dragonCurve("FX-Y",generation-1);
        else{
            if(skip==0){
                cout << seed[i];
                skip=-1;
                return;
            }else if(skip>0){
                skip-=1;
            }
        }
    }
}

//dragonCurve를 generation번 진환시킨 드래곤커브의 skip+1번째 문자반환
char getDragonCurveAt(const string& dragonCurve, const int generations, int skip){
    if(generations==0){
        if(skip>dragonCurve.length()) return '?';
        return dragonCurve[skip];
    }
    for(int i=0;i<dragonCurve.length();i++){
        if(dragonCurve[i]=='X' || dragonCurve[i]=='Y'){
            if(skip>=dragonCurveLength[generations]) skip-=dragonCurveLength[generations];
            else if(dragonCurve[i]=='X'){
                return getDragonCurveAt("X+YF",generations-1,skip);
            }else{
                return getDragonCurveAt("FX-Y",generations-1,skip);
            }
        }
        else{
            if(skip>0) skip-=1;
            else return dragonCurve[i];
        }
    }
    return '?';
}

