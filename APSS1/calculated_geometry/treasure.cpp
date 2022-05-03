#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>

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

typedef std::vector<Vector> Polygon;

double solve(const Polygon& r, const Polygon& p);

int main(){
    int testCase;
    std::cin >> testCase;
    while(testCase--){
        int rx0,ry0,rx1,ry1,vertexCount; 
        Polygon polygon, rectangle;
        std::cin >> rx0 >> ry0 >> rx1 >> ry1 >> vertexCount;
        rectangle.push_back(Vector(rx0,ry0));
        rectangle.push_back(Vector(rx1,ry0));
        rectangle.push_back(Vector(rx1,ry1));
        rectangle.push_back(Vector(rx0,ry1));
        for(int i=0;i<vertexCount;i++){
            int x,y;
            std::cin >> x >> y;
            polygon.push_back(Vector(x,y));
        }   
        std::cout<< std::setprecision(15);
        std::cout << solve(rectangle,polygon) <<"\n";
    }
    return 0;
}

double area(const Polygon& p){
    double ret=0;
    int n=p.size();
    for(int i=0;i<n;i++){
        int j=(i+1)%n;
        ret+=p[i].x*p[j].y-p[j].x*p[i].y;
    }
    return fabs(ret)/2.0;
}

double ccw(Vector a, Vector b){//counter clockwise
    return a.cross(b);
}

double ccw(Vector p, Vector a, Vector b){
    return ccw(a-p, b-p);
}

bool isLineIntersect(Vector a, Vector b, Vector c, Vector d, Vector& x){
    double det=(b-a).cross(d-c);
    if(fabs(det)<EPSILON) return false;
    x=a+(b-a)*((c-a).cross(d-c)/det);
    return true;
}

//a,b 점벡터
//직선 (a,b)의 왼쪽에 있는 점과 p와의 교점 들을 반환한다.
Polygon cutPolygon(const Polygon& p, const Vector a, const Vector b){
    int n=p.size();
    std::vector<bool> inside(n);
    for(int i=0;i<n;i++) inside[i]=ccw(a,b,p[i])>=0; //반평면 내부에 있는가?
    Polygon ret;
    for(int i=0;i<n;i++){
        int j=(i+1)%n;
        if(inside[i]) ret.push_back(p[i]); //반평면 내에 존재하는 경우 결과 다각형에 i 반드시 포함
        if(inside[i]!=inside[j]){ //변과 직선의 교차
            Vector cross;
            if(isLineIntersect(p[i],p[j],a,b,cross)) ret.push_back(cross);
        }
    }
    return ret;
}

//r(rectangle), p(polygon) 모두 반시계 방향으로 꼭짓점이 주어졌다고 가정
//서덜랜드-호지맨 알고리즘
double solve(const Polygon& r, const Polygon& p){
    Polygon ret=p;
    int rn=r.size();
    for(int i=0;i<rn;i++){ //cutPolygon을 4번 불러서 사각형과 p의 교집합 ret 다각형을 구한다.
        ret=cutPolygon(ret,r[i],r[(i+1)%rn]);
    }
    return area(ret);
}