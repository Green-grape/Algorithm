#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int NUMBER=10;

class Trie{
    bool isEnd;
    Trie* children[NUMBER]; 
    int char_to_index(char c){
        return c-'0';
    }
    public:
        Trie(){
            this->isEnd=false;
            memset(children,0,sizeof(children));
        }
        ~Trie(){
            for(int i=0;i<NUMBER;i++){
                if(children[i]){
                    delete children[i];
                }
            }
        }
        void insert(const string key){
            if(key.length()==0){
                isEnd=true;
            }
            else{
                int index=this->char_to_index(key[0]);
                if(children[index]==0){
                    children[index]=new Trie();
                }
                children[index]->insert(key.substr(1));
            }
        }
        Trie* find(const string key){
            if(key.length()==0){
                return this;
            }
            int index=this->char_to_index(key[0]);
            if(children[index]==0){
                return NULL;
            }
            return children[index]->find(key.substr(1));
        }
        bool isExist(const string key){
            if(key.length()==0 && isEnd){
                return true;
            }
            int index=this->char_to_index(key[0]);
            if(children[index]==0){
                return false;
            }
            return children[index]->isExist(key.substr(1));
        }
};

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        int numberCount;
        cin >> numberCount;
        Trie* trie=new Trie();
        vector<string> input;
        for(int i=0;i<numberCount;i++){
            char temp[11];
            scanf("%s", temp);
            input.push_back(string(temp));
        }
        sort(input.begin(), input.end());
        bool ret=true;
        for(int i=input.size()-1;i>=0;i--){
            if(trie->find(input[i])!=NULL){
                ret=false;
                break;
            }
            trie->insert(input[i]);
        }
        if(ret) cout <<"YES"<<"\n";
        else cout <<"NO"<<"\n";
    }
    return 0;
}