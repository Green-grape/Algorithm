#include <cstdio>
#include <string>
#include <string.h>
#include <set>
#include <map>
#include <iostream>

using namespace std;

set<pair<int,int>> dualPriorityQueue;
map<int,int> diff;

void add(pair<int,int> p){
    dualPriorityQueue.insert(p);
    diff[p.second]=p.first;
}

void solved(int pName){
    int d=diff[pName];
    dualPriorityQueue.erase(make_pair(d,pName));
    diff.erase(pName);
}

void recommend(int opt){
    if(dualPriorityQueue.empty()) return;
    if(opt==1){
        pair<int,int> maxPriority=(*(dualPriorityQueue.rbegin()));
        printf("%d\n", maxPriority.second);
    }else if(opt==-1){
        pair<int,int> minPriority=(*(dualPriorityQueue.begin()));
        printf("%d\n",minPriority.second);
    }
}

int main(){
    int problemCount,operationCount;
    scanf("%d", &problemCount);
    for(int i=0;i<problemCount;i++){
        int p,d;
        scanf("%d %d", &p, &d);
        diff[p]=d;
        dualPriorityQueue.insert(make_pair(d,p));
    }
    scanf("%d", &operationCount);
    for(int i=0;i<operationCount;i++){
        char op[10];
        int p,d;
        getchar();
        scanf("%s",op);
        //cout << op <<"\n";
        if(strcmp(op,"add")==0){
            scanf("%d %d",&p,&d);
            add(make_pair(d,p));
        }
        else if(strcmp(op,"solved")==0){
            scanf("%d",&p);
            solved(p);
        }
        else if(strcmp(op,"recommend")==0){
            scanf("%d",&p);
            recommend(p);
        }
        //cout <<"\n"<<"i:"<<i<<"\n";
    }
    return 0;
}