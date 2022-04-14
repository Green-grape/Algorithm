#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

int lectureCount,remainCount;

double getMinAverageRank(const std::vector<int>& lectureRank, const std::vector<int>& lectureStudent);

int main(){
    int testCase;
    std::cin >> testCase;
    for(int i=0;i<testCase;i++){
        std::cin >> lectureCount >> remainCount;
        std::vector<int> lectureRank, lectureStudent;
        for(int j=0;j<lectureCount;j++){
            int rank, student;
            std::cin >> rank >> student;
            lectureRank.push_back(rank);
            lectureStudent.push_back(student);
        }
        std::cout << std::fixed << std::setprecision(10)<<"\n";
        std::cout << getMinAverageRank(lectureRank, lectureStudent) <<"\n";
    }   
    return 0;
}

bool decision(const std::vector<int>& lectureRank, const std::vector<int>& lectureStudent,const double rank){
    std::vector<double> decisionValue(lectureCount,0); 
    for(int i=0;i<decisionValue.size();i++){
        decisionValue[i]=lectureRank[i]-rank*lectureStudent[i];
    }
    std::sort(decisionValue.begin(), decisionValue.end());
    double ret=0;
    for(int i=0;i<remainCount;i++) ret+=decisionValue[i];
    return ret<=0;
}

double getMinAverageRank(const std::vector<int>& lectureRank, const std::vector<int>& lectureStudent){
    double left=0,right=1;
    for(int it=0;it<100;it++){
        double mid=(left+right)/2.0;
        if(decision(lectureRank,lectureStudent,mid)){
            right=mid;
        }
        else left=mid;
    }
    return right;
}