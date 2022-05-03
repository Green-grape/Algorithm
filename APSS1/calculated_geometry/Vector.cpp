//수학적의미에서 벡터의 구현
#include <cmath>
#include <algorithm>
const double EPSILON=0.000001;

class Vector{
public:
    double x,y;
    explicit Vector(double _x=0, double _y=0){ //묵시적 형변환 방지
        this->x=_x;
        this->y=_y;
    }
    bool operator==(const Vector& v){
        return this->x==v.x && this->y==v.y;
    }
    bool operator<(const Vector& v){
        return this->x!=v.x ? this->x<v.x : this->y<v.y;
    }
    Vector operator+(const Vector& v){
        return Vector(this->x+v.x, this->y+v.y);
    }
    Vector operator-(const Vector& v){
        return Vector(this->x-v.x, this->y-v.y);
    }
    Vector operator*(const double m){
        return Vector(this->x*m, this->y*m);
    }
    double norm(){ //벡터의 길이
        return sqrt(pow(this->x,2)+pow(this->y,2));
    }
    Vector normalize(){//단위 벡터 반환
        double length=this->norm();
        return Vector(this->x/length, this->y/length);
    }
    double polar(){ //x축의 양의 방향으로 부터 벡터의 각도
        return fmod(atan2(y,x)+2*M_PI, 2*M_PI);
    }
    double dot(const Vector& v){ //내적
        return this->x*v.x+this->y+v.y;
    }
    double cross(const Vector& v){ //외적
        return this->x*v.y-this->y*v.x;
    }
    Vector project(Vector v){//this벡터를 v벡터에 사영
        Vector dir=v.normalize();
        return dir*dir.dot(*this);
    }
};

//vector를 이용한 두 점과 다른 한 점과의 거리차
//a가 b보다 p에 얼마나 가까운가
double howMuchCloser(Vector p, Vector a, Vector b){
    return (b-p).norm()-(a-p).norm();
}

//외적을 이용한 두 벡터의 방향 추측
//원점을 기준으로 하여 b가 a의 반시계 방향인가? (yes:양수, no:음수)
double ccw(Vector a, Vector b){//counter clockwise
    return a.cross(b);
}

//기준을 p로 했을때
double ccw(Vector p, Vector a, Vector b){
    return ccw(a-p, b-p);
}

//(a,b)를 포함하는 직선과 (c,d)를 포함하는 직선의 교점 x를 구한다.
//두 선이 평행하면 false 아니면 true
bool isLineIntersect(Vector a, Vector b, Vector c, Vector d, Vector& x){
    double det=(b-a).cross(d-c);
    if(fabs(det)<EPSILON) return false;
    x=a+(b-a)*((c-a).cross(d-c)/det);
    return true;
}

//선분과 선분의 교차:(a,b)와 (c,d)가 평행한 두 성분 일때 이들이 한 점에 겹치는가?
bool parallelSegments(Vector a, Vector b, Vector c, Vector d, Vector& p){
    if(b<a) std::swap(a,b);
    if(d<c) std::swap(c,d);
    //한 직선 위가 아니 거나 두 선분이 겹치지 않는 경우
    if(ccw(a,b,c)!=0 || b<c || d<a) return false;
    if(a<c) p=c;
    else p=a;
    return true;
}

//a,b,p가 일직선상에 있을때 p가 a,b두 점 사이에 있는가?
bool isBetween(Vector p, Vector a, Vector b){
    if(b<a) std::swap(a,b);
    return p==a || p==b || (a<p && p<b);
}

//선분(a,b)와 (c,d)의 교점 p반환
//교점 존재 true, 아님 false
//여러개인 경우 아무거나
bool isLineSegmentIntersect(Vector a, Vector b, Vector c, Vector d,Vector& p){
    if(!isLineIntersect(a,b,c,d,p)) return parallelSegments(a,b,c,d,p);
    return isBetween(p,a,b) && isBetween(p,c,d);
}

//교점이 필요없는 경우
bool isLineSegmentIntersect(Vector a, Vector b, Vector c, Vector d){
    double ab=ccw(a,b,c)*ccw(a,b,d); //교점이 생기려면 선분 ab가 선분 cd를 가로 질러야 한다 음수면 가로  지름
    double cd=ccw(c,d,a)*ccw(c,d,b); //교점이 생기려면 선분 cd도 선분 ab를 가로 질러야한다 음수면 가로  지름
    if(ab==0 && cd==0){ //a,b,c,d가 모두 한 직선에 있는 경우
        if(b<a) std::swap(a,b);
        if(d<c) std::swap(c,d);
        return !(b<c || d<a);
    }
    return ab<=0 && cd <=0;
}

//(a,b)를 지나는 직선에 p가 내린 수선의 발
Vector perpendicularFoot(Vector p, Vector a, Vector b){
    return a+(p-a).project(b-a);
}

//점과 선 사이의 거리(사영 이용)
//(a,b)를 지나는 직선과 p의 거리
double pointToLine(Vector p, Vector a, Vector b){
    return (p-perpendicularFoot(p,a,b)).norm();
}