/*극대 안정 집합: 더 이상 원소를 추가할 수 없는 집합*/
/*전체 집합이 주어질때 극대 안정 집합의 개수는?*/
//ex) A,B와 C,D가 공존 불가할때 극대 안정 집합의 개수=4 {A,C} {A,D} {B,C} {B,D}

const int MAXN=30;
int n;
int explodes[MAXN]; //explode[i]= i번째 원소와 같이 두면 안되는 원소

bool isStable(int set){
    for(int i=0;i<n;i++){
        if((set & (1<<i)) && (set & explode[i])) return false; //for문 하나를 지워서 속도 상승
    }
    return true;
}

int countStable(){
    int ret=0;
    int setCount=(1<<n);
    for(int set=1;set<setCount;set++){
        if(!isStable(set)) continue;
        bool isCanExtend=false;
        for(int add=0;add<n;add++){
            if((set & (1<<add))==0 && (explodes[add] & set)==0){
                isCanExtend=true;
            }
            if(isCanExtend) break;
        }
        if(!isCanExtend) ret++;
    }
    return ret;
}