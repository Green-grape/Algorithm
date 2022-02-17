/*
주어진 팀들이 모두 같은 날에 월간회의 또는 주간회의 둘 중 하나를 하려고 한다.
이때 가능하다면 시간 순으로 팀 명 & 회의 시간을 출력하고 
불가능하다면 'IMPOSSIBLE'를 출력한다.
*/

#include <iostream>
#include <vector>

using namespace std;

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int teamCount;
        cin >> teamCount;
        vector<pair<int,int>> meetingTimes;
        meetingTimes.resize(teamCount*2);
        for(int j=0;j<teamCount;j++){
            int s0,e0,s1,e1;
            cin >> s0 >> e0 >> s1 >> e1;
            meetingTimes[2*j]=make_pair(s0,e0);
            meetingTimes[2*j+1]=make_pair(s1,e1);
        }
    }
}

bool isJoint(pair<int,int> a, pair<int,int> b){
    return !(a.second<=b.first || b.second<=a.first);
}

/*
주간회의와 월간회의 둘 중 '하나'만 한다는 것에 집중하면
!주간회의 시행->월간회의 시행 or !월간회의 시행->주간회의 시행으로 함의 그래프를 생성할 수 있다.
*/  
vector<vector<int>> makeGraph(const vector<pair<int,int>>& meetingTimes){ 
    vector<vector<int>> adj=vector<vector<int>>(meetingTimes.size()*2,vector<int>());
    for(int i=0;i<meetingTimes.size();i+=2){
        //회의는 i or j
        //i에 대해서 2i는 시행, 2i+1는 시행x를 의미한다.
        int j=i+1;
        adj[2*j+1].push_back(2*i); // ~j->i
        adj[2*i+1].push_back(2*j); // ~i->j
    }
    //시간이 겹칠 경우
    for(int i=0;i<meetingTimes.size();i++){
        int j=i+1;
        if(isJoint(meetingTimes[i],meetingTimes[j])){
            adj[2*i].push_back(2*j+1);
            adj[2*j].push_back(2*i+1);
        }
    }
    return adj;
}