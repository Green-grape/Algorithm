#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int testCase;
    cin >> testCase;
    while(testCase--){
        vector<int> values;
        vector<int> ret;
        int treeSize;
        cin >> treeSize;
        values.resize(treeSize);
        for(int i=1;i<=treeSize;i++){
            cin >> values[i-1];
            if(i%2){
                sort(values.begin(),values.begin()+i);
                ret.push_back(values[i/2]);
            }
        }
        int count=0;
        cout << ret.size() <<"\n";
        for(int i=0;i<ret.size();i++){
            cout << ret[i] <<" ";
            count++;
            if(count==10){
                cout <<"\n";
                count=0;
            }
        }
    }
    return 0;
}