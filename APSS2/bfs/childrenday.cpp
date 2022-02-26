/*
다음 조건을 모두 만족하는 c의 최솟값
1.n+m<=c
2.c%n==m
3.numList에 있는 숫자구만 구성됨
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

string solution(const string, const int, const int);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        string numList;
        int n,m;
        cin >> numList >> n >> m;
        cout << solution(numList, n, m) <<"\n";
    }
    return 0;
}

int nextVertex(int curNum, int nextNum, int mod){
    int next=curNum*10+nextNum;
    if(next>=mod) return mod+next%mod; //그래프를 2n으로 잡아서 m과 n+m을 구분
    return next%mod;
}
//그래프
//정점 0~n-1 n의 나머지 표현
//간선 v1->v2는 (c'modn==v1, (c'*10+x)modn==v2, x는 numList에 존재)
string solution(const string numList, const int n, const int m){
    string sortedNumList=numList;
    // 가장 작은 c값을 찾기 위해서 작은 것부터 검색
    sort(sortedNumList.begin(),sortedNumList.end());
    //parent[i]=i전에 선택된 정점, edge[i]=parent[i]->i로 갈때 선택된 간선
    vector<int> parent(2*n,-1), edge(2*n,-1);
    queue<int> q;
    q.push(0); 
    parent[0]=0;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=0;i<sortedNumList.length();i++){
            int next=nextVertex(cur,sortedNumList[i]-'0',n);
            if(parent[next]==-1){
                parent[next]=cur;
                edge[next]=sortedNumList[i]-'0';
                q.push(next);
            }
        }
    }
    if(parent[n+m]==-1) return "IMPOSSIBLE"; //2번 조건 불만족
    string ret="";
    int cur=n+m;
    while(parent[cur]!=cur){
        ret+=char(edge[cur]+'0');
        cur=parent[cur];
    }
    
    reverse(ret.begin(),ret.end());
    return ret;
}

