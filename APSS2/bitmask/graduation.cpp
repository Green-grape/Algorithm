#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int MAX_MAJOR=12;
const int MAX_SEMESTER=10;
const int INF=987654321;

int before[MAX_MAJOR]; //before[i]=i의 선수 과목 배열
int cache[MAX_SEMESTER][(1<<MAX_MAJOR)];
vector<int> openMajor;
int majorCount,listenCount,semesterCount,maxListen;

bool isListenable(int m, int taken){
    return (before[m] & taken)==before[m];
}

void init(){
    memset(before,0,sizeof(before));
    memset(cache,-1,sizeof(cache));
    openMajor.resize(0);
}

int bitCount(int bit){
    return __builtin_popcount(bit);
}

//현재학기가 curSemester이고 takenMajor만큼 과목을 들었을때 앞으로 들어야하는 최소의 학기 수는?
int graduate(int curSemester,int takenMajor){
    if(bitCount(takenMajor)>=listenCount) return 0;
    if(curSemester>=semesterCount) return INF;
    int& minSemester=cache[curSemester][takenMajor];
    if(minSemester!=-1) return minSemester;
    minSemester=INF;
    int canTake=openMajor[curSemester] & ~takenMajor;
    for(int i=0;i<majorCount;i++){
        if((canTake & (1<<i)) && !isListenable(i, takenMajor)){
            canTake=canTake & ~(1<<i);
        }
    }
    for(int take=canTake;take;take=((take-1) & canTake)){
        if(bitCount(take)>maxListen) continue;
        minSemester=min(minSemester,1+graduate(curSemester+1, takenMajor | take));
    }
    return minSemester=min(minSemester, graduate(curSemester+1, takenMajor));
}

int main(){
    int testCase;
    cin >> testCase;
    while(testCase--){
        init();
        cin >> majorCount >> listenCount >> semesterCount >> maxListen;
        for(int i=0;i<majorCount;i++){
            int beforeCount;
            cin >> beforeCount;
            for(int j=0;j<beforeCount;j++){
                int b;
                cin >> b;
                before[i]=before[i] | (1<<b);
            }
        }
        openMajor.resize(semesterCount);
        for(int i=0;i<semesterCount;i++){
            int openCount;
            cin >> openCount;
            openMajor[i]=0;
            for(int j=0;j<openCount;j++){
                int o;
                cin >> o;
                openMajor[i]=openMajor[i] | (1<<o);
            }
        }
        int ret=graduate(0,0);
        if(ret==INF) cout << "IMPOSSIBLE"<<"\n";
        else cout << ret <<"\n";
    }
    return 0;
}