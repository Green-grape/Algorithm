#include <queue>
#include <vector>
#include <iostream>

using namespace std;

int main(){
    int n,k;
    queue<int> q;
    cin >> n >> k;
    for(int i=1;i<=n;i++) q.push(i);
    int popCount=0;
    vector<int> ret;
    while(!q.empty()){
        if(popCount==k-1){
            ret.push_back(q.front());
            q.pop();
            popCount=0;
            continue;
        }
        int front=q.front();
        q.pop();
        q.push(front);
        popCount++;
    }
    cout << "<";
    for(int i=0;i<ret.size();i++){
        cout <<ret[i];
        if(i!=ret.size()-1) cout <<", ";
    }
    cout <<">";
    return 0;
}