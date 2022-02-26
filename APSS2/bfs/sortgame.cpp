/*
직관적인 해결책 but 느림...
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

int getMinReverseToSort(const vector<int>);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int arrLength;
        cin >> arrLength;
        vector<int> arr;
        for(int j=0;j<arrLength;j++){
            int num;
            cin >> num;
            arr.push_back(num);
        }
        cout << getMinReverseToSort(arr) <<"\n";
    }
    return 0;
}

bool isSameArr(vector<int> arr1, vector<int> arr2){
    return equal(arr1.begin(),arr1.begin()+arr1.size(),arr2.begin());
}

bool isCanBeSameByOneReverse(vector<int> arr1, vector<int> arr2){
    //[i,j]를 뒤집어 보면서 확인한다. 
    for(int i=0;i<arr1.size();i++){
        for(int j=i;j<arr1.size();j++){
            vector<int> ori=arr1;
            if(j==arr1.size()-1) reverse(arr1.begin()+i,arr1.end());
            else reverse(arr1.begin()+i,arr1.begin()+j+1);
            if(isSameArr(arr1,arr2)) return true;
            arr1=ori;
        }
    }
    return false;
}

//배열을 하나의 정점으로 하고 그 배열을 한 번 뒤집어서 도달할수 있는 배열을 adj에 추가한다.
pair<pair<int,int>, vector<vector<int>>> makeGraph(const vector<int> arr){
    vector<vector<int>> possibleArrs;
    vector<int> sortedArr=arr;
    sort(sortedArr.begin(),sortedArr.end());
    do{
        possibleArrs.push_back(sortedArr);
    }while(next_permutation(sortedArr.begin(),sortedArr.end()));

    vector<vector<int>> adj(possibleArrs.size());
    int start=-1;
    int target=0;
    for(int i=0;i<possibleArrs.size();i++){
        if(isSameArr(possibleArrs[i],arr)) start=i;
        cout << i <<"\n";
        for(int j=i+1;j<possibleArrs.size();j++){
            if(isCanBeSameByOneReverse(possibleArrs[i],possibleArrs[j])){
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    return make_pair(make_pair(start,target), adj);
}

//start로부터 target까지의 최단 거리 반환 with bfs
int getMinDistances(int start, int target, vector<vector<int>> adj){
    vector<int> distance=vector<int>(adj.size(),-1);
    queue<int> q;
    distance[start]=0;
    q.push(start);
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=0;i<adj[cur].size();i++){
            int next=adj[cur][i];
            if(distance[next]==-1){
                q.push(next);
                distance[next]=distance[cur]+1;
            }
        }
    }
    return distance[target];
}

int getMinReverseToSort(const vector<int> arr){
    pair<pair<int,int>, vector<vector<int>>> graphEl=makeGraph(arr);
    int start=graphEl.first.first;
    int target=graphEl.first.second;
    vector<vector<int>> adj=graphEl.second;
    cout <<"d"<<"\n";
    return getMinDistances(start,target,adj);
}