#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

vector<int> belt; //belt[i]=i번째 접시에 있는 초밥의 번호
vector<int> sushiCount; //sushiCount[i]=i번 스시가 지금 몇개 있는가

int getMaxKind(int successive, int coupon){
    //원형이므로 벨트 복제
    vector<int> temp=belt;
    belt.insert(belt.end(),temp.begin(),temp.end());
    int curKind=0;
    for(int i=0;i<successive;i++){
        if(sushiCount[belt[i]]==0){
            curKind++;
        }
        sushiCount[belt[i]]++;
    }
    int ret=curKind;
    if(sushiCount[coupon]==0) ret++;
   // cout << ret <<"\n";
    for(int i=successive;i<belt.size();i++){
        int outPos=i-successive,inPos=i;
        if(sushiCount[belt[outPos]]==1){
            curKind--;
        }
        sushiCount[belt[outPos]]--;
        if(sushiCount[belt[inPos]]==0){
            curKind++;
        }
        sushiCount[belt[inPos]]++;
        if(sushiCount[coupon]==0){
            ret=max(ret,curKind+1);
            //cout << curKind+1 <<"\n";
        }
        else{
            ret=max(ret,curKind);
            //cout << curKind <<"\n";
        } 
    }
    return ret;
}

int main(){
    int beltLength,sushiKind ,successive, coupon;
    cin >> beltLength >> sushiKind >> successive >> coupon;
    belt.resize(beltLength);
    sushiCount.resize(sushiKind+1);
    for(int i=0;i<beltLength;i++) scanf("%d", &belt[i]);
    cout << getMaxKind(successive,coupon) <<"\n";
    return 0;
}