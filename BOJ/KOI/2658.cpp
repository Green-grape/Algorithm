#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string itos(int num,int length){
    if(num==0) return string(length,'0');
    string ret="";
    while(num!=0){
        char c=num%10+'0';
        ret+=c;
        num/=10;
    }
    reverse(ret.begin(),ret.end());
    return ret;
}

string getClockNum(string s){
    string ret;
    int retNum=10000;
    for(int i=0;i<4;i++){
        int num=stoi(s);
        if(num<retNum){
            ret=s;
            retNum=num;
        }
        s=s.substr(1)+s[0];
    }
    return ret;
}

vector<string> precal(){
    vector<string> ret;
    for(int i=1111;i<=9999;i++){
        string num=itos(i,4);
        bool goNext=false;
        for(int j=0;j<num.size();j++){
            if(num[j]=='0'){
                goNext=true;
            }
        }
        if(goNext) continue;
        string clockNum=getClockNum(num);
        ret.push_back(clockNum);
    }
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(),ret.end()),ret.end());
    return ret;
}

int main(){
    vector<string> seq=precal();
    string num;
    for(int i=0;i<4;i++){
        char c;
        cin >> c;
        num+=c;
    }
    num=getClockNum(num);
    for(int i=0;i<seq.size();i++){
        if(seq[i].compare(num)==0){
            cout << i+1<<"\n";
            break;
        }
    }
    return 0;
}