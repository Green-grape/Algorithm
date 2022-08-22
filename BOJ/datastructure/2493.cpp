#include <stack>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solve(stack<int> towers){
    vector<int> ret(towers.size()+1,0);
    stack<pair<int,int>> temp;
    while(!towers.empty()){
        int lastHeight=towers.top();
        int lastIdx=towers.size();
        towers.pop();

        while(!temp.empty()){
            pair<int,int> unChecked=temp.top();
            if(unChecked.second>lastHeight) break;
            temp.pop();
            ret[unChecked.first]=lastIdx;
        }
        temp.push(make_pair(lastIdx,lastHeight));
    }
    return ret;
}

int main(){
    int towerCount;
    scanf("%d", &towerCount);
    stack<int> towers;
    for(int i=0;i<towerCount;i++){
        int height;
        scanf("%d", &height);
        towers.push(height);
    }
    vector<int> ret=solve(towers);
    for(int i=1;i<ret.size();i++){
        cout << ret[i] <<" ";
    }
    return 0;
}