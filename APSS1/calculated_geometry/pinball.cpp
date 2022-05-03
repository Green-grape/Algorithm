#include <cmath>
#include <vector>
#include <iostream>
#include <string>

const double EPSILON=1e-9;
const double INF=1e200;

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
        return this->x*v.x+this->y*v.y;
    }
    double cross(const Vector& v){ //외적
        return this->x*v.y-this->y*v.x;
    }
    Vector project(Vector v){//this벡터를 v벡터에 사영
        Vector dir=v.normalize();
        return dir*dir.dot(*this);
    }
};

//ax^2+bx+c=0의 실수해를 반환
std::vector<double> poly2(double a, double b, double c){
    double d=b*b-4*a*c;
    if(d<-EPSILON) return std::vector<double>(); //해X
    if(d<EPSILON) return std::vector<double>(1, -b/(2*a)); //중근
    std::vector<double> ret;
    ret.push_back((-b-sqrt(d))/(2*a));
    ret.push_back((-b+sqrt(d))/(2*a));
    return ret;
}
//위치벡터가 p이고 방향 벡터가 q인 공이 1초에 q만큼 움직일때 중심이 cen이고 반지름이 r인 원과 몇 초후 충돌하는가?
//충돌하지 않는 경우 INF 반환
double hitCircle(Vector p, Vector q, Vector cen, int r){
    double a=q.dot(q);
    double b=2*(p-cen).dot(q);
    double c=cen.dot(cen)+p.dot(p)-2*p.dot(cen)-r*r;
    std::vector<double> times=poly2(a,b,c);
    if(times.size()==0 || times[0]<EPSILON) return INF;
    return times[0];
}

//방향벡터 q인 원이 중심이 cen인원과 contact에서 충돌했을때 새로운 방향은?(정반사 한다고 가정)
Vector reflectCircle(Vector q, Vector cen, Vector contact){
    return (q-q.project(contact-cen)*2).normalize();
}

std::vector<Vector> center;
std::vector<int> radius;
//공의 위치 pos와 방향 dir가 주어질때 최대 10번의 충돌을 반환한다.
std::vector<int> simulate(Vector pos, Vector dir){
    dir=dir.normalize();
    int hitCount=0;
    std::vector<int> ret;
    while(hitCount<100){
        int circle=-1, n=center.size();
        double minTime=INF*0.5;
        for(int i=0;i<n;i++){
            double cand=hitCircle(pos,dir,center[i], radius[i]+1); //충돌하는 공의 반지름을 0이라 두어 쉽게 풀기위해 수정
            if(cand<minTime){
                circle=i;
                minTime=cand;
            }
        }
        if(circle==-1) break;
        ret.push_back(circle);
        Vector contact=pos+dir*minTime;
        dir=reflectCircle(dir,center[circle],contact);
        pos=contact;
        hitCount++;
    }
    return ret;
}

int main(){
    int testCase;
    std::cin >> testCase;
    while(testCase--){
        int startX,startY,dx,dy,circleCount;
        std::cin >> startX >> startY >> dx >> dy >> circleCount;
        for(int n=0;n<circleCount;n++){
            int x,y,r;
            std::cin >> x >> y >> r;
            center.push_back(Vector((double)x,(double)y));
            radius.push_back(r);
        }
        std::vector<int> ret=simulate(Vector((double)startX,(double)startY),Vector((double)dx,(double)dy));
        for(int i=0;i<ret.size();i++){
            std::cout << ret[i] <<" ";
        }
        std::cout << "\n";
        //init
        center.resize(0);
        radius.resize(0);
    }
    return 0;
}
