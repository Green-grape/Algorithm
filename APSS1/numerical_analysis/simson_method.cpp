//simson's method를 이용해서 f(x)=e^x*sin(x)의 정적분 근삿값을 구해본다
#include <iostream>
#include <cmath>

const double radian=M_PI/180.0;

double f(double x){
    return exp(x)*sin(x);
}

double Fc(double x){
    return 0.5*(exp(x)*sin(x)-exp(x)*cos(x));
}

double F(double a, double b){
    return Fc(b)-Fc(a);
}

int main(){
    int n=2;
    double res=0,start=1,end=3;
    start*=radian;end*=radian;
    double h=(end-start)/n;
    while(1){
        for(int i=0;i<n/2;i++){
            double left=start+(2*i)*h,right=start+(2*i+2)*h;
            double mid=(left+right)/2;
            res+=(f(left)+4*f(mid)+f(right))*(h/3);
        }
        if(fabs(F(start,end)-res)<0.0000001){
            std::cout <<F(start,end)<<"\n";
            std::cout <<res <<"\n";
            std::cout << n<<"\n";
            break;
        }
        n+=2;
        res=0;
    }
    return 0;
}