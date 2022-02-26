/*
간단한 BFS의 구현
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//bfs를 방문한 순서를 반환한다.
vector<int> bfs(int start, vector<vector<int>> adj){
    vector<bool> isDiscovered(adj.size(),false);
    queue<int> q;
    vector<int> ret;
    isDiscovered[start]=true;
    q.push(start);
    while(!q.empty()){
        int i=q.front();
        ret.push_back(i);
        q.pop();
        for(int j=0;j<adj[i].size();j++){
            int next=adj[i][j];
            if(!isDiscovered[next]) q.push(next);
            isDiscovered[next]=true;
        }
    }
    return ret;
}