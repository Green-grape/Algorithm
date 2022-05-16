#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

int solve(string brackets){
    int left=0,right=0;;
    int ret=0;
    for(int i=0;i<brackets.length();i++){
        if(i!=brackets.length()-1 && brackets[i]=='(' && brackets[i+1]==')'){
            ret+=left-right; //잘린 부분 추가
            i++;
            continue;
        }
        if(brackets[i]=='('){
            left++;
        }
        else if(brackets[i]==')'){
            right++;
            ret+=1; //하나의 라인이 끝났으므로 나머지 1칸 처리
        }
    }
    return ret;
}

int main(){
    string brackets;
    cin >> brackets;
    cout << solve(brackets) <<"\n";
    return 0;
}
