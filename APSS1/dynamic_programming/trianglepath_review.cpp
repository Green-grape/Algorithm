#include <algorithm>

const int MAX_ROW=100;
int n;
int triangle[MAX_ROW][MAX_ROW];
int cache[MAX_ROW][MAX_ROW];

int getMaxPathSum(const int x, const int y){ //(x,y)에서 끝까지의 숫자의 합을 최대화하는 경로
    if(x>n-1 || y>n-1) return 0;
    int& ret=cache[x][y];
    if(ret!=-1) return ret;
    return ret=triangle[x][y]+max(getMaxPathSum(x+1,y+1),getMaxPathSum(x,y+1));
}