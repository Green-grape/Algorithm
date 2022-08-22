/*
원 이동하기 2 문제를 만들고 만든 데이터가 문제의 조건에 맞는지 확인하는 코드를 작성해야한다.

해당 문제의 데이터는 아래 조건들을 만족해야한다.

모든 원의 중심 좌표는 x축 위에 존재해야 한다.
N개의 원 중 임의의 두 원을 선택했을 때, 교점이 존재하지 않아야 한다. 즉, 하나의 원이 다른 원 안에 존재하거나 외부에 존재한다.
데이터 형식은 원의 개수 $N$이랑 각 원의 중심 x좌표, 원의 반지름 r만 주어진다. 따라서, 2번 조건을 만족하는지만 확인하면 된다.

주어진 데이터가 해당 조건을 만족하는지 확인해보자.
*/

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>

const int INF=987654321;
using namespace std;

//occupy[i].first<=occupy[i+1].first 가정
bool isIntersect(vector<pair<int,int>> occupy){
    int left=-INF,right=-INF,n=occupy.size();
    int lastRight=-INF;
    for(int i=0;i<n;i++){
        if(right<occupy[i].first){ //새로운 구간
            left=occupy[i].first;
            right=occupy[i].second;
        }
        else{ 
            if(left<occupy[i].first && occupy[i].second<right){
                if(occupy[i].first<=lastRight && lastRight<=occupy[i].second) return true;
                lastRight=occupy[i].second;
            }
            else return true;
        }
    }
    return false;
}

int main(){
    int circleCount;
    scanf("%d", &circleCount);
    vector<pair<int,int>> occupy; //i번째 원이 차지한 구간
    for(int i=0;i<circleCount;i++){
        int cen, r;
        scanf("%d %d", &cen, &r);
        occupy.push_back(make_pair(cen-r,cen+r));
    }
    sort(occupy.begin(),occupy.end());
    if(isIntersect(occupy)) cout << "NO" <<"\n";
    else cout <<"YES"<<"\n";
    return 0;
}