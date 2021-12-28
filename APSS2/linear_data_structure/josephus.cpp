#include <iostream>
#include <list>

using namespace std;

list<int> remainNumber(int,int);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int peopleNum, jump;
        cin >> peopleNum >> jump;
        list<int> ret=remainNumber(peopleNum,jump);
        for(list<int>::iterator iter=ret.begin();iter!=ret.end();iter++){
            cout << *iter <<" ";
        }
        cout <<"\n";
    }
    return 0;
}

list<int> remainNumber(int peopleNum, int jump){
    list<int> ret;
    for(int i=1;i<=peopleNum;i++) ret.push_back(i);
    list<int>::iterator target=ret.begin();
    for(int i=0;i<peopleNum-2;i++){
        list<int>::iterator temp=target;
        for(int j=0;j<jump;j++){
            target++;
            if(target==ret.end()) target=ret.begin();
        }
        ret.erase(temp);
    }
    return ret;
}