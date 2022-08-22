#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int n=0;
    string name;
    map<string, int> treeCounts;
    char tempName[31];
    while(scanf("%[^\n]s",tempName)!=EOF){
        getchar();
        name=tempName;
        if(treeCounts.find(name)==treeCounts.end()){
            treeCounts[name]=1;
        }else{
            int cur=treeCounts[name];
            treeCounts.erase(name);
            treeCounts[name]=cur+1;
        }
        n++;
    }
    vector<pair<string,int>> trees;
    for(auto treeCount:treeCounts){
        trees.push_back(make_pair(treeCount.first,treeCount.second));
    }
    sort(trees.begin(),trees.end());
    cout << fixed;
    cout.precision(4);
    for(int i=0;i<trees.size();i++){
        cout << trees[i].first << " " << trees[i].second/(double)n*100 <<"\n";
    }
    return 0;
}