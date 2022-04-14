#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

std::vector<double> differentiate(const std::vector<double>& poly); //poly=f(x)라할때 f`(x) 반환
std::vector<double> solveNaive(const std::vector<double>& poly); //1차, 2차 poly의 해를 구한다.
double evaluate(const std::vector<double>& poly, double x0); //poly=f(x)라할때 f(x0) 반환
std::vector<double> solve(const std::vector<double>& poly);

int main(){
    int testCase;
    std::cin >> testCase;
    for(int i=0;i<testCase;i++){
        int degree;
        std::cin >> degree;
        std::vector<double> poly(degree+1); //poly[i]=10^i의 계수
        for(int j=degree;j>=0;j--){
            std::cin >> poly[j];
        }
        std::vector<double> ret=solve(poly);
        for(int j=0;j<ret.size();j++){
            std::cout << ret[j] <<" ";
        }
        std::cout <<"\n";
    }
    return 0;
}

std::vector<double> differentiate(const std::vector<double>& poly){
    std::vector<double> ret(poly.size()-1);
    for(int i=poly.size()-1;i>0;i--){
        ret[i-1]=poly[i]*i;
    }
    for(int i=ret.size()-1;i>=0;i--){
        std::cout << ret[i] <<" ";
    }
    std::cout << "\n";
    return ret;
}

std::vector<double> solveNaive(const std::vector<double>& poly){
    if(poly.size()==2){//1차 방정식
        double ret=-1*(poly[0]/poly[1]);
        return std::vector<double>(ret,1);
    }
    else if(poly.size()==3){//2차 방정식
        double front=-1*(poly[1]/(2*poly[2])); 
        double back=std::sqrt(std::pow(poly[1],2)-4*poly[2]*poly[0])/(2*poly[2]);
        std::vector<double> ret;
        ret.push_back(front-back);
        ret.push_back(front+back);
        return ret;
    }
    return std::vector<double>();
}

double evaluate(const std::vector<double>& poly, double x0){
    double ret=0;
    for(int i=0;i<poly.size();i++){
        ret+=std::pow(x0,i)*poly[i];
    }
    return ret;
}

//poly의 근을 반환
std::vector<double> solve(const std::vector<double>& poly){
    int degree=poly.size()-1;
    if(degree<=2) return solveNaive(poly);
    std::vector<double> dPoly=differentiate(poly);
    std::vector<double> extremumPoints=solve(dPoly);
    extremumPoints.push_back(-11);
    extremumPoints.push_back(11);
    std::sort(extremumPoints.begin(), extremumPoints.end());

    std::vector<double> ret;
    for(int i=1;i<extremumPoints.size();i++){
        double left=extremumPoints[i-1],right=extremumPoints[i];
        std::cout << "x " <<left<<" "<<right<<"\n";
        double leftValue=evaluate(poly,left),rightValue=evaluate(poly,right);
        std::cout << "y " <<leftValue<<" "<<rightValue<<"\n"; 
        if(leftValue*rightValue>0) continue;
        if(leftValue>rightValue){
            std::swap(leftValue,rightValue);
            std::swap(left,right);
        }
        for(int it=0;it<100;it++){
            double mid=(left+right)/2;
            double midValue=evaluate(poly,mid);
            if(leftValue*midValue>0){
                leftValue=midValue;
                left=mid;
            }
            else{
                rightValue=midValue;
                right=mid;
            }
        }
        ret.push_back((left+right)/2.0);
    }
    std::sort(ret.begin(),ret.end());
    return ret;
}