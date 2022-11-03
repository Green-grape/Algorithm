#include <iostream>
#include <vector>

using namespace std;

const int MOD=1000;
int n;

class Matrix{
public:
    vector<vector<int>> value;
    Matrix(){

    }
    Matrix(vector<vector<int>> _value){
        this->value=_value;
    }
    Matrix operator*(Matrix m){
        vector<vector<int>> ret(value.size(), vector<int>(m.value[0].size()));
        for(int i=0;i<ret.size();i++){
            for(int j=0;j<ret[i].size();j++){
                for(int k=0;k<ret[i].size();k++){
                    ret[i][j]=(ret[i][j]%MOD+(value[i][k]*m.value[k][j])%MOD)%MOD;
                }
            }
        }
        return Matrix(ret);
    }
};

Matrix unit;

Matrix getMatrix(Matrix cur, const long long mul){
    if(mul==0) return unit;
    if(mul==1) return cur;

    Matrix half=getMatrix(cur,mul/2);
    if(mul%2==0){
        return half*half;
    }else{
        return half*half*cur;
    }
}


int main(){
    long long mul;
    cin >> n >> mul;
    vector<vector<int>> unitV(n, vector<int>(n));
    for(int i=0;i<n;i++) unitV[i][i]=1;
    unit.value=unitV;
    vector<vector<int>> value(n, vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> value[i][j];
        }
    }
    Matrix matrix(value);
    Matrix ret=getMatrix(matrix,mul);
    for(int i=0;i<ret.value.size();i++){
        for(int j=0;j<ret.value[i].size();j++){
            cout << ret.value[i][j]%MOD <<" ";
        }
        cout <<"\n";
    }
    return 0;
}