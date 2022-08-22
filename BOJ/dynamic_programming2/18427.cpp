/*
1번부터 N번까지의 학생들은 각각 블록들을 가지고 있다. 학생마다 최대 M개의 블록을 가지고 있을 수 있으며, 한 명의 학생이 가지고 있는 모든 블록들의 높이는 서로 다르다. 이 때 1번부터 N번까지의 학생들이 가진 블록을 차례대로 사용하여 바닥에서부터 쌓아올려 하나의 탑을 만들고자 한다.

단, 어떤 학생의 블록은 사용하지 않아도 되며 한 학생당 최대 1개의 블록만을 사용할 수 있다.

1번부터 N번까지의 학생들이 가지고 있는 블록들에 대한 정보가 주어졌을 때, 높이가 정확히 H인 탑을 만들 수 있는 경우의 수를 계산하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAXN=50;
const int MAX_HEIGHT=1000;
const int MOD=10007;

vector<vector<int>> cache(MAXN, vector<int>(MAX_HEIGHT+1,-1));
vector<vector<int>> blocks; //blocks[i]=i번째 학생이 가지고 있는 블록목록

int kindOfHeight(int from, int remainHeight){
    if(remainHeight==0) return 1;
    if(from==blocks.size()) return 0;
    int& ret=cache[from][remainHeight];
    if(ret!=-1) return ret;
    ret=0;
    for(int i=0;i<blocks[from].size();i++){
        int blockHeight=blocks[from][i];
        if(remainHeight-blockHeight>=0) ret=(ret+kindOfHeight(from+1,remainHeight-blockHeight))%MOD;
    }
    ret=(ret+kindOfHeight(from+1,remainHeight))%MOD;
    return ret;
}

vector<string> mySplit(string s, char delim){
    vector<string> ret;
    string::size_type searched=0;
    string::size_type start=0;
    string::size_type end=0;
    do{
        end=s.find(delim,searched);
        if(end==string::npos){
            ret.push_back(string(s.begin()+start,s.end()));
            break;
        }
        ret.push_back(string(s.begin()+start,s.begin()+end));
        start=searched=end+1;
    }while(true);
    return ret;
}

vector<int> myStoi(vector<string> v){
    vector<int> ret;
    for(int i=0;i<v.size();i++){
        ret.push_back(stoi(v[i]));
    }
    return ret;
}

int main(){
    int n,m,h;
    cin >> n >> m >> h;
    blocks.resize(n);
    getchar(); /*어떤 데이터형(int or char)과 string형을 연달아 입력받을 때 getline 버퍼에 입력된 줄바꿈 문자를 받아들여 버리는데 이를 막기위해서 사이에 getchar()를 삽입해줄 수 있다.*/
    for(int i=0;i<n;i++){
        string heights;
        getline(cin, heights);
        blocks[i]=myStoi(mySplit(heights,' '));
    }
    cout << kindOfHeight(0,h);
    return 0;
}