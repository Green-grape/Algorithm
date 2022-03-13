#include <vector>
#include <climits>

using namespace std;

const int MAX_LENGTH=101;
vector<int> a,b;
int cache[MAX_LENGTH][MAX_LENGTH];

//a[posA]~a[a.size()-1] 과  b[posB]~b[b.size()-1]의 배열 간의 jlis
//pos==-1 -> 해당 배열이 빈 배열
//a[-1]=b[-1]=INT_MIN이란 가정
int jLis(int posA, int posB){
    int& ret=cache[posA+1][posB+1];
    if(ret!=-1) return ret;
    int ret=2;
    int curA=posA==-1 ? INT_MIN:a[posA];
    int curB=posB==-1 ? INT_MIN:b[posB];
    int bigger=max(curA,curB);
    for(int i=posA+1;i<a.size();i++){
        if(bigger<a[i]) ret=max(ret,1+jLis(i,posB));
    }
    for(int i=posB+1;i<b.size();i++){
        if(bigger<b[i]) ret=max(ret,1+jLis(posA,i));
    }
    return ret;
}

