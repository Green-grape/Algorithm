#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

void solve(vector<double>& trees, double needLength){
    double left=0,right=1000000000, mid;
    for(int it=0;it<100;it++){
        mid=(left+right)/2;
        double cand=0;
        for(int i=0;i<trees.size();i++){
            cand+=(trees[i]-mid>0 ? trees[i]-mid:0);
        }
        if(cand>needLength){
            left=mid;
        }else if(cand<needLength){
            right=mid;
        }
    }
    cout << (int)floor((left+right)/2) <<"\n";
}

int main(){
    int treeCount;
    double needLength;
    cin >> treeCount >> needLength;
    vector<double> trees(treeCount);
    for(int i=0;i<treeCount;i++){
        scanf("%lf", &trees[i]);
    }
    solve(trees, needLength);
    return 0;
}