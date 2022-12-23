#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

//아이디어: 브루트포스

vector<int> isNotWalk(10);
int target;

bool isHaveNotWalkingBtn(int n){
    string s=to_string(n);
    for(int i=0;i<s.size();i++){
        if(isNotWalk[s[i]-'0']) return true;
    }
    return false;
}

int solve(){
    int ret=abs(target-100);
    for(int i=0;i<=1000000;i++){
        if(!isHaveNotWalkingBtn(i)){
            ret=min(ret, (int)(abs(target-i)+to_string(i).length()));
        }
    }
    return ret;
}

int main(){
    int notWalkingBtn;
    cin >> target >> notWalkingBtn;
    for(int i=0;i<notWalkingBtn;i++){
        int btn;
        cin >> btn;
        isNotWalk[btn]=true;
    }
    int ret=solve();
    cout << ret <<"\n";
    return 0;
}