#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <string.h>

const int MAX_PRICE_LENGTH=14;
const int MAX_M=20;
const int MOD=1e9+7;
int cache[(1<<(MAX_PRICE_LENGTH))+1][MAX_M+1][2];
bool isUsed[MAX_PRICE_LENGTH];
using namespace std;

int solution(string, int);
bool isDividable(string s, int m);
void init();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        string curPrice;
        int m;
        cin >> curPrice >> m;
        init();
        cout << solution(curPrice,m)<<"\n";
    }
    return 0;
}

void init(){
    for(int i=0;i<MAX_PRICE_LENGTH;i++) isUsed[i]=false;
    memset(cache,-1,sizeof(cache));
}

bool isDividable(string s, int m){
    int totalMod=0;
    int totalModNum=0;
    long long num=stoll(s);
    for(int i=0;i<s.length();i++){
        int subMod=((int)(s[i]-'0'));
        subMod%=m;
        for(int j=s.length()-1-i;j>0;j--){
            subMod=((subMod%m)*(10%m))%m;
        }
        totalMod=(subMod+totalMod)%m;
    }
    if(totalMod%m==0) return true;
    return false;
}

//des보다 작고 m으로 나눈 나머지가 0인 가격의 순열의 개수를 반환
//idx: 추가할 숫자의 인덱스
//taken: 추가된 숫자들의 인덱스를 비트로 표현한것
//mod:price를 m으로 나눈 나머지 -> 나머지가 같다=>price=m*k+나머지로 표현할때 같은 형태이다
//less:현재의 숫자가 des보다 작은 위치에 있는가?
int permutation(int idx,int taken, int mod, int less, const string& start, const string& des,const int& m){
    if(idx==start.size()){
        return (less && (mod==0)) ? 1:0;
    }
    int& ret=cache[taken][mod][less];
    if(ret!=-1) return ret;
    ret=0;
    for(int next=0;next<des.size();next++){
        if((taken & (1<<next))==0){
            if(!less && des[idx]<start[next]) continue; //작을 가능성이 없는 것은 배제
            if(next>0 && start[next-1]==start[next] && ((taken & (1<<(next-1)))==0)) continue; //같은 숫자는 하나만 선택
            int nextMod=((mod*(10%m))%m+(start[next]-'0')%m)%m;
            int nextTaken=taken | (1<<next);
            int nextLess=less || des[idx]>start[next];
            ret=(ret+permutation(idx+1,nextTaken,nextMod,nextLess,start,des,m))%MOD;
        }
    }
    return ret%MOD;
}

int solution(string curPrice, int m){
    string start=curPrice;
    int ret=0;
    sort(start.begin(), start.end());
    return permutation(0,0,0,0,start,curPrice,m);
}

