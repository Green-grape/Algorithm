#include <iostream>

using namespace std;

int x1,y1,x2,y2;
int x3,y3,x4,y4;

int ccw(int x1, int y1, int x2, int y2){ 
    long long temp=x1*(long long)y2-x2*(long long)y1;
    if(temp>0) return 1;
    if(temp==0) return 0;
    if(temp<0) return -1;
}

bool isCross(){
    int d1=ccw(x3-x1, y3-y1, x2-x1, y2-y1);
    int d2=ccw(x4-x1, y4-y1, x2-x1, y2-y1);
    int d3=ccw(x1-x3, y1-y3, x4-x3, y4-y3);
    int d4=ccw(x2-x3, y2-y3, x4-x3, y4-y3);
    if(d1*d2<=0 && d3*d4<=0){
        if(d1*d2==0 && d3*d4==0){ //일직선
            pair<int,int> p1=min(make_pair(x1,y1),make_pair(x2,y2));
            pair<int,int> p2=max(make_pair(x1,y1),make_pair(x2,y2));
            pair<int,int> p3=min(make_pair(x3,y3),make_pair(x4,y4));
            pair<int,int> p4=max(make_pair(x3,y3),make_pair(x4,y4));
            return (p1<=p4 && p3<=p2);
        }else{
            return 1;
        }
    }
    return 0;
}

int main(){
    cin >> x1 >> y1 >> x2 >> y2;
    cin >> x3 >> y3 >> x4 >> y4;
    cout << isCross() <<"\n";
    return 0;
}