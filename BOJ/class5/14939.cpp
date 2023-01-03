#include <iostream>
#include <vector>

const int INF=987654321;

//스위치 문제=>첫줄만 클릭해야하는가 & 칸당 몇번 클릭 가능한지 생각

using namespace std;
int coords[][2]={
    {0,0},{1,0},{-1,0},{0,1},{0,-1}
};

void click(vector<vector<bool>>& boards, int y, int x){
    for(int i=0;i<5;i++){
        int curY=y+coords[i][0],curX=x+coords[i][1];
        if(curY<0 || boards.size()<=curY || curX<0 || boards[0].size()<=curX) continue;
        boards[curY][curX]=!boards[curY][curX];
    }
}

int getMinCnt(vector<vector<bool>> boards){
    int ret=0;
    for(int i=1;i<boards.size();i++){
        for(int j=0;j<boards[i].size();j++){
            if(boards[i-1][j]){
                click(boards,i,j);
                ret++;
            }
        }
    }
    for(int i=0;i<boards.size();i++){
        for(int j=0;j<boards[i].size();j++){
            if(boards[i][j]) return INF;
        }
    }
    return ret;
}

int main(){
    vector<vector<bool>> boards(10,vector<bool>(10));
    for(int i=0;i<10;i++){
        string line;
        cin >> line;
        for(int j=0;j<line.size();j++){
            if(line[j]=='O'){
                boards[i][j]=true;
            }
        }
    }
    int ret=INF;
    for(int i=0;i<(1<<10);i++){
        vector<vector<bool>> temp=boards;
        int cand=0;
        for(int j=0;j<10;j++){
            if(i & (1<<j)){
                click(temp,0,j);
                cand++;
            }
        }
        ret=min(ret, cand+getMinCnt(temp));
    }
    if(ret==INF) cout <<-1 <<"\n";
    else cout << ret <<"\n";
    return 0;
}