#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

bool isArea(double startX, double endX, double startY, double endY, vector<vector<pair<double,double>>>& squares){
    bool ret=false;
    for(int i=0;i<squares.size();i++){
        ret|=(squares[i][0].first<=startX && endX<=squares[i][1].first && squares[i][0].second<=startY && endY<=squares[i][1].second);
    }
    return ret;
}

int main(){
    int n;
    cin >> n;
    vector<vector<pair<double,double>>> squares(n);
    vector<double> squareX;
    for(int i=0;i<n;i++){
        double startX, startY, width, height;
        cin >> startX >> startY >> width >> height;
        squares[i].push_back({startX,startY});
        squares[i].push_back({startX+width, startY+height});
        squareX.push_back(startX);
        squareX.push_back(startX+width);
    }
    sort(squareX.begin(), squareX.end());
    double ret=0;
    for(int i=1;i<squareX.size();i++){
        double fromX=squareX[i-1], toX=squareX[i];
        vector<double> squareY;
        for(int j=0;j<squares.size();j++){
            if(squares[j][0].first<=fromX && toX<=squares[j][1].first){
                squareY.push_back(squares[j][0].second);
                squareY.push_back(squares[j][1].second);
            }
        }
        sort(squareY.begin(), squareY.end());
        for(int j=1;j<squareY.size();j++){
            if(isArea(fromX, toX, squareY[j-1], squareY[j], squares)){
                ret+=(toX-fromX)*(squareY[j]-squareY[j-1]);
            }
        }
    }
    if(ret==ceil(ret)) cout << (int)ret <<"\n";
    else {
        cout << fixed << setprecision(2) << ret <<"\n";
    }
    return 0;
}