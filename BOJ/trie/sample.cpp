#include <cstring>
#include <string>
using namespace std;

const int ALPHABETS=26;

class Trie{
    bool isEnd;
    Trie* children[ALPHABETS]; 
    int char_to_index(char c){
        return c-'a';
    }
    public:
        Trie(){
            this->isEnd=false;
            memset(children,0,sizeof(children));
        }
        ~Trie(){
            for(int i=0;i<ALPHABETS;i++){
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