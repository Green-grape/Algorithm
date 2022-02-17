#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;

vector<vector<int>> adj={
    {},
    {2},      //  vertex: 1 
    {3},      //  vertex: 2
    {1},      //  vertex: 3
    {2,5},    //  vertex: 4
    {7},      //  vertex: 5
    {5},      //  vertex: 6
    {6}       //  vertex: 7
};

vector<int> sccId; //정점들의 sccId
vector<int> discovered;//정점들의 발견순서
stack<int> s;
int sccCounter,vertexCounter;

vector<int> tarjanSCC();

int main(){
    tarjanSCC();
    for(int i=0;i<sccId.size();i++){
        cout <<sccId[i]<<" ";  
    }
    return 0;
}

//반환값:vertex에서 갈수 있는 정점중에서 가장 순서가 빠른것
int dfs(const int vertex){
    int ret=discovered[vertex]=vertexCounter++;
    s.push(vertex);
    for(int i=0;i<adj[vertex].size();i++){
        int next=adj[vertex][i];
        if(discovered[next]==-1){
            ret=min(ret,dfs(next));
        }else if(sccId[next]==-1){
            ret=min(ret,discovered[next]);
        }
    }
    if(ret==discovered[vertex]){
        while(true){
            int t=s.top();
            s.pop();
            sccId[t]=sccCounter;
            if(t==vertex) break;
        }
        ++sccCounter;
    }
    return ret;
}

vector<int> tarjanSCC(){
    sccId=discovered=vector<int>(adj.size(),-1);
    sccCounter=vertexCounter=0;
    for(int i=1;i<adj.size();i++){
        if(discovered[i]==-1) dfs(i);
    }
    return sccId;
}