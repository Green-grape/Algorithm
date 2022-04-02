#include <vector>
#include <iostream>
#include <string.h>

const int MAX_LENGTH=4;
const int MAX_SONG=50;
using namespace std;

vector<double> getFavoriteSongProbability(const vector<vector<double>>& pNext, const vector<int>& favoriteSong, const vector<int>& songLength, int playTime);
vector<double> getFavoriteSongProbability2(const vector<vector<double>>& pNext, const vector<int>& favoriteSong, const vector<int>& songLength, int playTime);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int musicCount, playTime, favoriteCount;
        cin >> musicCount >> playTime >> favoriteCount;
        vector<vector<double>> pNext(musicCount,vector<double>(musicCount));
        vector<int> favoriteSong(favoriteCount);
        vector<int> songLength(musicCount);
        for(int j=0;j<songLength.size();j++){
            cin >> songLength[j];
        }
        for(int j=0;j<musicCount;j++){
            for(int k=0;k<musicCount;k++){
                cin >> pNext[j][k];
            }
        }
        for(int j=0;j<favoriteCount;j++){
            cin >> favoriteSong[j];
        }
        vector<double> ret=getFavoriteSongProbability2(pNext, favoriteSong, songLength,playTime);
        for(int j=0;j<ret.size();j++){
            cout << ret[j] <<" ";
        }
        cout << "\n";
    }
    return 0;
}

double cache[MAX_LENGTH+1][MAX_SONG]; //cache[time][song]=time분일때 song이 시작될 확률
vector<double> getFavoriteSongProbability(const vector<vector<double>>& pNext, const vector<int>& favoriteSong, const vector<int>& songLength, int playTime){
    memset(cache,0,sizeof(cache));
    cache[0][0]=1.0;
    for(int time=1;time<=playTime;time++){
        for(int i=0;i<songLength.size();i++){
            double& prob=cache[time%(MAX_LENGTH+1)][i];
            prob=0;
            for(int prev=0;prev<songLength.size();prev++){
                if(time>=songLength[prev]) prob+=cache[(time-songLength[prev])%(MAX_LENGTH+1)][prev]*pNext[prev][i];
            }
        }
    }
    vector<double> ret(songLength.size());
    for(int i=0;i<favoriteSong.size();i++){
        for(int start=playTime-songLength[i]+1;start<=playTime;start++){
            ret[i]+=cache[start%(MAX_LENGTH+1)][i];
        }
    }
    return ret;
}

class SquareMatrix{
private:
    int n;
public:
    vector<vector<double>> matrix;
    SquareMatrix(int _n){
        this->n=_n;
        matrix=vector<vector<double>>(n,vector<double>(n,0));
    }
    int size(){
        return this->n;
    }
    void set(int x, int y,double val){matrix[x][y]=val;}
    vector<double>& operator[](int n){
        return this->matrix[n];
    }
    SquareMatrix operator*(SquareMatrix matrix2){
        if(matrix[0].size()!=matrix2.size()) return matrix2;
        SquareMatrix ret(n);
        for(int i=0;i<matrix.size();i++){
            for(int j=0;j<matrix.size();j++){
                for(int k=0;k<matrix.size();k++){
                    ret[i][j]+=matrix[i][k]*matrix2[k][j];
                }
            }
        }
        return ret;
    }
    SquareMatrix operator*(vector<vector<double>> matrix2){
        if(matrix[0].size()!=matrix2.size()) return SquareMatrix(matrix2.size());
        SquareMatrix ret(n);
        for(int i=0;i<matrix.size();i++){
            for(int j=0;j<matrix.size();j++){
                for(int k=0;k<matrix.size();k++){
                    ret[i][j]+=matrix[i][k]*matrix2[k][j];
                }
            }
        }
        return ret;
    }
    SquareMatrix identity(int n){
        SquareMatrix ret(n);
        for(int i=0;i<n;i++) ret[i][i]=1;
        return ret;
    }
    SquareMatrix pow(const int n){
        if(n==0) return identity(matrix.size());
        if(n%2>0) return pow(n-1)*matrix;
        SquareMatrix half=pow(n/2);
        return half*half; 
    }
};

//C[time+1]=WxC[time]인 W를 찾아서 행렬곱을 찾는다.
//start(time,song): time일때 song이 시작할 확률
//C[time]=[
//     [start(time-3,0)],
//     [start(time-3,1)],
//     ..
//     [start(time-3,songCount-1)],
//     [start(time-2,0)],
//     [start(time-2,1)],
//     ..
//     [start(time-2,songCount-1)],
//     [start(time-1,0)],
//     [start(time-1,1)],
//     ..
//     [start(time-1,songCount-1)],
//     [start(time,0)],
//     [start(time,1)],
//     ..
//     [start(time,songCount-1)],
// ]
vector<double> getFavoriteSongProbability2(const vector<vector<double>>& pNext, const vector<int>& favoriteSong, const vector<int>& songLength, int playTime){
    SquareMatrix w(4*songLength.size());
    //time+1의 첫 3*n원소는 그대로 가져온다.
    int n=songLength.size();
    for(int i=0;i<3*n;i++){
        w[i][i+n]=1.0;
    }
    for(int i=3*n;i<4*n;i++){
        for(int j=0;j<4*n;j++){
            int timeDif=4-j/n;
            if(timeDif==songLength[j%n]){
                w[i][j]=pNext[j%n][i%n];
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            w[3*n+i][(4-songLength[j])*n+j]=pNext[j][i];
        }
    }
    SquareMatrix wk=w.pow(playTime);
    vector<double> ret(n);
    for(int i=0;i<favoriteSong.size();i++){
        for(int start=0;start<songLength[i];start++){
            ret[i]+=wk[(3-start)*n+i][3*n]; 
        }
    }
    return ret;
}