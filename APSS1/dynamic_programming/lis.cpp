#include <iostream>
#include <vector>
#include <string>

#define MAX_ARR_LENGTH 502

using namespace std;

int cache[MAX_ARR_LENGTH];

int lis(vector<int>&);
int lis1(vector<int>&, int);
int lis2(vector<int>&, int);
int lis3(vector<int>&);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int elementCount;
        cin >> elementCount;
        vector<int> arr;
        for(int j=0;j<elementCount;j++){
            int temp;
            cin >> temp;
            arr.push_back(temp);
        }
        int res=lis3(arr);
        cout<<res<<"\n";
    }
}

// 완전 탐색 O(2^(n^2))
int lis(vector<int>& arr){
    if(arr.empty()) return 0;
    int ret=0;
    for(int idx=0;idx<arr.size();idx++){
        vector<int> biggerArr;
        for(int j=idx+1;j<arr.size();j++){
            if(arr[idx]<arr[j]) biggerArr.push_back(arr[j]);
        }
        ret=max(ret,1+lis(biggerArr));
    }
    return ret;
}

// 인덱스에 따라서 최대길이는 반드시 정해짐 -> cache[idx]=lisLength;로 캐싱 -> O(n^2)
// 이 함수를 n번 따로 호출해주어야한다.
int lis1(vector<int>& arr, int idx){
    if(cache[idx]!=-1) return cache[idx];
    int ret=1; //arr[idx] 포함
    for(int i=idx+1;i<arr.size();i++){
       if(arr[idx]<arr[i]) ret=max(ret, lis1(arr,i)+1);
    }
    return cache[idx]=ret;
}


//lis1의 n번따로 호출해주는 것을 없애는 코드 -> -1 index가 있는 것처럼 시작
int lis2(vector<int>& arr, int idx){
    if(cache[idx+1]!=-1) return cache[idx+1];
    int ret=1;
    for(int i=idx+1;i<arr.size();i++){
        if(idx==-1 || arr[idx]<arr[i]){
            ret=max(ret,lis2(arr,i)+1);
        }
    }
    return cache[idx+1]=ret;
}

int binarySearch(vector<int>& arr, int start, int end, int val){
    if(start>=end) return end;
    int mid=(start+end)/2;
    if(arr[mid]<val) return binarySearch(arr,mid+1,end,val);
    if(arr[mid]>val) return binarySearch(arr,start,mid,val);
    return mid;
}

// O(nlgn)
int lis3(vector<int>& arr){    
    vector<int> lis;
    lis.push_back(arr[0]);
    for(int i=1;i<arr.size();i++){
        if(lis.back()<arr[i]){ //lis의 맨 뒤값보다 큰 경우 arr[i]를 넣어준다.
            lis.push_back(arr[i]);
        }
        else{ //lis의 맨 뒤값보다 작거나 같은 경우 위치를 찾아서 넣어준다.
            int pos=binarySearch(lis,0,lis.size()-1,arr[i]);
            lis[pos]=arr[i];
        }   
    }
    return lis.size();
}