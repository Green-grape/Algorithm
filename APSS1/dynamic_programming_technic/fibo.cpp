#include <vector>

using namespace std;

//O(n) 반복적 동적 계획법
int fibo(int n){
    if(n<=1) return n;
    int fib[3];
    fib[0]=0;
    fib[1]=1;
    for(int i=2;i<=n;i++){
        fib[i%3]=fib[(i-1)%3]+fib[(i-2)%3];
    }
    return fib[n%3];
}

class SquareMatrix{
private:
    int n;
    vector<vector<int>> matrix;
public:
    SquareMatrix(int _n){
        this->n=_n;
        matrix=vector<vector<int>>(n,vector<int>(n,0));
    }
    int getSize(){
        return this->n;
    }
    vector<int> operator[](int n){
        return this->matrix[n];
    }
    SquareMatrix operator*(SquareMatrix matrix2){
        if(matrix[0].size()!=matrix2.getSize()) return NULL;
        SquareMatrix ret(n);
        for(int i=0;i<matrix.size();i++){
            for(int j=0;j<matrix.size();j++){
                for(int k=0;k<matrix.size();k++){
                    ret[i][j]+=matrix[i][k]*matrix[k][j];
                }
            }
        }
        return ret;
    }
};

SquareMatrix identity(int n){
    SquareMatrix ret(n);
    for(int i=0;i<n;i++) ret[i][i]=1;
    return ret;
}

//return A^n
SquareMatrix pow(const SquareMatrix& A, const int n){
    if(n==0) return identity(n);
    if(n%2>0) return pow(A,n-1)*A;
    SquareMatrix half=pow(A,n/2);
    return half*half; 
}

int fibo2(int n){
    if(n==0) return 0;
    SquareMatrix w(2);
    w[0][0]=0;
    w[0][1]=w[1][0]=w[1][1]=1;
    return pow(w,n-1)[1][1];
}