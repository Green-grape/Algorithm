#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//문자열은 간단하게 생각하자!

using namespace std;

string getRemainString(string str, string del){
    vector<char> v;
    v.reserve(str.size());
    for(int i=0;i<str.size();i++){
        v.push_back(str[i]);
        int n=v.size()-1;
        int m=del.size()-1;
        while(0<=n && 0<=m && v[n]==del[m]){
            n--;
            m--;
        }
        if(m==-1){ //찾음
            for(int j=0;j<del.size();j++) v.pop_back();
        }
        // for(int j=0;j<v.size();j++) cout <<v[j];
        // cout <<"\n";
    }
    string ret="";
    ret.resize(v.size());
    for(int i=0;i<v.size();i++) ret[i]=v[i];
    if(ret.size()==0) return "FRULA";
    return ret;
}

int main(){
    string str, del;
    cin >> str >> del;
    cout <<getRemainString(str, del) <<"\n";
    return 0;
}