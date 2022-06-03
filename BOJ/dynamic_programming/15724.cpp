/*일정한 직사각형 범위 내에 살고 있는 사람 수를 참고 자료로 쓰고 싶어한다.
진경대왕은 굉장히 근엄한 왕이기 때문에 당신에게 4개의 숫자로 직사각형 범위를 알려줄 것이다.
이떄 직사각형 범위 내의 사람 수의 총합은?
직사각형은 N*M크기를 가지며 (N,M<=1024), 각 지역마다 사람의 수는 100명이하이다.
*/

#include <stdio.h>

const int MAX_N=1024;
int cache[MAX_N][MAX_N]={0,}; //cache[i][j]=(0,0)~(i,j)까지의 사람 수의 총합
int board[MAX_N][MAX_N];
int n,m;

void precal(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cache[i][j]=board[i][j];
            if(j>0) cache[i][j]+=cache[i][j-1];
            if(i>0) cache[i][j]+=cache[i-1][j];
            if(i>0 && j>0) cache[i][j]-=cache[i-1][j-1];
        }
    }
}

int getTotal(int x1,int y1, int x2, int y2){ //x1<=x2, y1<=y2가정
    int ret=cache[x2][y2];
    if(x1>0) ret-=cache[x1-1][y2];
    if(y1>0) ret-=cache[x2][y1-1];
    if(x1>0 && y1>0) ret+=cache[x1-1][y1-1];
    return ret;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d", &board[i][j]);
        }
    }
    precal();
    int testCase;
    scanf("%d", &testCase);
    for(int i=0;i<testCase;i++){
        int x1,y1,x2,y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        printf("%d\n", getTotal(x1-1,y1-1,x2-1,y2-1));
    }
    return 0;
}