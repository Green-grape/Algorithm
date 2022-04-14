#include <vector>
#include <stdio.h>
#include <iostream>

std::vector<int> L;
std::vector<int> M;
std::vector<int> G;

int getKth(int k);

int main(void){
    int testCase;
    std::cin >> testCase;
    for(int i=0;i<testCase;i++){
        int cityCount, k;
        std::cin >> cityCount >> k;
        for(int j=0;j<cityCount;j++){
            int l,m,g;
            scanf("%d %d %d", &l, &m, &g);
            L.push_back(l);
            M.push_back(m);
            G.push_back(g);
        }
        printf("%d\n", getKth(k));
        L.resize(0);M.resize(0);G.resize(0);
    }
    return 0;
}

//0~distance까지의 표지판의 수가 N개 이상인가?
bool decision(int distance, int n){
    int cur=0,length=L.size();
    for(int i=0;i<length;i++){
        if(L[i]-M[i]<=distance){
            int end=std::min(L[i],distance);
            cur+=(end-(L[i]-M[i]))/G[i]+1;
        }
    }
    return cur>=n;
}

int getKth(int k){
    int left=0,right=8030001;
    for(int it=0;it<100;it++){
        int mid=(left+right)/2;
        if(decision(mid, k)){
            right=mid;
        }else{
            left=mid;
        }
    }
    return right;
}