#include <iostream>
#include <vector>
#include <cmath>

#define MAX_WALL 100

using namespace std;

struct Wall{
    vector<Wall*> children;
};

int x[MAX_WALL];
int y[MAX_WALL];
int r[MAX_WALL];
int wallCount;

int getMaxWallJump(int);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        cin >> wallCount;
        for(int j=0;j<wallCount;j++){
            cin >> x[j] >> y[j] >> r[j];
        }
        cout << getMaxWallJump(0) << "\n";
    }
    return 0;
}

int getLineLength(int x1,int y1, int x2, int y2){
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

bool isInside(int parent, int child){
    return (r[parent] > r[child]) && (getLineLength(x[parent],y[parent],x[child],y[child])<r[parent]-r[child]);
}

bool isChild(int parent, int child){
    if(!isInside(parent,child)) return false;
    for(int i=0;i<wallCount;i++){
        //직접적인 child가 아닌경우
        if(i!=parent && i!=child && isInside(parent,i) && isInside(i, child)){
            return false;
        }
    }
    return true;
}

Wall* makeTree(int root){
    Wall* rootWall=new Wall();
    for(int i=0;i<wallCount;i++){
        if(isChild(root,i)){
            rootWall->children.push_back(makeTree(i));
        }
    }
    return rootWall;
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

//O(n^3)
int getMaxWallJump(int root){
    Wall* rootWall=makeTree(root);
    return getMaxLeafDistance(rootWall);
}

