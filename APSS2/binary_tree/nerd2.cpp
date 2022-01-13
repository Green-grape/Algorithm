#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>

//map 관련 공부할것!

#define MAX_PERSON 50000

using namespace std;

map<int,int> coords;

int getRegisterableCount(int,int);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int peopleCount;
        int res=0;
        cin >> peopleCount;
        for(int j=0;j<peopleCount;j++){
            int peopleCount, bowlCount;
            scanf("%d %d", &peopleCount, &bowlCount);
            res+=getRegisterableCount(peopleCount,bowlCount);
        }
        cout << res <<"\n";
        coords.clear();
    }
}

bool isCanRegister(int x,int y){
    map<int,int>::iterator it=coords.lower_bound(x);
    if(it==coords.end()) return true;
    return y>it->second;
}


void removeUnRegisterable(int x,int y){
    map<int,int>::iterator it=coords.lower_bound(x);
    if(it==coords.begin()) return;
    it--;
    while(true){
        if(it->second>y) break;
        if(it==coords.begin()) {
            coords.erase(it);
            break;
        }
        map<int,int>::iterator beforeIt=it;
        beforeIt--;
        coords.erase(it);
        it=beforeIt;
    }
}

int getRegisterableCount(int x, int y){
    if(!isCanRegister(x,y)){
        return coords.size();
    }
    removeUnRegisterable(x,y);
    coords[x]=y;
    return coords.size();
}


