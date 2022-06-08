/*
흑백 영상을 압축하여 표현하는 데이터 구조로 쿼드 트리(Quad Tree)라는 방법이 있다. 
흰 점을 나타내는 0과 검은 점을 나타내는 1로만 이루어진 영상(2차원 배열)에서 같은 숫자의 점들이 한 곳에 많이 몰려있으면, 쿼드 트리에서는 이를 압축하여 간단히 표현할 수 있다.
주어진 영상이 모두 0으로만 되어 있으면 압축 결과는 "0"이 되고, 모두 1로만 되어 있으면 압축 결과는 "1"이 된다. 
만약 0과 1이 섞여 있으면 전체를 한 번에 나타내지를 못하고, 왼쪽 위, 오른쪽 위, 왼쪽 아래, 오른쪽 아래, 이렇게 4개의 영상으로 나누어 압축하게 되며, 이 4개의 영역을 압축한 결과를 차례대로 괄호 안에 묶어서 표현한다
2차원 배열은 NxN이며 (1<=N<=64)
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> board;

string compressQurdTree(int x0,int y0,int x1,int y1){ //(x0,y0)~(x1,y1)을 압축한 quadtree를 반환한다.
    if(x0==x1 && y0==y1) return string(1,board[x0][y0]);
    int midX=(x0+x1)/2, midY=(y0+y1)/2;
    string leftTop=compressQurdTree(x0,y0,midX,midY);
    string rightTop=compressQurdTree(x0,midY+1,midX,y1);
    string leftBottom=compressQurdTree(midX+1,y0,x1,midY);
    string rightBottom=compressQurdTree(midX+1,midY+1,x1,y1);
    if(leftTop==rightTop && rightTop==leftBottom && leftBottom==rightBottom && leftTop.length()==1) return leftTop;
    return "("+leftTop+rightTop+leftBottom+rightBottom+")";
}

int main(){
    int n;
    cin >> n;
    board.resize(n);
    for(int i=0;i<n;i++){
        cin >> board[i];
    }
    cout << compressQurdTree(0,0,n-1,n-1) <<"\n";
    return 0;
}

