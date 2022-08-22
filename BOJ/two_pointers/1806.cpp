/*
10,000 이하의 자연수로 이루어진 길이 N짜리 수열이 주어진다. 
이 수열에서 연속된 수들의 부분합 중에 그 합이 S 이상이 되는 것 중, 가장 짧은 것의 길이를 구하는 프로그램을 작성하시오.
*/

//복습

#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

vector<int> arr; //arr[1]부터 유효한 값이 들어감
vector<int> sumTo; //sumTo[i]=0~i번째까지의 합

int getMinLength(int s){
    for(int i=1;i<arr.size();i++) sumTo[i]=sumTo[i-1]+arr[i];
    int left=1;
    int right=arr.size()-1;
    int ret;
    while(left<=right){
        int mid=(left+right)/2;
        bool isCanbeShort=false;
        for(int i=1;i<=arr.size()-mid;i++){
            if(sumTo[i+mid-1]-sumTo[i-1]>=s){
                isCanbeShort=true;
                break;
            }
        }
        if(isCanbeShort){
            right=mid-1;
            ret=mid;
        }
        else left=mid+1;
        if(left>arr.size()-1) return 0;
    }
    return ret;
}

int main(){
    int arrLength, sum;
    cin >> arrLength >> sum;
    arr.resize(arrLength+1);
    sumTo.resize(arrLength+1);
    for(int i=1;i<arr.size();i++) scanf("%d", &arr[i]);
    cout << getMinLength(sum) <<"\n";
    return 0;
}
