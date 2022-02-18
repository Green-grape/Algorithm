/*
주어진 팀들이 모두 같은 날에 월간회의 또는 주간회의 둘 중 하나를 하려고 한다.
이때 가능하다면 시간 순으로 팀 명 & 회의 시간을 출력하고 
불가능하다면 'IMPOSSIBLE'를 출력한다.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<int> sccId; //정점들의 sccId
vector<int> discovered;//정점들의 발견순서
stack<int> s;
int sccCounter,vertexCounter;

vector<int> getPossibleMeetingTimes(const vector<pair<int,int>>);

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
        vector<int> res=getPossibleMeetingTimes(meetingTimes);
        if(res.size()==0) cout << "IMPOSSIBLE"<<"\n";
        else{
            cout <<"POSSIBLE"<<"\n";
            for(int i=0;i<res.size();i++){
                if(res[i]) cout << meetingTimes[i].first <<" "<<meetingTimes[i].second<<"\n";
            }
        }
    }
    return 0;
}

bool isJoint(pair<int,int> a, pair<int,int> b){
    return !(a.second<=b.first || b.second<=a.first);
}

/*
주간회의와 월간회의 둘 중 '하나'만 한다는 것에 집중하면
!주간회의 시행->월간회의 시행 or !월간회의 시행->주간회의 시행으로 함의 그래프를 생성할 수 있다.
+ 겹치는 것을 고려하여 그래프를 짤 수 있다.
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
        for(int j=0;j<i;j++){
            if(isJoint(meetingTimes[i],meetingTimes[j])){
                adj[2*i].push_back(2*j+1);
                adj[2*j].push_back(2*i+1);
            }
        }
    }
    return adj;
}

//반환값:vertex에서 갈수 있는 정점중에서 가장 순서가 빠른것
int dfs(const int vertex, const vector<vector<int>> adj){
    int ret=discovered[vertex]=vertexCounter++;
    s.push(vertex);
    for(int i=0;i<adj[vertex].size();i++){
        int next=adj[vertex][i];
        if(discovered[next]==-1){
            ret=min(ret,dfs(next,adj));
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

vector<int> tarjanSCC(const vector<vector<int>> adj){
    sccId=discovered=vector<int>(adj.size(),-1);
    sccCounter=vertexCounter=0;
    for(int i=1;i<adj.size();i++){
        if(discovered[i]==-1) dfs(i,adj);
    }
    return sccId;
}

vector<int> getPossibleMeetingTimes(const vector<pair<int,int>> meetingTimes){
    const vector<vector<int>> adj=makeGraph(meetingTimes);
    const vector<int> sccId=tarjanSCC(adj);

    //답이 존재x
    for(int i=0;i<sccId.size();i+=2){
        if(sccId[i]==sccId[i+1]){ //같은 scc에 존재한다는 것은 둘다 월간,주간회의가 모두 참 이거나 거짓인 경우이다.
            return vector<int>();
        }
    }
    
    //답이 존재
    //sccId의 역순이 위상 정렬이라는 것을 이용한다.
    vector<pair<int,int>> order;
    for(int i=0;i<sccId.size();i++){
        order.push_back(make_pair(-sccId[i],i));
    }
    sort(order.begin(),order.end());
    
    vector<int> ret(sccId.size()/2,-1);
    for(int i=0;i<order.size();i++){
        const int meetingTimeIdx=order[i].second/2;
        if(ret[meetingTimeIdx]!=-1) continue;
        // 먼저 나온 것들 이 ~이다. 
        ret[meetingTimeIdx]=!(order[i].second%2==0);
    }
    return ret;
}