#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string.h>

using namespace std;

const int MAX_LENGTH=100;
const int MAX_DIV=10;
const int INF=987654321;
vector<int> arr;
int cache[MAX_LENGTH][MAX_LENGTH][MAX_DIV];

int getMinDifQuantization(int,int,int);
void init();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int arrLength,divCount;
        cin >> arrLength >> divCount;
        init();
        for(int i=0;i<arrLength;i++){
            cin >> arr[i];
        }
        sort(arr.begin(),arr.begin()+arrLength);
        cout << getMinDifQuantization(0,arrLength-1,divCount) <<"\n";
    }
    return 0;
}

void init(){
    arr.resize(MAX_LENGTH,0);
    memset(cache,-1,sizeof(cache));
}

//가장 평균에 가까운 정수 반환
int getAverage(int start, int end){
    double sum=0;
    for(int i=start;i<=end;i++){
        sum+=arr[i];
    }
    sum/=(end-start+1);
    if(abs(sum)>=((int)(abs(sum)))+0.5) return sum>0 ? ((int)sum)+1:((int)sum)-1;
    return (int)sum;
}

//arr[start]~arr[end]까지의 양자화 최소값 반환,div는 양자화에 사용할 수 있는 값의 개수
int getMinDifQuantization(int start, int end, int div){
    if(start>=end) return 0;
    int& ret=cache[start][end][div];
    if(ret!=-1) return ret;
    if(div==1){
        int average=getAverage(start,end);
        ret=0;
        for(int i=start;i<=end;i++){
            ret+=(arr[i]-average)*(arr[i]-average);
        }
        return ret;
    }
    ret=INF;
    for(int i=start-1;i+start<=end;i++){
        ret=min(ret,getMinDifQuantization(start,i,1)+getMinDifQuantization(i+1,end,div-1));
    }
    return ret;
}