/* nxm의 0, 1로 된 배열이 있다. (1<=n,m<=1000)
이 배열에서 1로 된 가장 큰 정사각형의 크기를 구하는 프로그램을 작성하시오. */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAXN=1000;

int n,m;

vector<vector<int>> sumUntil;
vector<vector<int>> board(MAXN,vector<int>(MAXN));

void precal(){
    sumUntil=board;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(j>0) sumUntil[i][j]+=sumUntil[i][j-1];
            if(i>0) sumUntil[i][j]+=sumUntil[i-1][j];
            if(i>0 && j>0) sumUntil[i][j]-=sumUntil[i-1][j-1];
        }
    }
}

int sumRange(int x1, int y1, int x2, int y2){
    int ret=sumUntil[y2][x2];
    if(y1>0) ret-=sumUntil[y1-1][x2];
    if(x1>0) ret-=sumUntil[y2][x1-1];
    if(x1>0 && y1>0) ret+=sumUntil[y1-1][x1-1];
    return ret;
}

int getLargestSquare(){
    int maxside=min(n,m);
    for(int side=maxside;side>0;side--){
        int surface=side*side;
        bool isExist=false;
        for(int i=0;i<=n-side;i++){
            for(int j=0;j<=m-side;j++){
                if(surface==sumRange(j,i,j+side-1,i+side-1)) isExist=true;
            }
        }
        if(isExist) return surface;
    }
    return 0;
}

int main(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        string nums;
        cin >> nums;
        for(int j=0;j<nums.length();j++){
            board[i][j]=stoi(string(1,nums[j]));
        }
    }
    precal();
    cout << getLargestSquare() <<"\n";
    return 0;
}