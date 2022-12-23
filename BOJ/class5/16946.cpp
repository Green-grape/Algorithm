#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> zeroCnt; //zeroCnt[y][x]=(y,x)에서 dfs를 했을때 0의 개수
vector<string> board;
vector<vector<pair<int,int>>> parent;
vector<vector<bool>> isVisit;
const int adj[][2]={
    {0,-1},{0,1},{-1,0},{1,0}
};

void dfs(int y, int x, int pY, int pX){
    if(isVisit[y][x]) return;
    isVisit[y][x]=true;
    parent[y][x]={pY,pX};
    zeroCnt[pY][pX]++;
    for(int i=0;i<4;i++){
        int nextY=y+adj[i][0],nextX=x+adj[i][1];
        if(nextX<0 || board[0].size()<=nextX || nextY<0 || board.size()<=nextY) continue;
        if(board[nextY][nextX]=='1') continue;
        dfs(nextY,nextX, pY, pX);
    }
}
void precal(){
    parent=vector<vector<pair<int,int>>>(board.size(),vector<pair<int,int>>(board[0].size()));
    zeroCnt=vector<vector<int>>(board.size(), vector<int>(board[0].size()));
    isVisit=vector<vector<bool>>(board.size(),vector<bool>(board[0].size()));
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j]=='0' && !isVisit[i][j]) dfs(i,j,i,j);
        }
    }
}

vector<vector<int>> solve(){
    precal();
    vector<vector<int>> ret(board.size());
    for(int i=0;i<board.size();i++){
        ret[i].resize(board[i].size());
        for(int j=0;j<board[i].size();j++){
            if(board[i][j]!='0'){
                ret[i][j]=1;
                vector<pair<int,int>> usedP;
                for(int k=0;k<4;k++){
                    int nextY=i+adj[k][0],nextX=j+adj[k][1];
                    if(nextX<0 || board[0].size()<=nextX || nextY<0 || board.size()<=nextY) continue;
                    if(board[nextY][nextX]=='1') continue;
                    bool flag=false;
                    for(int n=0;n<usedP.size();n++){
                        if(usedP[n]==parent[nextY][nextX]){
                            flag=true;
                            break;
                        }
                    }
                    if(!flag){
                        usedP.push_back(parent[nextY][nextX]);
                        ret[i][j]=(ret[i][j]%10+zeroCnt[parent[nextY][nextX].first][parent[nextY][nextX].second]%10)%10;
                    }
                }
            }
        }
    }
    return ret;
}

int main(){
    int n,m;
    cin >> n >> m;
    board.resize(n);
    for(int i=0;i<n;i++){
        cin >> board[i];
    }
    vector<vector<int>> ret=solve();
    for(int i=0;i<ret.size();i++){
        for(int j=0;j<ret[i].size();j++){
            printf("%d",ret[i][j]);
        }
        printf("\n");
    }
    return 0;
}