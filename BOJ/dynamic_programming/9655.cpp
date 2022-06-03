#include <iostream>
#include <string.h>

using namespace std;
const int MAX=1000;

int cache[MAX+1];
int win(int remain){ //remain만큼 돌이 남았을때 해당 플레이어가 승리하는가?
    if(remain==1) return 1;
    if(remain==2) return 0;
    if(remain==3) return 1;
    int& ret=cache[remain];
    if(ret!=-1) return ret;
    return ret=(!win(remain-3)) || (!win(remain-1));
}

int main(){
    int n;
    cin >> n;
    memset(cache,-1,sizeof(cache));
    if(win(n)) cout <<"SK"<<"\n";
    else cout <<"CY"<<"\n";
}