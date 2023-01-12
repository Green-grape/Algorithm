#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN=100;

void addAllLines(vector<vector<pair<int,int>>>& lines, int startX, int startY, int endX, int endY, int idx){
    for(int x=startX;x<endX;x++){
        lines[x].push_back({startY,idx});
        lines[x].push_back({endY,idx});
    }
}

bool isArea(int x, pair<int,int> line1, pair<int,int> line2, vector<vector<pair<int,int>>>& rectangle){
    bool ret=false;
    for(int i=0;i<rectangle.size();i++){
        ret|=(rectangle[i][0].first<=x && x+1<=rectangle[i][1].first && rectangle[i][0].second<=line1.first && line2.first<=rectangle[i][1].second);
    }
    return ret;
}

int solve(vector<vector<pair<int,int>>>& lines, vector<vector<pair<int,int>>>& rectangle){
    int ret=0;
    for(int x=1;x<MAXN;x++){
        sort(lines[x].begin(), lines[x].end());
        //cout << x << "~"<< x+1 <<"\n";
        for(int i=1;i<lines[x].size();i++){
            if(isArea(x, lines[x][i-1], lines[x][i], rectangle)){
                ret+=lines[x][i].first-lines[x][i-1].first;
                //if(lines[x][i].first-lines[x][i-1].first) cout << ret <<"\n";
            }
        }
    }
    return ret;
}

int main(){
    vector<vector<pair<int,int>>> lines(MAXN); //lines[x]=x~x+1의 라인의 y값과 그 라인을 가진 직사각형 인덱스
    vector<vector<pair<int,int>>> rectangle(4);
    for(int i=0;i<4;i++){
        int startX, startY, endX, endY;
        cin >> startX >> startY >> endX >> endY;
        rectangle[i].push_back({startX,startY});
        rectangle[i].push_back({endX,endY});
        addAllLines(lines, startX, startY, endX, endY,i);
    }
    cout << solve(lines,rectangle) <<"\n";
    return 0;
}