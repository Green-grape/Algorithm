#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

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

vector<bool> isFinished;
vector<bool> isVisited;
vector<vector<int>> sccs;
stack<int> s;

void initialize();
void tarjan();

int main(){
    initialize();
    tarjan();
    return 0;
}

void initialize(){
    isFinished=vector<bool>(adj.size(),false);
    isVisited=vector<bool>(adj.size(),false);
}

int dfs(const int vertex){
    isVisited[vertex]=true;
    int parent=vertex;
    s.push(vertex);
    for(int i=0;i<adj[vertex].size();i++){
        int next=adj[vertex][i];
        if(!isVisited[next]) parent=min(parent,dfs(next));
        else if(!isFinished[next]) parent=min(parent,next);
    }
    if(parent==vertex){
        vector<int> scc;
        int topEl=0;
        do{
            topEl=s.top();
            scc.push_back(topEl);
            s.pop();
        }while(topEl!=parent);
        sccs.push_back(scc);
    }
    isFinished[vertex]=true;
    return parent;
}


//Tip: scc가 들어가는 순서=위상정렬의 역순(dfs가 늦게 종료하는 정점부터 배열하면 그 그래프의 위상정렬인것과 비슷한 논리)
void tarjan(){
    for(int i=1;i<adj.size();i++){
        if(!isVisited[i]) dfs(i);
    }
    for(int i=0;i<sccs.size();i++){
        cout << "{";
        for(int j=0;j<sccs[i].size();j++){
            cout <<sccs[i][j];
            if(j!=sccs[i].size()-1) cout <<", ";
        }
        cout <<"}\n";
    }
}