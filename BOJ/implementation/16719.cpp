#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

string str;
vector<bool> isUsed;
map<int,char> lastPrint;

void insert(pair<char,int> p){
    lastPrint[p.second]=p.first;
    for(map<int,char>::iterator it=lastPrint.begin();it!=lastPrint.end();it++){
        cout<<(*it).second;
    }
    cout <<"\n";
}

void alphabeticallyFastString(int from){
    string cur=string(str.begin()+from,str.end());
    vector<pair<char,int>> sortedStr;
    for(int i=0;i<cur.size();i++) sortedStr.push_back(make_pair(cur[i],i+from));
    sort(sortedStr.begin(),sortedStr.end());

    for(int i=0;i<sortedStr.size();i++){
        if(isUsed[sortedStr[i].second]) continue;
        isUsed[sortedStr[i].second]=true;
        insert(sortedStr[i]);
        alphabeticallyFastString(sortedStr[i].second+1);
    }
}

int main(){
    cin >> str;
    isUsed.resize(str.length());
    alphabeticallyFastString(0);
    return 0;
}