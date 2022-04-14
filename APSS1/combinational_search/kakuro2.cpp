#include <vector>
#include <iostream>
#include <string.h>

const int WHITE=1;
const int MAX_LEN=9;
const int MAX_N=20;
const int MAX_SUM=45;
const int MAX_SET=1023;
//board 정보
//color: 0=검은 or 힌트칸, 1=흰칸
//value: 각 흰 칸에 쓰인 수
//hint:각 칸에 해당하는 두 힌트의 번호
int n, color[MAX_N][MAX_N], value[MAX_N][MAX_N], hint[MAX_N][MAX_N][2];
//hint 정보
//sum: 힌트 칸에 쓰인 수
//length: 힌트 칸에 해당하는 흰 칸의 수
//known: 힌트 칸에 해당하는 흰 칸에 쓰인 숫자들의 집합
int q, sum[MAX_N*MAX_N], length[MAX_N*MAX_N], known[MAX_N*MAX_N];

int candidates[MAX_LEN+1][MAX_SUM+1][MAX_SET+1];

void init();
void generatesCandidates();
bool search();

int main(){
    int testCase;
    std::cin >> testCase;
    generatesCandidates();
    for(int i=0;i<testCase;i++){
        init();
        std::cin >> n;
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                std::cin >> color[j][k];
            }
        }
        std::cin >> q;
        for(int j=0;j<q;j++){
            int x, y, direction, s;
            std::cin >> y >> x >> direction >> s;
            x-=1;y-=1;
            hint[y][x][direction]=j;
            sum[j]=s;
            if(direction==0){//가로힌트
                int startY=y,startX=x+1;
                while(startX<n){
                    if(color[startY][startX]==WHITE){
                        hint[startY][startX][direction]=j;
                        length[j]++;
                        startX++;
                    }else break;
                }
            }else{
                int startY=y+1,startX=x;
                while(startY<n){
                    if(color[startY][startX]==WHITE){
                        hint[startY][startX][direction]=j;
                        length[j]++;
                        startY++;
                    }else break;
                }
            }
        }
        search();
    }
    return 0;
}

void init(){
    memset(color,0,sizeof(color));
    memset(value,0,sizeof(value));
    memset(hint,0,sizeof(hint));
    memset(sum,0,sizeof(sum));
    memset(length,0,sizeof(length));
    memset(known,0,sizeof(known));
}

//mask에 속한 원소들의 개수 반환
int getSize(int mask){
    int ret=0;
    for(int i=1;i<10;i++){
        if(mask & (1<<i)) ret++;
    }
    return ret;
}

//mask에 속한 원소들의 합 반환
int getSum(int mask){
    int ret=0;
    for(int i=1;i<10;i++){
        if(mask & (1<<i)) ret+=i;
    }
    return ret;
}

// //연속된 len개의 흰 칸에 적힌 수 합이 sum이여야하는데 이미 적힌 숫자의 목록이 known[]일때 남은 칸에 들어갈 수 있는 숫자들의 집합
// int getCandidates(int len, int sum, int known){
//     //조건에 부합하는 집합들의 합집합
//     int allSets=0;
//     //{1,...,9}의 부분집합을 모두 생성
//     for(int set=0;set<=MAX_SET;set+=2){ //-> 이 부분의 반복문이 속도를 느리게 한다.
//         //조건 확인
//         if((set & known)==known && getSize(set)==len && getSum(set)==sum){
//             allSets |= set;
//         }
//     }
//     return allSets & ~known;
// }

void generatesCandidates(){
    memset(candidates,0, sizeof(candidates));
    for(int set=0;set<MAX_SET+1;set+=2){
        int l=getSize(set),s=getSum(set);
        int subset=set;
        //전체가 set일 경우에 모든 known을 고려한다.
        while(true){
            candidates[l][s][subset] |= (set & ~subset);
            if(subset==0) break;
            subset=(subset-1) & set;
        }
    }
}

void putValue(int y, int x, int val){
    for(int i=0;i<2;i++){
        known[hint[y][x][i]]+=(1<<val);
    }
    value[y][x]=val;
}

void popValue(int y, int x,int val){
    for(int i=0;i<2;i++){
        known[hint[y][x][i]]-=(1<<val);
    }
    value[y][x]=0;
}

int getCandHint(int hint){
    return candidates[length[hint]][sum[hint]][known[hint]];
}

int getCandCoord(int y, int x){
    return getCandHint(hint[y][x][0]) & getCandHint(hint[y][x][1]);
}

void printSolution(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            std::cout << value[i][j] <<" ";
        }
        std::cout <<"\n";
    }
}

bool search(){
    int x=-1,y=-1,minCands=1023;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(color[i][j]==WHITE && value[i][j]==0){
                int cands=getCandCoord(i,j);
                if(getSize(minCands)>getSize(cands)){
                    minCands=cands;
                    y=i,x=j;
                }
            }
        }
    }
    if(minCands==0) return false;
    if(y==-1){
        printSolution();
        return true;
    }
    for(int val=1;val<=9;val++){
        if(minCands & (1<<val)){
            putValue(y,x,val);
            if(search()) return true;
            popValue(y,x,val);
        }
    }
    return false;
}