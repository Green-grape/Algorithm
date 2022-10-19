#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

//string append 와 stoi는 생각보다 매우 느리다라는 것을 주의하자

using namespace std;

const int MAXN=10000;

int calD(int num){
    return (num*2)%MAXN;
}

int calS(int num){
    return (num-1+MAXN)%MAXN;
}

int calL(int num){
    return (num%1000)*10+num/1000;
}

int calR(int num){
    return (num%10)*1000+num/10;
}

pair<int,char> calculator(int num, int idx){
    switch (idx)
    {
    case 0:
        return make_pair(calD(num),'D');
    case 1:
        return make_pair(calL(num),'L');
    case 2:
        return make_pair(calR(num),'R');
    case 3:
        return make_pair(calS(num),'S');
    default:
        return make_pair(0,' ');
    }
}

vector<pair<int,char>> before(MAXN+1);

void getMinCal(int start, int target){
    vector<int> isVisit(MAXN+1);
    queue<int> q;
    q.push(start);
    isVisit[start]=1;
    if(target==start) return;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            pair<int,char> temp=calculator(cur,i);
            int next=temp.first;
            if(!isVisit[next]){
                before[next]=make_pair(cur,temp.second);
                isVisit[next]=1;
                if(next==target) return;
                q.push(next);
            }
        }
    }
}

string reconstruct(int cur, int end){
    if(cur==end) return "";
    pair<int, char> bef=before[cur];
    return reconstruct(bef.first,end)+bef.second;
}

string solve(int start, int target){
    getMinCal(start, target);
    return reconstruct(target, start);
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase>0){
        int cur, target;
        scanf("%d %d", &cur, &target);
        string ret=solve(cur,target);
        cout << ret <<"\n";
        testcase--;
        before.clear();
    }
    return 0;
}