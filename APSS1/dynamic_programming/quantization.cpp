#include <iostream>
#include <vector>
#include <algorithm>
#include "string.h"

#define INF 987654321
#define MAX_ARR_LENGTH 100
#define MAX_DIV 10

using namespace std;

int cache[MAX_ARR_LENGTH+1][MAX_ARR_LENGTH+1];
int totalMinSquareDif[MAX_ARR_LENGTH+1][MAX_ARR_LENGTH+1][MAX_DIV+1];
int solution(vector<int>&, int);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        vector<int> arr;
        int arrLength, usingNumberCount,temp;
        cin >> arrLength >> usingNumberCount;
        for(int j=0;j<arrLength;j++){
            cin >> temp;
            arr.push_back(temp);
        }
        cout <<solution(arr, usingNumberCount)<<"\n";
    }
}

//arr의 오차제곱의 합의 최소값을 출력 [start,end]
int getMinSquareDif(vector<int>& arr, int start, int end){
   //for(int i=start;i<=end;i++){
    //    cout<<arr[i];
    //}
    int& ret=cache[start][end];
    if(ret!=-1) return ret;
    ret=0;
    double avr=0;
    int apxAvr;
    for(int i=start;i<=end;i++) avr+=arr[i];
    avr/=(end-start+1);
    if(avr-(int)avr>=0.5) apxAvr=((int)avr)+1;
    else apxAvr=(int)avr;
    for(int i=start;i<=end;i++){
        ret+=(apxAvr-arr[i])*(apxAvr-arr[i]);
    } 
    //cout <<" avr "<<avr<<" apxAvr "<< apxAvr<<" ret "<<ret<<"\n";
    return ret;
}

//arr을 div개로 나누어 오차제곱의 합을 구했을 때 그 최소값
//가정: arr은 오름차순으로 정렬되어있다.
int getTotalMinSquareDif(vector<int>& arr, int start, int end, int div){
    if(start>end) return 0;
    int& ret=totalMinSquareDif[start][end][div];
    if(ret!=-1) return ret;
    if(div==1) return ret=getMinSquareDif(arr,start,end);
    ret=INF;
    for(int i=0;i<arr.size();i++){
        if(start+i<=end) ret=min(ret, getMinSquareDif(arr,start,start+i)+getTotalMinSquareDif(arr, start+i+1,end,div-1));
    }
    return ret;
}


int solution(vector<int>& arr, int div){
    memset(cache,-1,sizeof(cache));
    memset(totalMinSquareDif,-1,sizeof(totalMinSquareDif));
    sort(arr.begin(),arr.end());
    return getTotalMinSquareDif(arr,0,arr.size()-1,div);
}