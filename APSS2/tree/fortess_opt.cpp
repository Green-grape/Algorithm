#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define MAX_WALL 100

using namespace std;

struct Wall{
    int x;
    int y;
    int r;
    bool isPushed;
    vector<Wall*> children;
    Wall(int _x, int _y, int _r): x(_x), y(_y), r(_r) {
        isPushed=false;
    }
};

struct Comparator{
    bool operator()(Wall* wall1, Wall* wall2){
        return wall1->r<wall2->r;
    }
};

int wallCount;

int getMaxWallJump(vector<Wall*>);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        cin >> wallCount;   
        vector<Wall*> walls;
        for(int j=0;j<wallCount;j++){
            int x,y,r;
            cin >> x >> y >> r;
            Wall* wall=new Wall(x,y,r);
            walls.push_back(wall);
        }
        cout << getMaxWallJump(walls)<<"\n";
    }
    return 0;
}

int getLineLength(int x1,int y1, int x2, int y2){
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

bool isParent(Wall* parent, Wall* child){
    //이미 정렬되어있으므로 직접부모인 경우를 체크 안해도 무조건 부모이다.
    return parent->r>child->r && (getLineLength(parent->x, parent->y, child->x, child->y)<parent->r-child->r);
}

//트리를 leaf에서 부터 생성
void makeTree(vector<Wall*> walls, Wall* child,int startIdx){
    for(int i=startIdx+1;i<walls.size();i++){    
        if(isParent(walls[i],child) && !child->isPushed){
            child->isPushed=true;
            walls[i]->children.push_back(child);
            makeTree(walls, walls[i],i);
            return;
        }
    }
}

int getTreeHeight(Wall* wall){
    int ret=0;
    for(int i=0;i<wall->children.size();i++){
        ret=max(ret, 1+getTreeHeight(wall->children[i]));
    }
    return ret;
}

int getMaxLeafDistance(Wall* wall){
    int primaryHeight=0;
    int secondaryHeight=0;
    for(int i=0;i<wall->children.size();i++){
        int height=1+getTreeHeight(wall->children[i]);
        if(primaryHeight<height){
            secondaryHeight=primaryHeight;
            primaryHeight=height;
        }else if(secondaryHeight<height){
            secondaryHeight=height;
        }
    }
    return primaryHeight+secondaryHeight;
}

//O(n^2)
int getMaxWallJump(vector<Wall*> walls){
    Comparator com;
    sort(walls.begin(), walls.end(), com);
    for(int i=0;i<walls.size();i++){
        makeTree(walls,walls[i],i);
    }
    return getMaxLeafDistance(walls[walls.size()-1]);
}