#include <iostream>
#include <vector>

using namespace std;

struct Square{
    int startY, startX, endY, endX;
    Square(int _startY, int _startX, int _endY, int _endX):startY(_startY), startX(_startX), endY(_endY), endX(_endX){}
};

//직사각형을 나눈다.
pair<Square,Square> splitSquare(Square& s, int dir, int line){
    if(dir==0){
        Square up=Square(s.startY,s.startX,line,s.endX);
        Square down=Square(line, s.startX, s.endY, s.endX);
        return {up,down};
    }else{
        Square left=Square(s.startY, s.startX, s.endY, line);
        Square right=Square(s.startY, line, s.endY, s.endX);
        return {left,right};
    }
}

vector<Square> cutSquares(vector<Square>& squares, int dir, int line){
    vector<Square> ret;
    for(int i=0;i<squares.size();i++){
        if((dir==0 && squares[i].startY<line && line<squares[i].endY) || (dir==1 && squares[i].startX<line && line<squares[i].endX)){ //x방향으로 자름
            pair<Square,Square> splited=splitSquare(squares[i],dir,line);
            ret.push_back(splited.first);
            ret.push_back(splited.second);
        }else{
            ret.push_back(squares[i]);
        }
    }
    return ret;
}

int getMaxArea(vector<Square>& squares){
    int ret=0;
    for(int i=0;i<squares.size();i++){
        ret=max(ret, (squares[i].startY-squares[i].endY)*(squares[i].startX-squares[i].endX));
    }
    return ret;
}

int main(){
    int endY, endX;
    cin >> endX >> endY;
    vector<Square> squares;
    squares.push_back(Square(0,0,endY,endX));
    int cutCnt;
    cin >> cutCnt;
    for(int i=0;i<cutCnt;i++){
        int dir, line;
        cin >> dir >> line;
        squares=cutSquares(squares,dir,line);
    }
    cout << getMaxArea(squares)<<"\n";
    return 0;
}