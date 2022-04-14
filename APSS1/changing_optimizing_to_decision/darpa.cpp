#include <vector>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cmath>

//카메라를 설치할 수 있는 위치와 개수가 주어질때 가장 가까이 설치된 카메라의 거리의 최대값은?
double getMaxDistance(const std::vector<double> locations, const int cameras);


int main(){
    int testCase;
    std::cin >> testCase;
    for(int i=0;i<testCase;i++){
        int cameraCount, positionCount;
        std::vector<double> positions;
        std::cin >> cameraCount >> positionCount;
        for(int j=0;j<positionCount;j++){
            double position;
            std::cin >> position;
            positions.push_back(position);
        }
        std::cout << std::fixed << std::setprecision(2);
        std::cout << getMaxDistance(positions,cameraCount) <<"\n";
    }
    return 0;
}


bool isCanInstall(const std::vector<double> locations, const int cameras, const double gap){
    double installableLocation=-1;
    int installed=0;
    for(int i=0;i<locations.size();i++){
        if(installableLocation<=locations[i]){
            installed++;
            installableLocation=locations[i]+gap;
        }
    }
    return installed>=cameras;
}

double getMaxDistance(const std::vector<double> locations, const int cameras){
    double left=0,right=241;
    for(int it=0;it<100;it++){
        double mid=(left+right)/2.0;
        if(isCanInstall(locations,cameras,mid)){
            left=mid;
        }
        else{
            right=mid;
        }
    }
    return left;
}