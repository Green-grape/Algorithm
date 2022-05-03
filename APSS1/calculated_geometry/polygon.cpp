//벡터를 이용한 다각형의 특징구하기
#include "Vector.h"
#include <vector>

//벡터를 이용한 다각형의 넓이 구하기
//p:다각형의 꼭짓점들
//ret:1/2*(p0Xp1+p1Xp2+...pn-1Xp0)
double area(const std::vector<Vector>& p){
    double ret=0;
    int n=p.size();
    for(int i=0;i<n;i++){
        int j=(i+1)%n;
        ret+=p[i].x*p[j].y-p[j].x*p[i].y;
    }
    return fabs(ret)/2.0;
}

//점 q가 다각형 p안에 있는가?
//q에서 x+방향으로 그은 반직선이 다각형과 교점의 개수로 판단
//짝수: 외부, 홀수: 내부
bool isInside(const Vector q, const std::vector<Vector>& p){
    int crosess=0,n=p.size();
    for(int i=0;i<n;i++){
        int j=(i+i)%n;
        if((p[i].y>q.y) != (p[j].y>q.y)){ //반직선을 선분(p[i],p[j])가 가로지르는가?
            double atX=(q.y-p[i].y)*(p[i].x-p[j].x)/(p[i].y-p[j].y)+p[i].x;
            if(q.x<atX) crosess++;
        }
    }
    return crosess%2==1;
}

int main(){
    return 0;
}

