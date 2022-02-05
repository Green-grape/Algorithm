#include <iostream>
#include <vector>
#include <algorithm>

vector<vector<int>> adjacent;

//circuit에 EulerCircle의 역순이 삽입된다.
void getEulerCircuit(const int vertex, vector<int>& circuit){
    for(int i=0;i<adjacent[vertex].size();i++){
        while(adjacent[vertex][i]!=0){
            adjacent[vertex][i]--;
            adjacent[i][vertex]--;
            setEulerCircuit(i,circuit);
        }
    }
    //circuit에는 vertex의 이후의 점들이 이미 등록이 되어있다. -> why? 
    //vertex에서 갈 수 있는 모든 점들이 이미 circuit에 추가가 되어있다. while문 때문에
    //vertex만 추가해주면 EulerCircle의 vertex~end의 점들이 역순으로 추가되어있다.
    circuit.push_back(vertex);
    
}

//start->end로 가면서 모든 간선을 지나는 경로인 EulerTrail 구하기
//end->start로 간선을 추가한 후 start->start의 EulerCircuit을 구한후 end->start 제거

vector<int> mergeVector(vector<int> front, vector<int> back){
    vector<int> res;
    res.reserve(front.size()+back.size());
    res.insert(res.end(),front.begin(),front.end());
    res.insert(res.end(),back.begin(),back.end());
    return res;
}

vector<int> removeEdge(const int start, const int end, vector<int>& trail){
    for(int i=1;i<trail.size();i++){
        if((trail[i-1]==start && trail[i]==end) || (trail[i-1]==end && trail[i]==start)){
            vector<int> frontTrail=vector<int>(trail.begin(), trail.begin()+i-1);
            vector<int> backTrail;
            if(trail.begin()+i+1==trail.end()) backTrail=vector<int>();
            else backTrail=vector<int>(trail.begin()+i+1,trail.end());
            return mergeVector(frontTrail,backTrail);
        }
    }
}

vector<int> getEulerTrail(const int start, const int end, vertor<int>& trail){
    //addEdge
    adjacent[start][end]++;
    adjacent[end][start]++;
    getEulerCircuit(start, trail);
    reverse(trail.begin(),trail.end());
    return removeEdge(start,end,trail);
}