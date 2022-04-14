#include <iostream>
#include <vector>
#include <algorithm>

const int MAX_BOARD=10;
int remainBlocks=0;
int blockSize=0;
int boardHeight, boardWidth, blockHeight, blockWidth;
std::vector<std::vector<int>> board;
std::vector<std::vector<int>> block;
std::vector<std::vector<std::pair<int,int>>> blockType;
int best=0;

int solve();

int main(){
    int testCase;
    std::cin >> testCase;
    for(int i=0;i<testCase;i++){
        std::cin >> boardHeight >> boardWidth >> blockHeight >> blockWidth;
        board.resize(boardHeight);
        block.resize(blockHeight);
        for(int j=0;j<boardHeight;j++){
            for(int k=0;k<boardWidth;k++){
                char c;
                std::cin >> c;
                if(c=='#') board[j].push_back(1);
                else{
                    board[j].push_back(0);
                    remainBlocks++;
                }
            }
        }
        for(int j=0;j<blockHeight;j++){
            for(int k=0;k<blockWidth;k++){
                char c;
                std::cin >> c;
                if(c=='#'){
                    block[j].push_back(1);
                    blockSize++;
                }
                else block[j].push_back(0);
            }
        }
        std::cout << solve() << "\n";
        block.resize(0);
        board.resize(0);
        blockType.resize(0);
        best=0;remainBlocks=0;blockSize=0;
    }
    return 0;
}

std::vector<std::vector<int>> rotate(std::vector<std::vector<int>> square){
    std::vector<std::vector<int>> ret(square[0].size(),std::vector<int>(square.size(),0));
    for(int i=0;i<square.size();i++){
        for(int j=0;j<square[i].size();j++){
            ret[j][square.size()-1-i]=square[i][j];
        }
    }
    return ret;
}

std::vector<std::vector<std::pair<int,int>>> makeBlockType(){
    std::vector<std::vector<std::pair<int,int>>> ret(4);
    for(int type=0;type<4;type++){
        int startX=-1,startY=-1;
        for(int i=0;i<block.size();i++){
            for(int j=0;j<block[i].size();j++){
                if(block[i][j]==1){
                    if(startX==-1){
                        startX=i;
                        startY=j;
                    }
                    ret[type].push_back(std::make_pair(i-startX,j-startY));
                }
            }
        }
        block=rotate(block);
    }
    std::sort(ret.begin(),ret.end());
    ret.erase(std::unique(ret.begin(),ret.end()),ret.end());
    return ret;
}

bool isInRange(int x, int y){
    if((x<0) || (x>=boardHeight) || (y<0) || (y>=boardWidth)) return false;
    return true;
}

bool insertBlock(int x, int y, int type){
    for(int i=0;i<blockType[type].size();i++){
        if(isInRange(x+blockType[type][i].first,y+blockType[type][i].second) && board[x+blockType[type][i].first][y+blockType[type][i].second]==0){
            board[x+blockType[type][i].first][y+blockType[type][i].second]=1;
        }else return false;
    }
    return true;
}

void deleteBlock(int x,int y, int type){
    for(int i=0;i<blockType[type].size();i++){
        if(isInRange(x+blockType[type][i].first,y+blockType[type][i].second)) board[x+blockType[type][i].first][y+blockType[type][i].second]=0;
    }
}

bool blockPrune(int placed) //가지치기
{

        int cnt = 0;

        for (int i = 0; i < boardHeight; i++)

               for (int j = 0; j < boardWidth; j++)

                       cnt += (board[i][j]==0) ? 1 : 0;

        return ((cnt / blockSize) + placed <= best);

}

void countCover(int placed){
    if(blockPrune(placed)) return;
    int startX=-1,startY=-1;
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j]==0){
                startX=i;
                startY=j;
                break;
            }
        }
        if(startX!=-1) break;
    }
    if(startX==-1){
        std::cout << best << placed<<remainBlocks<<"\n";
        best=std::max(best,placed);
        return;
    }
    int count=0;
    //이 칸을 덮는 경우
    for(int type=0;type<blockType.size();type++){
        if(insertBlock(startX,startY,type)){
            remainBlocks-=blockSize;
            countCover(placed+1);
            remainBlocks+=blockSize;
        }
        deleteBlock(startX, startY, type);
    }
    //이 칸을 덮지 않는 경우
    board[startX][startY]=1;
    countCover(placed);
    board[startX][startY]=0;
}

int solve(){
    blockType=makeBlockType();
    countCover(0);
    return best;
}