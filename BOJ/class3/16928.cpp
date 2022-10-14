#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

map<int, int> goFront;
map<int, int> goBack;

const int BLOCK_COUNT=100;
const int START=1;

int move(int block){
    if(goFront.find(block)!=goFront.end()) return goFront[block];
    if(goBack.find(block)!=goBack.end()) return goBack[block];
    return block;
}

int bfs(){
    vector<int> isVisit(BLOCK_COUNT+1);
    queue<pair<int,int>> q;
    q.push(make_pair(START,1));
    isVisit[START]=1;
    int ret=101;
    while(!q.empty()){
        pair<int,int> f=q.front();
        int cur=f.first;
        int depth=f.second;
        q.pop();
        for(int block=cur+1;block<=cur+6 && block<=BLOCK_COUNT;block++){
            int next=move(block);
            if(block==BLOCK_COUNT){
                ret=min(ret, depth);
            }
            if(isVisit[next]) continue;
            isVisit[next]=1;
            q.push(make_pair(next,depth+1));
        }
    }
    return ret;
}

int main(){
    int goFrontCount, goBackCount;
    cin >> goFrontCount >> goBackCount;
    for(int i=0;i<goFrontCount;i++){
        int b1,b2;
        cin >> b1 >> b2;
        goFront[b1]=b2;
    }
    for(int i=0;i<goBackCount;i++){
        int b1,b2;
        cin >> b1 >> b2;
        goBack[b1]=b2;
    }
    cout <<bfs() <<"\n";
    return 0;
}