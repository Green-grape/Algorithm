#include <iostream>
#include <vector>
#include <string>

using namespace std;

int getMinMovingDial(const vector<string>&);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int statusCount;
        cin >> statusCount;
        vector<string> statuses;
        for(int j=0;j<statusCount+1;j++){
            string temp;
            cin >> temp;
            statuses.push_back(temp);
        }
        cout << getMinMovingDial(statuses) << "\n";
    }
    return 0;
}

vector<int> getParialMatch(const string& str){
    //자기 자신에 대한 kmpSearch 수행
    int begin=1, matched=0;
    vector<int> p(str.length(),0);
    while(begin+matched<str.length()){
        if(str[begin+matched]==str[matched]){
            p[begin+matched]=matched+1;
            matched++;
        }else{
            if(matched==0) begin++;
            else{
                begin+=matched-p[matched-1];
                matched=p[matched-1];
            }
        }
    }
    return p;
}

vector<int> kmpSearch(const string& str1, const string& str2){
    int begin=0, matched=0;
    vector<int> partialMatch=getParialMatch(str2);
    vector<int> ret;
    while(begin+matched<str1.length()){
        if(str1[begin+matched]==str2[matched]){
            matched++;
            if(matched==str2.length()) ret.push_back(begin);
        }
        else{
            if(matched==0) begin++;
            else{
                begin+=matched-partialMatch[matched-1];
                matched=partialMatch[matched-1];
            }
        }
    }
    return ret;
}

int shiftReverseClockwise(const string& original, const string& target){
    return kmpSearch(original+original, target)[0];
}

int shiftClockwise(const string& original, const string& target){
    return shiftReverseClockwise(target,original);
}

int getMinMovingDial(const vector<string>& statuses){
    int ret=0;
    for(int i=1;i<statuses.size();i++){
        if(i%2){//시계
           ret+=shiftClockwise(statuses[i-1],statuses[i]);
        }
        else{
            ret+=shiftReverseClockwise(statuses[i-1], statuses[i]);
        }
    }
    return ret;
}

