#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> v;
    for(int i=0;i<3;i++){
        int val;
        cin >> val;
        v.push_back(val);
    }
    sort(v.begin(),v.end());
    for(int i=0;i<v.size();i++){
        cout << v[i] <<" ";
    }
    return 0;
}