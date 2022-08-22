/*N(1 ≤ N ≤ 100)개의 수로 이루어진 1차원 배열이 있다. 이 배열에서 M(1 ≤ M ≤ ⌈(N/2)⌉)개의 구간을 선택해서, 구간에 속한 수들의 총 합이 최대가 되도록 하려 한다. 단, 다음의 조건들이 만족되어야 한다.

각 구간은 한 개 이상의 연속된 수들로 이루어진다.
서로 다른 두 구간끼리 겹쳐있거나 인접해 있어서는 안 된다.
정확히 M개의 구간이 있어야 한다. M개 미만이어서는 안 된다.
N개의 수들이 주어졌을 때, 답을 구하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>

const int MAXN=100;
const int INF=987654321;

using namespace std;

vector<int> arr;
vector<vector<int>> cache(MAXN, vector<int>(MAXN,-1));

int getMaxSum(int from, int remainRanges){ //from으로 부터 remainRanges만큼의 구간을 선택할때 그 구간들의 합의 최대
    if(from>=arr.size() || remainRanges==0) return 0;
    int& ret=cache[from][remainRanges];
    if(ret!=-1) return ret;
    ret=-INF;
    int tempSum=0;
    for(int i=from;i<arr.size();i++){
        tempSum+=arr[i];
        if((arr.size()-i-1)/2>=remainRanges-1) ret=max(ret,tempSum+getMaxSum(i+2,remainRanges-1));
    }
    if((arr.size()-from)/2>=remainRanges) ret=max(ret,getMaxSum(from+1,remainRanges));
    return ret;
}

int main(){
    int n,m;
    cin >> n >> m;
    arr.resize(n);
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    cout << getMaxSum(0,m) <<"\n";
    return 0;
}