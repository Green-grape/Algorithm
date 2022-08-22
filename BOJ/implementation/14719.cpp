#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

//최적화 가능(To Do)

int getStagnantWater(vector<int>& heights){
    vector<int> leftMaxHeights(heights.size());
    vector<int> rightMaxHeights(heights.size());
    for(int i=0;i<heights.size();i++){
        for(int left=i-1;left>=0;left--) leftMaxHeights[i]=max(leftMaxHeights[i],heights[left]);
        for(int right=i+1;right<heights.size();right++) rightMaxHeights[i]=max(rightMaxHeights[i],heights[right]);
    }
    int ret=0;
    for(int i=0;i<heights.size();i++){
        int needToFill=min(leftMaxHeights[i],rightMaxHeights[i])-heights[i];
        if(needToFill>0) ret+=needToFill;
    }
    return ret;
}

int main(){
    int height,width;
    cin >> height >> width;
    vector<int> heights(width);
    for(int i=0;i<heights.size();i++) scanf("%d", &heights[i]);
    cout << getStagnantWater(heights) <<"\n";
    return 0;
}