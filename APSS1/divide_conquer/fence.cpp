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
        results.push_back(getBiggestSquare2());
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

//
int getBiggestSquare2(){
    stack<int> remainBoards;
    boards.push_back(0);//for문이 한번더 시행되기 위함
    int ret=0;
    for(int i=0;i<boards.size();i++){
        while(!remainBoards.empty() && boards[remainBoards.top()]>=boards[i]){
            //int j=remainBoards.top();
            //right[j]=i;
            int currentHeight=boards[remainBoards.top()];
            remainBoards.pop();
            int width; //width=right[j]-left[j]-1
            if(remainBoards.empty()) width=i; //left[j]=-1
            else width=(i-1)-remainBoards.top(); //left[j]=remainBoards.top()
            ret=max(ret, width*currentHeight);
        }
        remainBoards.push(i);
    }
    return ret;
}