#include <vector>
#include <iostream>
#include <iomanip>

double getMinCash(const double remain, const int month, const double interest);

int main(){
    int testCase;
    std::cin >> testCase;
    for(int i=0;i<testCase;i++){
        double remain, interest;
        int month;
        std::cin >> remain >> month >> interest;
        std::cout << std::fixed << std::setprecision(10);
        std::cout << getMinCash(remain, month, interest) <<"\n";
    }
    return 0;
}

//remain을 month동안 interest의 연이자율로 매달 cash만큼 갚을때 남은 금액은?
double banlance(double remain, const double cash, const int month, const double interest){
    for(int it=0;it<month;it++){
        remain*=(1.0+(interest/12.0)/100.0);
        remain-=cash;
    }
    return remain;
}

double getMinCash(const double remain, const int month, const double interest){
    double left=0,right=100000000*(1.0+(interest/12.0)/100.0)+1;
    for(int it=0;it<100;it++){
        double mid=(left+right)/2;
        if(banlance(remain, mid, month, interest)<0){
            right=mid;
        }else{
            left=mid;
        }
    }
    return right;
}