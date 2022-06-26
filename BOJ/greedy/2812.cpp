/*N자리 숫자가 주어졌을 때, 여기서 숫자 K개를 지워서 얻을 수 있는 가장 큰 수를 구하는 프로그램을 작성하시오.*/

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

string getMaxDeletedNum(string num, int deleteCount){
    stack<char> s;
    s.push(num[0]);
    for(int i=1;i<num.length();i++){
        if(num[i]<=s.top()) s.push(num[i]);
        else{
            while(deleteCount>0 && !s.empty() && s.top()<num[i]){
                s.pop();
                deleteCount--;
            }
            s.push(num[i]);
            if(deleteCount==0){
                for(int j=i+1;j<num.length();j++) s.push(num[j]);
                break;
            }
        }
    }
    while(deleteCount>0 && !s.empty()){
        s.pop();
        deleteCount--;
    }
    string ret="";
    while(!s.empty()){
        ret+=s.top();
        s.pop();
    }
    reverse(ret.begin(),ret.end());
    if(ret.length()==0) ret+="0";
    return ret;
}

int main(){
    string num; int numCount, deleteCount;
    cin >> numCount >> deleteCount;
    cin >> num;
    cout << getMaxDeletedNum(num, deleteCount) <<"\n";
    return 0;
}