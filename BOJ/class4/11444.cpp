#include <iostream>
#include <vector>

using namespace std;

const int MOD=1000000007;

class Matrix{
    vector<vector<long long>> value;
public:
    Matrix(){

    }
    Matrix(vector<vector<long long>> _value){
        value=_value;
    }
    vector<long long> operator[](int idx){
        return value[idx];
    }
    Matrix operator*(Matrix mat){
        vector<vector<long long>> ret(mat.value.size(), vector<long long>(mat.value[0].size()));
        for(int i=0;i<ret.size();i++){
            for(int j=0;j<ret[i].size();j++){
                for(int k=0;k<ret[i].size();k++){
                    ret[i][j]=(ret[i][j]%MOD+(value[i][k]*mat.value[k][j])%MOD)%MOD;
                }
            }
        }
        return Matrix(ret);
    }
};

Matrix base({{1,1},{1,0}});
Matrix unit({{1,0},{0,1}});

Matrix pow(Matrix cur, long long n){
    if(n==0) return unit;
    if(n==1) return cur;
    Matrix half=pow(cur,n/2);
    if(n%2==0) return half*half;
    else return half*half*cur;
}

//Fn=Fn-1+Fn-2를 행렬로 변경하자
//[Fn]=[1,1][Fn-1,Fn-2]T
//Fn=Fn+0*Fn-1이므로
//[Fn-1]=[1,0][Fn-1,Fn-2]이므로 두 식을 합치면
//[Fn]= [1,1][Fn-1]이고 F1=1, F0=0임을 생각하면
//[Fn-1] [1,0][Fn-2]

//[Fn+1]= [1,1]^n * [1]
//[Fn] [1,0]    [0]
int fibo(long long n){
    Matrix baseN=pow(base,n);
    //cout << baseN[0][0] << " " <<baseN[0][1]<<"\n";
    //cout << baseN[1][0] << " " <<baseN[1][1]<<"\n";
    Matrix m0({{1},{0}});
    Matrix ret=baseN*m0;
    return ret[1][0];
}

int main(){
    long long n;
    cin >> n;
    cout << fibo(n)%MOD <<"\n";
    return 0;
}

