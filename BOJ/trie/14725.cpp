#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

const int MAX_CHILD=1000;

class Trie{
    vector<Trie*> children;
    static map<string,int> dic;
    static vector<pair<string,int>> inputs;
    static int childCount;
    bool isSorted=false;
    int toIndex(string s){
        if(dic.find(s)==dic.end()){
            Trie::dic[s]=Trie::dic.size();
            inputs.push_back(make_pair(s,dic[s]));
        }
        int index=Trie::dic[s];
        return index;
    }
    void prePrintNode(){
        sort(inputs.begin(), inputs.end());
        isSorted=true;
    }
    public:
        Trie(){
            this->children=vector<Trie*>(childCount, NULL);
        }
        void insert(vector<string>& keys, int cur){
            if(cur==keys.size()){
                return;
            }
            int index=toIndex(keys[cur]);
            if(this->children[index]==NULL){
                this->children[index]=new Trie();
            }
            this->children[index]->insert(keys, cur+1);
        }
        void printNode(int depth){
            if(!isSorted) prePrintNode();
            for(int i=0;i<inputs.size();i++){
                int index=inputs[i].second;
                string s=inputs[i].first;
                //cout << index << " " <<s <<"\n";
                if(this->children[index]!=NULL){
                    cout << string(depth*2,'-') << s <<"\n";
                    this->children[index]->printNode(depth+1);
                }
            }
        }
};

map<string,int> Trie::dic=map<string,int>();
vector<pair<string,int>>Trie::inputs=vector<pair<string,int>>();
int Trie::childCount=MAX_CHILD;

int main(){
    int childCount;
    cin >>childCount;
    Trie* trie=new Trie();
    for(int i=0;i<childCount;i++){
        int keyCount;
        cin >> keyCount;
        vector<string> keys(keyCount);
        for(int j=0;j<keyCount;j++){
            cin >> keys[j];
        }
        trie->insert(keys,0);
    }
    trie->printNode(0);
    return 0;
}