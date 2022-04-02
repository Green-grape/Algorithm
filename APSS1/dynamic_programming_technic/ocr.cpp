#include <vector>
#include <iostream>
#include <cmath>
#include <map>

const int MAX_WORD_COUNT=500;
const int MAX_SENTENCE_COUNT=100;
const int MAX_SENTENCE_LENGTH=100;
using namespace std;


vector<string> word;
map<string,int> wordMap;
vector<double> pStart; //pStart[i]=i가 문장의 시작일 확률
double pNext[MAX_WORD_COUNT][MAX_WORD_COUNT]; //pNext[i][j]=i다음이 j일 확률
double pClassify[MAX_WORD_COUNT][MAX_WORD_COUNT]; //pClassify[i][j]=i를 j로 분류할 확률
double cache[MAX_SENTENCE_COUNT+1][MAX_WORD_COUNT+1];
int choice[MAX_SENTENCE_COUNT+1][MAX_WORD_COUNT+1];

void init();
string reconstruct(int idx,int prev,vector<string>&);
double solution(int idx, int prev, vector<string>& sentence);

int main(){
    //빠른 입출력
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);

    int wordCount, sentenceCount;
    cin >> wordCount >> sentenceCount;
    for(int i=0;i<wordCount;i++){
        string w;
        cin >> w;
        word.push_back(w);
        wordMap[w]=i;
    }
    for(int i=0;i<wordCount;i++){
        double p;
        cin >> p;
        pStart.push_back(log10(p));
    }
    for(int i=0;i<wordCount;i++){
        for(int j=0;j<wordCount;j++){
            cin >> pNext[i][j];
            pNext[i][j]=log10(pNext[i][j]); //나중에 곱셈이 너무 작아져서 언더플로우 나는 것을 방지
        }
    }
    for(int i=0;i<wordCount;i++){
        for(int j=0;j<wordCount;j++){
            cin >> pClassify[i][j];
            pClassify[i][j]=log10(pClassify[i][j]); //나중에 곱셈이 너무 작아져서 언더플로우 나는 것을 방지
        }
    }
    for(int i=0;i<sentenceCount;i++){
        int sentenceLength;
        cin >> sentenceLength;
        vector<string> sentence;
        for(int j=0;j<sentenceLength;j++){
            string s;
            cin >> s;
            sentence.push_back(s);
        }
        init();
        solution(0,-1,sentence);
        string ret=reconstruct(0,-1, sentence);
        cout << ret <<"\n";
    }
    return 0;
}

void init(){
    for(int i=0;i<MAX_SENTENCE_COUNT+1;i++){
        for(int j=0;j<MAX_WORD_COUNT+1;j++){
            cache[i][j]=1.0;
        }
    }
}

//원본 문장을 Q, 사본 문장을 R이라고 하자.
//idx:sentence의 idx, prev:원본의 이전 단어 위치
//우리가 원하는 값은 idx가 0~word.size()-1 까지 pClassify[i][wordMap[sentence[idx]]]+pNext[prev][i] (0<=i<=word.size()-1)의 합의 최대값이다.
//solution의 반환 값은 idx부터의 합의 최대이며 Q[idx-1]=word[prev]이다.
double solution(int idx, int prev, vector<string>& sentence){
    if(idx==sentence.size()) return 0;
    double ret=cache[idx][prev+1];
    if(ret!=1.0) return ret;
    ret=-1e200;
    int& choose=choice[idx][prev+1];
    if(prev==-1){
        for(int i=0;i<word.size();i++){
            double tRet=pStart[i]+solution(idx+1,i,sentence);
            if(tRet>ret){
                ret=tRet;
                choose=i;
            }
        }
        return ret;
    }
    int cur=wordMap[sentence[idx]];
    for(int i=0;i<word.size();i++){
        double tRet=pClassify[i][cur]+pNext[prev][i]+solution(idx+1,i,sentence);
        if(tRet>ret){
            ret=tRet;
            choose=i;
        }
    }
    return ret;
}

string reconstruct(int idx,int prev, vector<string>& sentence){
    int choose=choice[idx][prev+1];
    string ret=word[idx];
    if(idx<sentence.size()-1){
        ret=ret+" "+reconstruct(idx+1,choose,sentence);
    }
    return ret;
}