#include <cstdio>
#include <string>
#include <map>
#include <iostream>

using namespace std;

map<int,int> dualPriorityQueue; //이중우선순위 큐

void insert(int num){
    if(dualPriorityQueue.find(num)==dualPriorityQueue.end()) dualPriorityQueue[num]=1;
    else{
        int cur=dualPriorityQueue[num];
        dualPriorityQueue[num]=cur+1;
    }
}

void pop(int opt){
    if(dualPriorityQueue.empty()) return;
    if(opt==1){
        pair<int,int> maxPriority=(*(dualPriorityQueue.rbegin()));
        //printf("%d %d", maxPriority.first, maxPriority.second);
        if(maxPriority.second==1) dualPriorityQueue.erase(maxPriority.first);
        else dualPriorityQueue[maxPriority.first]=maxPriority.second-1;
    }else if(opt==-1){
        pair<int,int> minPriority=(*(dualPriorityQueue.begin()));
        //printf("%d %d", minPriority.first, minPriority.second);
        if(minPriority.second==1) dualPriorityQueue.erase(minPriority.first);
        else dualPriorityQueue[minPriority.first]=minPriority.second-1;
    }
}

int main(){
    int testCase;
    scanf("%d", &testCase);
    char input[100];
    while(testCase--){
        dualPriorityQueue.clear();
        int operationCount;
        scanf("%d", &operationCount);
        for(int i=0;i<operationCount;i++){
            getchar();
            scanf("%[^\n]s",input);
            char opt=input[0];
            string num=input;
            num=num.substr(2);
            if(opt=='I') insert(stoi(num));
            else if(opt=='D'){
                pop(stoi(num));
            }
            //cout << "i:"<< i<<"\n";
        }
        if(dualPriorityQueue.empty()){
            cout << "EMPTY" <<"\n";
        }else{
            int maxPriority=(*(dualPriorityQueue.rbegin())).first;
            int minPriority=(*(dualPriorityQueue.begin())).first;
            cout << maxPriority <<" "<<minPriority<<"\n";
        }
    }
    return 0;
}