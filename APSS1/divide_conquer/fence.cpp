#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> boards;
int getBiggestSquare(int,int);
int getBiggestSquare2();

int main(){
    int testCase;
    vector<int> results;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int boardCount,board;
        cin >> boardCount;
        for(int j=0;j<boardCount;j++){
            cin >> board;
            boards.push_back(board);
        }
        results.push_back(getBiggestSquare(0,boards.size()-1));
        cout << 1 <<"\n";
        results.push_back(getBiggestSquare2());
        cout << 2 <<"\n";
        //reinitialize
        boards.resize(0);
    }
    for(vector<int>::iterator iter=results.begin();iter!=results.end();iter++){
        cout << *iter <<"\n";
    }
    return 0;
}

//[left,right]인 직사각형들중에서 사각형의 넓이가 가장 넓은 것을 return 'O(nlgn)'
int getBiggestSquare(int left, int right){
    //기저사례
    if(left>right) return 0;
    if(left==right) return boards[left];

    int mid=(left+right)/2;
    //가장 넓이가 큰 사각형이 mid를 걸치지 않을때   
    int sideBiggestArea=max(getBiggestSquare(left,mid-1),getBiggestSquare(mid+1,right));

    //가장 넓이가 큰 사각형이 mid를 걸칠때의 상황
    int currentHeight=boards[mid];
    int currentArea=currentHeight;
    int leftEnd=mid,rightEnd=mid;
    while(left<leftEnd || rightEnd<right){
        if(left<leftEnd && (rightEnd==right || (boards[leftEnd-1]>boards[rightEnd+1]))){
            leftEnd--;
            currentHeight=min(currentHeight, boards[leftEnd]);
        }
        else{
            rightEnd++;
            currentHeight=min(currentHeight,boards[rightEnd]);
        }
        currentArea=max(currentArea, currentHeight*(rightEnd-leftEnd+1));
    }
    return max(sideBiggestArea, currentArea);
}

int getBiggestSquare2(){
    stack<int> s;
    boards.push_back(0); //다른 모든 판자의 right[]를 정의해줌(right[i]: i번째 판자를 포함하는 사각형중 최대면적을 가지는 사각형을 오른쪽에서 막는 판자)
    int ret=0;
    for(int i=0;i<boards.size();i++){
        while(!s.empty() && boards[s.top()]>=boards[i]){
            int j=s.top();
            s.pop();
            int width=-1;
            if(s.empty()) width=i;
            else width=i-1-s.top();
            ret=max(ret, boards[j]*width);
        }
        s.push(i);
    }
    return ret;
}