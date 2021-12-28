#include <iostream>
#include <vector>
#include <string>

using namespace std;
int board[20][20]={0,};
const int blockType[4][3][2]={
    {{0,0},{1,0},{0,1}},
    {{0,0},{1,0},{1,1}},
    {{0,0},{0,1},{1,1}},
    {{0,0},{-1,1},{0,1}}
};
int boardHeight;
int boardWidth;
int remainBlock=0;

int countCover();

int main(){
    int testCase;
    string temp;
    vector<int> results;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        cin >> boardHeight >> boardWidth;
        for(int j=0;j<boardHeight;j++){
            cin >> temp;
            for(int k=0;k<boardWidth;k++){
                if(temp[k]=='#') board[k][j]=1;
                else remainBlock++;
            }
        }
        results.push_back(countCover());
        //reinitialize
        for(int j=0;j<20;j++){
            for(int k=0;k<20;k++){
                board[j][k]=0;
            }
        }
        remainBlock=0;
    }
    for(vector<int>::iterator iter=results.begin();iter!=results.end();iter++){
        cout << *iter << "\n";
    }
    return 0;
}

bool isInRange(int x, int y){
    if((x<0) || (x>=boardWidth) || (y<0) || (y>=boardHeight)) return false;
    return true;
}

//L모양블럭을 넣는데 성공하면 해당 blockX & blockY의 index, 아니면 -1
//L모양블럭을 x,y을 포함하게 넣을 수 있는지 확인

bool insertBlock(int x,int y, int i){
    int block1X=x+blockType[i][1][0],block1Y=y+blockType[i][1][1];
    int block2X=x+blockType[i][2][0],block2Y=y+blockType[i][2][1];
    if(isInRange(block1X,block1Y) && isInRange(block2X, block2Y)){
        if(board[block1X][block1Y]==0 && board[block2X][block2Y]==0){
            board[block1X][block1Y]=1;
            board[block2X][block2Y]=1;
            board[x][y]=1;
            remainBlock-=3;
            return true;
        }
    }
    return false;     
}

void deleteBlock(int x, int y, int i){
    int block1X=x+blockType[i][1][0],block1Y=y+blockType[i][1][1];
    int block2X=x+blockType[i][2][0],block2Y=y+blockType[i][2][1];
    board[block1X][block1Y]=0;
    board[block2X][block2Y]=0;
    board[x][y]=0;
    remainBlock+=3;
}

int countCover(){
    //기저 사례
    if(remainBlock%3!=0) return 0;
    if(remainBlock==0) return 1;
    int x=-1,y=-1;
    for(int i=0;i<boardHeight;i++){
        for(int j=0;j<boardWidth;j++){
            if(board[j][i]==0){
                x=j;
                y=i;
                break;
            }
        }
        if(x!=-1) break;
    }
    int count=0;
    for(int i=0;i<4;i++){
        if(insertBlock(x,y,i)){
            count+=countCover();
            deleteBlock(x,y,i);
        }
    }
    return count;
}