#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int MAXN=30;
const int MAXW=40000;
int cache[MAXW+1][MAXN+2]={0,};

vector<int> weights;
vector<bool> isCanMake(MAXW+1);

//이전 무게가 prevWeight이고 현재 계산하려는 추가 cur일때
void precal(int prevWeight, int cur){
    if(cur==weights.size()){
        if(0<prevWeight && prevWeight<=MAXW) isCanMake[prevWeight]=true;
        return;
    }
    if(cache[prevWeight][cur]!=0) return;
    cache[prevWeight][cur]=1;
    isCanMake[prevWeight]=true;
    if(0<prevWeight+weights[cur] && prevWeight+weights[cur]<=MAXW) precal(prevWeight+weights[cur],cur+1);
    if(0<prevWeight-weights[cur] && prevWeight-weights[cur]<=MAXW) precal(prevWeight-weights[cur],cur+1);
    if(0<-prevWeight+weights[cur] && -prevWeight+weights[cur]<=MAXW) precal(-prevWeight+weights[cur],cur+1);
    precal(prevWeight,cur+1);
}

int main(){
    int weightCnt;
    cin >> weightCnt;
    weights.resize(weightCnt+1);
    for(int i=1;i<=weightCnt;i++) cin >> weights[i];
    precal(0,0);
    int checkCnt;
    cin >> checkCnt;
    for(int i=0;i<checkCnt;i++){
        int w;
        cin >> w;
        if(isCanMake[w]) cout <<"Y"<<" ";
        else cout <<"N"<<" ";
    }
    return 0;
}