#include <algorithm>

using namespace std;

const int MAX_ROW=100;
const int MIN_INF=-987654321;
int n;
int triangle[MAX_ROW][MAX_ROW];
int path[MAX_ROW][MAX_ROW];
int cache[MAX_ROW][MAX_ROW];
int smallCache[2][MAX_ROW];

int getMaxPathSum(const int x, const int y){ //(x,y)에서 끝까지의 숫자의 합을 최대화하는 경로
    if(x>n-1 || y>n-1) return 0;
    int& ret=path[x][y];
    if(ret!=-1) return ret;
    return ret=triangle[x][y]+max(getMaxPathSum(x+1,y+1),getMaxPathSum(x,y+1));
}

int getMaxPathSumIterative(){//getMaxPathSum을 반복문으로 구현
    for(int y=0;y<n;y++){
        cache[n-1][y]=triangle[n-1][y];
    }
    for(int x=n-2;x>=0;x--){
        for(int y=0;y<x+1;y++){
            cache[x][y]=max(cache[x+1][y]+triangle[x][y],cache[x+1][y+1]+triangle[x][y]);
        }
    }
    return cache[0][0];
}

int getMaxPathSumIterative2(){//getMaxPathSumIterative의 공간복잡도 최적화한 것
     for(int y=0;y<n;y++){
        smallCache[(n-1)%2][y]=triangle[(n-1)%2][y];
    }
    for(int x=n-2;x>=0;x--){
        for(int y=0;y<x+1;y++){
            smallCache[x%2][y]=max(smallCache[(x+1)%2][y]+triangle[x][y],smallCache[(x+1)%2][y+1]+triangle[x][y]);
        }
    }
    return smallCache[0][0];
}


int getMaxPathSumCount(const int x, const int y){ //(x,y)에서 끝까지의 숫자의 합을 최대화하는 경로의 개수
    if(x>n-1 || y>n-1) return 0;
    int& ret=cache[x][y];
    if(ret!=-1) return ret;
    if(x==n-1 && y==n-1) return ret=1;
    ret=0;
    if(getMaxPathSum(x+1,y+1)>=getMaxPathSum(x,y+1)) ret+=getMaxPathSumCount(x+1,y+1);
    if(getMaxPathSum(x+1,y+1)<=getMaxPathSum(x,y+1)) ret+=getMaxPathSumCount(x,y+1);
    return ret;
}