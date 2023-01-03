#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int coords[][2]={
    {0,1},{0,-1},{1,0},{-1,0}
};
int n;
vector<vector<bool>> isVisit;
vector<int> parent;
vector<string> boards;

void dfs(int cur, const int& p, const bool& isHaveColorWeakness){
    int curY=cur/n, curX=cur%n, pY=p/n, pX=p%n;
    if(isVisit[curY][curX]) return;
    isVisit[curY][curX]=true;
    parent[cur]=p;
    for(int i=0;i<4;i++){
        int nextY=curY+coords[i][0], nextX=curX+coords[i][1];
        if(nextY<0 || n<=nextY || nextX<0 || n<=nextX) continue;
        if(isHaveColorWeakness){
            if(boards[curY][curX]==boards[nextY][nextX] || (boards[curY][curX]!='B' && boards[nextY][nextX]!='B')){
                dfs(nextY*n+nextX, p, isHaveColorWeakness);
            }
        }else{
            if(boards[curY][curX]==boards[nextY][nextX]){
                dfs(nextY*n+nextX,p, isHaveColorWeakness);
            }
        }
    }
}

int countArea(bool isHaveColorWeakness){
    parent=vector<int>(boards.size()*boards.size(),-1);
    isVisit=vector<vector<bool>>(boards.size(), vector<bool>(boards[0].size()));
    for(int i=0;i<boards.size();i++){
        for(int j=0;j<boards[i].size();j++){
            if(!isVisit[i][j]) dfs(i*n+j, i*n+j, isHaveColorWeakness);
        }
    }
    sort(parent.begin(), parent.end());
    parent.erase(unique(parent.begin(),parent.end()),parent.end());
    return parent.size();
}

pair<int,int> solve(){
   return {countArea(false),countArea(true)};
}

int main(){
    cin >> n;
    boards.resize(n);
    for(int i=0;i<n;i++){
        cin >> boards[i];
    }
    pair<int,int> ret=solve();
    cout << ret.first <<" "<<ret.second<<"\n";
    return 0;
}