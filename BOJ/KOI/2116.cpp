#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

class Dice{
public:
    vector<int> side;
    Dice(vector<int> side){
        this->side=side;
    }
    int getReverse(int val){
        int idx=-1;
        for(int i=0;i<side.size();i++){
            if(side[i]==val){
                idx=i;
                break;
            }
        }
        if(idx==0 || idx==side.size()-1) return side[side.size()-idx-1];
        if(idx<side.size()/2) return side[idx+2];
        else return side[idx-2];
    }
    int getMaxSide(int top){
        int bottom=getReverse(top);
        for(int i=6;i>=1;i--){
            if(i!=top && i!=bottom) return i;
        }
    }
};

vector<Dice> dices;

//이전 주사위의 꼭대기가 prev이고 현재 주사위가 cur일때
int getMaxSideSum(int prev, int cur){
    if(cur==dices.size()) return 0;
    return dices[cur].getMaxSide(prev)+getMaxSideSum(dices[cur].getReverse(prev),cur+1);
}

int solve(){
    int ret=0;
    for(int i=1;i<=6;i++){
        ret=max(ret, getMaxSideSum(i,0));
    }
    return ret;
}

int main(){
    int diceCnt;
    cin >> diceCnt;
    for(int i=0;i<diceCnt;i++){
        vector<int> side(6);
        for(int j=0;j<6;j++){
            scanf("%d", &side[j]);
        }
        dices.push_back(Dice(side));
    }
    cout << solve() <<"\n";
    return 0;
}