#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
//미춌다....(복습 하기)

const int MAX_NODE=100;
const int INF=987654321;
int n;
double x[MAX_NODE],y[MAX_NODE],r[MAX_NODE];
std::pair<double,double> ranges[MAX_NODE];
void convertToRange(){
    for(int i=0;i<n;i++){
        double cur=fmod(M_PI*2+atan2(y[i],x[i]),M_PI*2);
        double range=2*asin(r[i]/16.0);
        ranges[i]=std::make_pair(cur-range,cur+range);
    }
    std::sort(ranges, ranges+n);
}

int solveLinear(double begin, double end){ //[begin,end]를 덮기 위해서 최소 몇개의 구간을 선택해야하는가?
    int used=0,idx=0;
    while(begin<end){
        double maxCover=-1;
        while(idx<n && ranges[idx].first<=begin){ //가장 많이 덮는 구간 찾기(ranges가 정렬되어 있음을 고려한다.)
            maxCover=std::max(maxCover,ranges[idx].second);
            idx++;
        }
        if(maxCover<=begin) return INF; //찾지 못함
        begin=maxCover;
        ++used;
    }
    return used;
}

int solveCircular(){
    convertToRange();
    int ret=INF;
    for(int i=0;i<n;i++){
        if(ranges[i].first<=0 || ranges[i].second>=M_PI*2){//정규화(원형을 선분으로 펴서 보고 있으므로 0을 덮는 구간을 고려한다)
            double begin=fmod(ranges[i].second,M_PI*2);
            double end=fmod(ranges[i].first+M_PI*2,M_PI*2);
            ret=std::min(ret,1+solveLinear(begin,end));
        }
    }
    return ret;
}

int main(){
    int testCase;
    std::cin >> testCase;
    for(int i=0;i<testCase;i++){
        std::cin >> n;
        for(int j=0;j<n;j++){
            std::cin >> y[j] >> x[j] >>r[j];
        }
        int ret=solveCircular();
        if(ret>=INF) std::cout <<"IMPOSSIBLE" <<"\n";
        else std::cout << ret<<"\n";
    }
    return 0;
}
