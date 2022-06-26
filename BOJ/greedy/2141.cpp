/*
수직선과 같은 일직선상에 N개의 마을이 위치해 있다. i번째 마을은 X[i]에 위치해 있으며, A[i]명의 사람이 살고 있다.
이 마을들을 위해서 우체국을 하나 세우려고 하는데, 그 위치를 어느 곳으로 할지를 현재 고민 중이다. 
고민 끝에 나라에서는 각 사람들까지의 거리의 합이 최소가 되는 위치에 우체국을 세우기로 결정하였다. 
우체국을 세울 위치를 구하는 프로그램을 작성하시오.
각 마을까지의 거리의 합이 아니라, 각 사람까지의 거리의 합임에 유의한다
*/

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int getPostofficePos(vector<int> villege, vector<int> people){
    long long signChecker=0; //거리 합 함수의 기울기가 음수인지 양수인지 체크한다.
    vector<pair<int,int>> sortedVillege;
    for(int i=0;i<villege.size();i++) sortedVillege.push_back(make_pair(villege[i],i));
    sort(sortedVillege.begin(), sortedVillege.end());
    for(int i=0;i<people.size();i++){ //위치가 0일때 체크
        signChecker+=(-people[i]);
    }
    for(int i=0;i<sortedVillege.size();i++){ //거리 합 함수의 기울기가 양수가 되면 그 이후에는 계속 증가한다.(최소점이 단 하나만 존재한다.)
        signChecker+=2*people[sortedVillege[i].second];
        if(signChecker>=0) return sortedVillege[i].first;
    }
    return -1;
}

int main(){
    int villegeCount;
    scanf("%d", &villegeCount);
    vector<int> villege(villegeCount), people(villegeCount);
    for(int i=0;i<villegeCount;i++){
        scanf("%d %d", &villege[i], &people[i]);
    }
    printf("%d\n", getPostofficePos(villege, people));
    return 0;
}