/*피자의 토핑이 0~19번까지 번호를 가지는 스무가지 토핑이 있을때 비트마스크로 피자의 토핑을 표현*/

int fullPizza=(1<<20)-1;

//피자에 들어있는 토핑에 관한 연산(집합과 원소)
int addTopping(int pizza, int topping) {return pizza | topping;}
bool isToppingIn(int pizza, int topping) {return !((pizza & (1<<topping))==0);}
int deleteTopping(int pizza, int topping) {return pizza & ~(1<<topping);}
int toggleTopping(int pizza, int topping) {return pizza ^ (1<<topping);}

//피자까리 연산(집합과 집합)
int addPizza(int p1,int p2) {return p1 | p2;};
int intersectPizze(int p1, int p2) {return p1 & p2;};

int toppingCount(int p){
    if(p==0) return 0;
    return p%2+toppingCount(p/2);
}
//__builtin_popcount(p); gcc/g++

//이진수 표현에서 끝에 붙어 있는 0의 개수는?
int getMinElement(int p){
    if(p==0) return 1;
    if(p%2) return 0;
    return 1+getMinElement(p/2);
}
//__builtin_ctz(p) (0인 경우 결과 이상함 주의!)

//최하위 비트 구하기
int firstTopping(int pizza) {return (pizza & -pizza);} //2의 보수법 덕분에 가능
//최하위 비트 지우기
int deleteFirstTopping(int pizza) {return (pizza & (pizza-1));}
//모든 집합 순회
void iterate(int pizza){
    for(int subset=pizza;subset;subset=((subset-1) & pizza)){
        //do something
    }
}