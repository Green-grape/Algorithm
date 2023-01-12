#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

vector<vector<int>> makeRotation(vector<int> arr){
    vector<vector<int>> ret;
    for(int i=0;i<arr.size();i++){
        ret.push_back(arr);
        int temp=arr[0];
        arr=vector<int>(arr.begin()+1,arr.end());
        arr.push_back(temp);
    }
    return ret;
}

//같은 모양 미리 만들기
vector<vector<int>> precal(vector<int> arr){
    vector<vector<int>> ret=makeRotation(arr);
    //reverse
    for(int i=0;i<arr.size();i++){
        if(arr[i]==1) arr[i]=3;
        else if(arr[i]==3) arr[i]=1;
        else if(arr[i]==2) arr[i]=4;
        else if(arr[i]==4) arr[i]=2;
    }
    reverse(arr.begin(), arr.end());
    vector<vector<int>> back=makeRotation(arr);
    ret.insert(ret.end(),back.begin(), back.end());
    return ret;
}

bool isSame(vector<int>& arr, vector<vector<int>> &shapes){
    bool ret=false;
    for(int i=0;i<shapes.size();i++){
        ret|=(arr==shapes[i]);
        if(ret) break;
    }
    return ret;
}

int main(){
    int arrLength;
    cin >> arrLength;
    vector<int> arr(arrLength);
    for(int i=0;i<arrLength;i++){
        scanf("%d", &arr[i]);
    }
    vector<vector<int>> sameShapes=precal(arr);
    int cmpCnt;
    cin >> cmpCnt;
    vector<vector<int>> ret;
    for(int i=0;i<cmpCnt;i++){
        vector<int> compare(arrLength);
        for(int j=0;j<arrLength;j++){
            scanf("%d", &compare[j]);
        }
        if(isSame(compare, sameShapes)){
            ret.push_back(compare);
        }
    }
    cout << ret.size() <<"\n";
    for(int i=0;i<ret.size();i++){
        for(int j=0;j<ret[i].size();j++){
            cout << ret[i][j] <<" ";
        }
        cout << "\n";
    }
    return 0;
}