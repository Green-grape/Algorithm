/*
N×N 게임판에 수가 적혀져 있다. 이 게임의 목표는 가장 왼쪽 위 칸에서 가장 오른쪽 아래 칸으로 규칙에 맞게 점프를 해서 가는 것이다.
각 칸에 적혀있는 수는 현재 칸에서 갈 수 있는 거리를 의미한다. 반드시 오른쪽이나 아래쪽으로만 이동해야 한다. 0은 더 이상 진행을 막는 종착점이며, 항상 현재 칸에 적혀있는 수만큼 오른쪽이나 아래로 가야 한다. 
한 번 점프를 할 때, 방향을 바꾸면 안 된다. 즉, 한 칸에서 오른쪽으로 점프를 하거나, 아래로 점프를 하는 두 경우만 존재한다.
가장 왼쪽 위 칸에서 가장 오른쪽 아래 칸으로 규칙에 맞게 이동할 수 있는 경로의 개수를 구하는 프로그램을 작성하시오.
N (4 ≤ N ≤ 100), 0<=이동칸의 값<=9 (0은 종착점)
*/
#include <stdio.h>
#include <string.h>
const int MAXN=100;

int board[MAXN][MAXN];
long long cache[MAXN][MAXN];
int n;

long long pathCount(int x, int y){ //(x,y)로부터 아래 끝까지 갈 수 있는 경우의 수
    if(x==n-1 && y==n-1) return 1;
    if(x>n-1 || y>n-1) return 0;
    long long& ret=cache[x][y];
    if(ret!=-1) return ret;
    ret=0;
    ret+=pathCount(x+board[x][y],y);
    ret+=pathCount(x,y+board[x][y]);
    return ret;
}

long long solve(){
    memset(cache,-1,sizeof(cache));
    return pathCount(0,0);
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&board[i][j]);
        }
    }
    printf("%lld\n", solve());
    return 0;
}