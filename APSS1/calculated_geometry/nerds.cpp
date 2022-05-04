#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

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

double ccw(Vector a, Vector b){//counter clockwise
    return a.cross(b);
}

//기준을 p로 했을때
double ccw(Vector p, Vector a, Vector b){
    return ccw(a-p, b-p);
}

typedef vector<Vector> Polygon;

//볼록껍질(convexholl): 모든 정점을 포함하는 최소 크기의 다각형
//gift wrapping algorithm
Polygon getConvexHoll(vector<Vector>& points){
    int n=points.size();
    Polygon ret;
    Vector start=*min_element(points.begin(), points.end());
    ret.push_back(start);
    while(true){
        Vector pivot=ret.back(), next=points[0];
        for(int i=1;i<n;i++){
            double cross=ccw(pivot, next, points[i]); //0보다 작으면 더 오른쪽
            double dis=(points[i]-pivot).norm()-(next-pivot).norm();
            if(cross>0 || (cross==0 && dis>0)) next=points[i];
        }
        if(next==start) break;
        ret.push_back(next);
    }
    return ret;
}

bool isInside(const Vector q, const vector<Vector> p){
    int crosess=0,n=p.size();
    for(int i=0;i<n;i++){
        int j=(i+1)%n;
        if((p[i].y>q.y) != (p[j].y>q.y)){ //반직선을 선분(p[i],p[j])가 가로지르는가?
            double atX=(q.y-p[i].y)*(p[i].x-p[j].x)/(p[i].y-p[j].y)+p[i].x;
            if(q.x<atX) crosess++;
        }
    }
    return crosess%2==1;
}

bool isLineSegmentIntersect(Vector a, Vector b, Vector c, Vector d){
    double ab=ccw(a,b,c)*ccw(a,b,d); //교점이 생기려면 선분 ab가 선분 cd를 가로 질러야 한다 음수면 가로  지름
    double cd=ccw(c,d,a)*ccw(c,d,b); //교점이 생기려면 선분 cd도 선분 ab를 가로 질러야 한다 음수면 가로  지름
    if(ab==0 && cd==0){ //a,b,c,d가 모두 한 직선에 있는 경우
        if(b<a) std::swap(a,b);
        if(d<c) std::swap(c,d);
        return !(b<c || d<a);
    }
    return ab<=0 && cd <=0;
}

bool isPolygonIntersect(Polygon p1, Polygon p2){
    int n=p1.size(),m=p2.size();
    //하나가 다른 하나를 포함
    if(isInside(p1[0],p2) || isInside(p2[0],p1)) return true;
    //이외에는 선분이 서로 만나는 경우
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(isLineSegmentIntersect(p1[i],p1[(i+1)%n],p2[j],p2[(j+1)%m])) return true;
            
        }
    }
    return false;
}

int main(){
    int testCase;
    cin >> testCase;
    while(testCase--){
        int count;
        cin >> count;
        vector<Vector> nerds, notNerds;
        for(int i=0;i<count;i++){
            int x,y,isNerd;
            cin >> isNerd >> x >> y;
            if(isNerd) nerds.push_back(Vector(x,y));
            else notNerds.push_back(Vector(x,y));
        }
        Polygon p1=getConvexHoll(nerds);
        Polygon p2=getConvexHoll(notNerds);
        if(isPolygonIntersect(p1,p2)){
            cout << "THEORY IS INVALID" <<"\n";
        }
        else cout << "THEORY HOLDS" <<"\n";
    }   
    return 0;
}