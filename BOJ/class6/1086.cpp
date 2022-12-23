#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAXN=50;

vector<string> nums;
vector<int> modNums; //modNums[i]=nums[i]%k;
vector<vector<long long>> cache;
int p10[MAXN+1]; //p10[i]=(10^i)%k;
int k;

//used: 사용한 수, modVal: 지금 까지 만든수의 k에 대한 나머지
long long sequential_sum_count(int used, int modVal){
    if(used==(1<<nums.size())-1) return modVal==0;
    long long& ret=cache[used][modVal];
    if(ret!=-1) return ret;
    ret=0;
    for(int i=0;i<nums.size();i++){
        if(used & (1<<i)) continue;
        int newModVal=(((modVal%k)*(p10[nums[i].size()]%k))%k+modNums[i]%k)%k;
        ret+=sequential_sum_count(used | (1<<i),newModVal);
    }
    return ret;
}

void precal(){
    cache=vector<vector<long long>>(1<<nums.size(),vector<long long>(k,-1));
    p10[0]=1%k;
    for(int i=1;i<=MAXN;i++){
        p10[i]=((p10[i-1]%k)*(10%k))%k;
    }
    modNums.resize(nums.size());
    for(int i=0;i<modNums.size();i++){
        for(int j=0;j<nums[i].size();j++){
            modNums[i]+=(((nums[i][j]-'0')%k)*(p10[nums[i].size()-1-j]%k))%k;
        }
    }
    // for(int i=0;i<=MAXN;i++) cout << "p10["<<i<<"]: "<<p10[i] <<" ";
    // cout <<"\n";
    // for(int i=0;i<modNums.size();i++) cout << modNums[i]<<" ";
    // cout <<"\n";
}

long long factorial(int n){
    long long ret=1;
    for(int i=1;i<=n;i++) ret*=i;
    return ret;
}

long long gcd(long long a, long long b){ //a,b의 최대 공약수
    if(a<b) return gcd(b,a);
    if(b==0) return a;
    return gcd(b, a%b);
}

int main(){
    int n;
    cin >> n;
    nums.resize(n);
    for(int i=0;i<nums.size();i++){
        cin >> nums[i];
    }
    cin >> k;
    precal();
    long long p=sequential_sum_count(0,0);
    long long q=factorial(n);
    if(p==0) cout << "0/1" <<"\n";
    else if(p==q) cout << "1/1" <<"\n";
    else cout << p/gcd(p,q) <<"/"<<q/gcd(p,q)<<"\n";
    return 0;
}