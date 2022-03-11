#include <vector>
#include <iostream>
using namespace std;

int main(){
    vector<int> a(2,1);
    vector<int> overFlow(2,0);
    a.insert(a.begin(), overFlow.begin(), overFlow.end());
    for(int i=0;i<a.size();i++) cout <<a[i]<<"\n";
}