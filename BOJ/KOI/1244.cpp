#include <iostream>
#include <vector>

using namespace std;

vector<bool> changeMuliple(vector<bool> switches, int idx){
    for(int i=idx;i<switches.size();i+=idx){
        switches[i]=!switches[i];
    }
    return switches;
}

vector<bool> changeSymmetric(vector<bool> switches, int idx){
    int left=idx,right=idx;
    while(1<=left && right<switches.size() && switches[left]==switches[right]){
        if(left==right){
            switches[left]=!switches[left];
        }else{
            switches[left]=!switches[left];
            switches[right]=!switches[right];
        }
        left--;
        right++;
    }
    return switches;

}

vector<bool> (*change[2])(vector<bool>,int)={changeMuliple,changeSymmetric};

int main(){
    int n;
    cin >> n;
    vector<bool> switches(n+1);
    for(int i=1;i<=n;i++){
        int cur;
        cin >> cur;
        if(cur) switches[i]=true;
    }
    int changeCnt;
    cin >> changeCnt;
    for(int i=0;i<changeCnt;i++){
        int changeKind,idx;
        cin >> changeKind >>idx;
        switches=change[changeKind-1](switches,idx);
    }
    int printCnt=0;
    for(int j=1;j<switches.size();j++){
        cout << (switches[j] ? 1:0) <<" ";
        printCnt++;
        if(printCnt==20){
            cout <<"\n";
            printCnt=0;
        }
    }
    cout <<"\n";
    return 0;
}