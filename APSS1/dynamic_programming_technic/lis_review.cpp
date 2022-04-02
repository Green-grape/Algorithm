#include <algorithm>
#include <vector>

using namespace std;

const int MAX_LENGTH=100;
int cache[MAX_LENGTH], arr[MAX_LENGTH];
int idx[MAX_LENGTH];
vector<int> c;
int n;

//start~n-1까지의 LIS길이 출력 O(n^2)
int lisFrom(int start){
    int& ret=cache[start];
    if(ret!=-1) return cache[start];
    ret=1;
    for(int i=start+1;i<n;i++){
        if(arr[start]<arr[i]){
            ret=max(ret,1+lisFrom(i));
        }
    }
    return ret;
}

int lis2(){
    int maxLen=0;
    for(int i=0;i<n;i++){
        maxLen=max(maxLen, lisFrom(i));
    }
    return maxLen;
}

int binarySearch(vector<int>& v, int start, int end, int val){
    if(start>=end) return start;
    int mid=(start+end)/2;
    if(v[mid]>val) return binarySearch(v, start, mid-1,val);
    if(v[mid]<val) return binarySearch(v, mid+1,end,val);
    return mid;
}

int lisFast(int start){
    c.push_back(arr[start]);
    idx[start]=0;
    for(int i=start+1;i<n;i++){
        if(c.back()<arr[i]){
            c.push_back(arr[i]);
            idx[i]=i-start;
        }
        else{
            int pos=(c,start,c.size()-1,arr[i]);
            c[pos]=arr[i];
            idx[i]=pos-start;
        }
    }
    return c.size();
}

//lis 전체 구조 반환
vector<int> reconstruct(int start){
    vector<bool> isFinded(MAX_LENGTH,false);
    vector<int> ret;
    int arrIdx=n-1;
    int find=c.size()-1;
    while(arrIdx>=start){
        if(idx[arrIdx]==find && !isFinded[find]){
            isFinded[find]=true;
            find--;
            ret.push_back(arr[arrIdx]);
            if(find<0) break;
        }
        arrIdx--;
    }
    sort(ret.begin(),ret.end());
    return ret;
}