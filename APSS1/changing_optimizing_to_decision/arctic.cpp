#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <iomanip>

double optimize(const std::vector<std::pair<double,double>> locations);

int main(){
    int testCase;
    std::cin >> testCase;
    for(int i=0;i<testCase;i++){
        int locationCount;
        std::cin >> locationCount;
        std::vector<std::pair<double,double>> locations;
        for(int j=0;j<locationCount;j++){
            double x, y;
            std::cin >> x >> y;
            locations.push_back(std::make_pair(x,y));
        }
        std::cout << std::fixed << std::setprecision(2);
        std::cout <<optimize(locations)<<"\n";
    }
    return 0;
}

double distance(const double x1, const double x2, const double y1, const double y2){
    return std::sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

//반지름이 r인 통신장비로 모든 기지가 연결이 가능한가?
bool decision(const std::vector<std::pair<double,double>> locations, const double r){
    std::vector<std::vector<int>> connectable(locations.size(),std::vector<int>(locations.size(),0));
    for(int i=0;i<locations.size();i++){
        for(int j=i+1;j<locations.size();j++){
            double x1=locations[i].first,y1=locations[i].second;
            double x2=locations[j].first,y2=locations[j].second;
            if(distance(x1,x2,y1,y2)<=r){
                connectable[i][j]=1;
                connectable[j][i]=1;
            }
        }
    }
    //dfs도 가능하나 bfs보다 느리므로 bfs사용!
    std::vector<bool> isVisited(locations.size(),false);
    isVisited[0]=true;
    std::queue<int> q;
    q.push(0);
    int seen=0;
    while(!q.empty()){
        int top=q.front();
        q.pop();
        seen++;
        for(int i=0;i<connectable[top].size();i++){
            if(connectable[top][i] && !isVisited[i]){
                isVisited[i]=true;
                q.push(i);
            }
        }
    }
    return seen==locations.size();
}

double optimize(const std::vector<std::pair<double,double>> locations){
    double left=0, right=1500;
    for(int it=0;it<100;it++){
        double mid=(left+right)/2;
        if(decision(locations,mid)){
            right=mid;
        }
        else{
            left=mid;
        }
    }
    return right;
}