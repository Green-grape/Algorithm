#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int MAXN=10000000;

vector<int> parent(MAXN+1);

int getParent(int child){
    if(parent[child]==child) return child;
    return parent[child]=getParent(parent[child]);
}

bool isSameSet(int n1, int n2){
    return getParent(n1)==getParent(n2);
}

void unify(int n1, int n2){
    int p1=getParent(n1);
    int p2=getParent(n2);
    if(p1<p2){
        parent[p2]=p1;
    }else if(p1>p2){
        parent[p1]=p2;
    }
}

int main(){
    int n, operateCount;
    cin >> n >> operateCount;
    for(int i=0;i<=n;i++){
        parent[i]=i;
    }
    for(int i=0;i<operateCount;i++){
        int opt,n1,n2;
        scanf("%d %d %d", &opt, &n1 ,&n2);
        if(opt==0){
            unify(n1,n2);
        }else{
            if(isSameSet(n1,n2)){
                cout <<"YES" <<"\n";
            }else{
                cout <<"NO" <<"\n";
            }
        }
    }
    return 0;
}