#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

int getSubArrayCountAtSum(const int, const int);

class NumberGenerator{
    private:
        int start=1983;
        long long cur=-1;
        long long mod=pow(2,32);
    public:
        int first(){
            return cur=start;
        }
        int next(){
            if(cur==-1) return cur=start;
            cur=(cur*214013+2531011)%mod;
            return cur%10000+1;
        }
};

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int arrLength, subArrSum; //arrLength<=50000000, subArrSum<=5000000
        cin >> subArrSum >> arrLength;
        cout << getSubArrayCountAtSum(arrLength,subArrSum) << "\n";
    }
    return 0;
}


//offline algorithm
/*
int getSubArrayCountAtSum(const vector<int>& arr, const int subArrSum){
    int tail=0,ret=0,rangeSum=arr[0];
    for(int head=0;head<arr.size();head++){
        while(rangeSum<subArrSum && tail+1<arr.size()){
            rangeSum+=arr[++tail];
        }
        if(rangeSum==subArrSum) ret++;
        rangeSum-=arr[head];
    }
    return ret;
}
*/

//online algorithm
int getSubArrayCountAtSum(const int arrLength, const int subArrSum){
    NumberGenerator num=NumberGenerator();
    int ret=0, rangeSum=num.first(), count=0;
    queue<int> subArr;
    subArr.push(num.first());
    for(int i=0;i<arrLength;i++){
        while(rangeSum<subArrSum && count+1<arrLength){
            int newValue=num.next();
            //cout << rangeSum <<" + "<<newValue<<"\n";
            rangeSum+=newValue;
            subArr.push(newValue);
            count++;
        }
        //cout << rangeSum <<" = "<<subArrSum <<"\n";
        if(rangeSum==subArrSum) ret++;  
        rangeSum-=subArr.front();
        subArr.pop();      
    }
    return ret;
}