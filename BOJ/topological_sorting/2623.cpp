#include <iostream>
#include <vector>
#include <cstdio>
#include <set>
#include <queue>

using namespace std;

vector<int> getSequence(vector<set<int>>& prevs, vector<set<int>>& nexts){
    vector<bool> isVisit(prevs.size());
    queue<int> q;
    for(int i=1;i<prevs.size();i++){
        if(prevs[i].size()==0){
            q.push(i);
            isVisit[i]=true;
        }
    }
    vector<int> ret;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        ret.push_back(cur);
        for(set<int>::iterator it=nexts[cur].begin();it!=nexts[cur].end();it++){
            int next=(*it);
            prevs[next].erase(cur);
            if(!isVisit[next] && prevs[next].size()==0){
                q.push(next);
                isVisit[next]=true;
            }
        }
    }
    return ret;
}

int main(){
    int nodeCount, sequences;
    cin >> nodeCount >> sequences;
    vector<set<int>> prevs(nodeCount+1);
    vector<set<int>> nexts(nodeCount+1);
    for(int i=0;i<sequences;i++){
        int subNodeCount;
        cin >> subNodeCount;
        int cur, next;
        cin >> cur;
        for(int j=0;j<subNodeCount-1;j++){
            cin >> next;
            prevs[next].insert(cur);
            nexts[cur].insert(next);
            cur=next;
        }
    }
    vector<int> ret=getSequence(prevs,nexts);
    if(ret.size()==nodeCount){
        for(int i=0;i<ret.size();i++){
            cout << ret[i] <<"\n";
        }
    }
    else cout << 0 <<"\n";
    return 0;
}