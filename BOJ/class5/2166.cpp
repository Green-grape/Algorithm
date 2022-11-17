#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

//TIP
//외적
//long double은 16byte로 정밀도가 매우 높다
long double outerProduct(pair<int,int> pivot, pair<int,int> v1, pair<int,int> v2){
    return (v1.first-pivot.first)*(long double)(v2.second-pivot.second)-(v2.first-pivot.first)*(long double)(v1.second-pivot.second);
}

long double getArea(vector<pair<int,int>>& coords){
    long double ret=0;
    pair<int,int> pivot=coords[0];
    for(int i=1;i<coords.size()-1;i++){
        ret+=(outerProduct(pivot, coords[i], coords[i+1])/2.0);
    }
    return ret;
}

int main(){
    int n;
    cin >> n;
    vector<pair<int,int>> coords(n);
    for(int i=0;i<n;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        coords[i]={x,y};
    }
    long double ret=getArea(coords);
    if(ret<0) ret*=-1;
    printf("%.1Lf\n", ret);
    return 0;
}