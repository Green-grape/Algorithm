#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

const int MAX=200;
int cows[MAX+1]; //cows[i]=i번째 방이 들어간 소
int done[MAX+1]; //done[i]=i번째 방이 차지 되었는가?
vector<vector<int>> possible; //possible[i]=i번째 소가 들어갈 수 있는 room

bool bipartiteDFS(int x){
    for(int i=0;i<possible[x].size();i++){
        int r=possible[x][i];
        if(done[r]) continue;
        done[r]=1;
        //r번째 방이 비어있거나 다른 소가 비킬 수 있는 경우
        if(cows[r]==-1 || bipartiteDFS(cows[r])){
            cows[r]=x;
            return true;
        }
    }
    return false;
}

int main(){
    int cowCount, roomCount;
    cin >> cowCount >> roomCount;
    possible=vector<vector<int>>(cowCount, vector<int>());
    memset(cows,-1,sizeof(cows));
    for(int cow=0;cow<cowCount;cow++){
        int possibleCount;
        cin >> possibleCount;
        for(int j=0;j<possibleCount;j++){
            int temp;
            cin >> temp;
            possible[cow].push_back(temp-1);
        }
    }
    int ret=0;
    for(int i=0;i<cowCount;i++){
        memset(done,0,sizeof(done));
        if(bipartiteDFS(i)) ret++;
    }
    cout << ret <<"\n";
    return 0;
}