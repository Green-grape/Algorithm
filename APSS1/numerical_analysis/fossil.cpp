#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

std::vector<std::pair<std::pair<double,double>,std::pair<double,double>>> upper,lower;
double getMaxDif(const double startX, const double endX, const std::vector<std::pair<double,double>> polygon1, const std::vector<std::pair<double,double>> polygon2);

int main(){
    int testCase;
    std::cin >> testCase;
    for(int i=0;i<testCase;i++){
        int vertexCount1,vertexCount2;
        double minX1=1e20,maxX1=-1e20,minX2=1e20,maxX2=-1e20;
        std::vector<std::pair<double,double>> vertex1; //[0,100],[0,100] & x,y는 실수 
        std::vector<std::pair<double,double>> vertex2;
        upper.clear();
        lower.clear();
        std::cin >> vertexCount1 >> vertexCount2;
        for(int j=0;j<vertexCount1;j++){ //시계 반대 방향으로 주어짐
            double x,y; 
            std::cin >> x >> y;
            vertex1.push_back(std::make_pair(x,y));
            maxX1=std::max(maxX1, x);
            minX1=std::min(minX1, x);
        }
        for(int j=0;j<vertexCount2;j++){ //시계 반대 방향으로 주어짐
            double x,y; 
            std::cin >> x >> y;
            vertex2.push_back(std::make_pair(x,y));
            maxX2=std::max(maxX2, x);
            minX2=std::min(minX2, x);
        }
        double startX=std::max(minX1,minX2);
        double endX=std::min(maxX1,maxX2);
        std::cout << std::fixed << std::setprecision(10);
        std::cout << getMaxDif(startX,endX,vertex1,vertex2)<<"\n";
    }
}

bool isBetween(const double x, const std::pair<double,double> p1,const std::pair<double,double> p2){
    return ((p1.first<=x && x<=p2.first) || (p2.first<=x && x<=p1.first));
}

//x좌표가 x인 수직선과 polygon과의 교점의 y좌표
double getY(const double x, const std::pair<double,double> p1,const std::pair<double,double> p2){
    const double dx=p1.first-p2.first;
    const double dy=p1.second-p2.second;
    return dy*(x-p1.first)/dx+p1.second;
}

//x좌표가 x일때 두 도형의 겹치는 부분의 차(삼분 검색을 이용하기 위해서 도형을 위, 아래로 쪼갠다)
double getDif(const double x){
    double minUp=1e20,maxLow=-1e20;
    const int us=upper.size(),ls=lower.size();
    for(int i=0;i<us;i++){
        if(isBetween(x,upper[i].first,upper[i].second)) minUp=std::min(minUp, getY(x,upper[i].first,upper[i].second));
    }
    for(int i=0;i<ls;i++){
        if(isBetween(x,lower[i].first,lower[i].second)) maxLow=std::max(maxLow, getY(x,lower[i].first,lower[i].second));
    }
    return minUp-maxLow;
}

//도형의 위, 아래를 upper, lower에 저장한다(입력이 반시계라는 것을 이용) 
void decompose(const std::vector<std::pair<double,double>>& vertex){
    const int n=vertex.size();
    for(int i=0;i<n;i++){
        if(vertex[i].first<vertex[(i+1)%n].first) lower.push_back(std::make_pair(vertex[i],vertex[(i+1)%n]));
        else if(vertex[i].first>vertex[(i+1)%n].first) upper.push_back(std::make_pair(vertex[i],vertex[(i+1)%n]));
    }
}

//가정:polygon1의 최대 높이가 polygon2보다 높다.
double getMaxDif(const double startX, const double endX, const std::vector<std::pair<double,double>> polygon1, const std::vector<std::pair<double,double>> polygon2){
    double left=startX,right=endX;
    decompose(polygon1);
    decompose(polygon2);
    if(right<left) return 0;
    for(int it=0;it<100;it++){
        double leftTernary=(left*2+right)/3;
        double rightTernary=(left+right*2)/3;
        if(getDif(leftTernary)>getDif(rightTernary)){
            right=rightTernary;
        }
        else left=leftTernary;
    }
    return std::max(0.0,getDif((left+right)/2));
}