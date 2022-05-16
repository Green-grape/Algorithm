#include <iostream>
#include <stack>
#include <vector>

using namespace std;
/*복습*/
vector<char> solve(vector<int>& arr){
    stack<int> s;
    vector<char> ret;
    int pushcount=1;
    for(int i=0;i<arr.size();i++){
        while(pushcount<=arr[i]){
            s.push(pushcount);
            pushcount++;
            ret.push_back('+');
        }
        if(s.top()==arr[i]){
            s.pop();
            ret.push_back('-');
        }
        else return vector<char>();
    }
    return ret.size()==2*arr.size() ? ret: vector<char>();
}

int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    vector<char> ret=solve(arr);
    if(ret.size()==0) cout <<"NO"<<"\n";
    else{
        for(int i=0;i<ret.size();i++){
            cout << ret[i] <<"\n";
        }
    }
    return 0;
}