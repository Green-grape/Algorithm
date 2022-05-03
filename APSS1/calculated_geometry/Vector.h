#include <cmath>
#include <algorithm>

class Vector{
public:
    double x,y;
    explicit Vector(double _x=0, double _y=0);//묵시적 형변환 방지
    bool operator==(const Vector& v);
    bool operator<(const Vector& v);
    Vector operator+(const Vector& v);
    Vector operator-(const Vector& v);
    Vector operator*(const double m);
    double norm(); //벡터의 길이
    Vector normalize();//단위 벡터 반환
    double polar(); //x축의 양의 방향으로 부터 벡터의 각도
    double dot(const Vector& v); //내적
    double cross(const Vector& v); //외적
    Vector project(Vector v);//this벡터를 v벡터에 사영
};
