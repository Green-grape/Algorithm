#include <vector>
#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>

const int MAX_SUB_STRING=15;
const int MAX_SUB_STRING_LENGTH=40;
using namespace std;
const int MAX_STRING_LENGTH=MAX_SUB_STRING*MAX_SUB_STRING_LENGTH;
int cache[1<<MAX_SUB_STRING][MAX_SUB_STRING+1];
int sameCharCount[MAX_SUB_STRING][MAX_SUB_STRING]; //i->j순서로 문자열이 올때 겹치는 문자의 수
vector<string> subStrings;

void init();
int restore(int last, int used);
bool isAlreadyIn(string s);
string reconstruct(int last, int used);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int subStringCount;
        cin >> subStringCount;
        subStrings.resize(0);
        for(int j=0;j<subStringCount;j++){
            string s;
            cin >> s;
            if(!isAlreadyIn(s)) subStrings.push_back(s);
        }
        init();
        restore(-1, 0);
        cout << reconstruct(-1,0) <<"\n";
    }
    return 0;
}

bool isAlreadyIn(string s){
    for(int i=0;i<subStrings.size();i++){
        for(int j=0;j<subStrings[i].length();j++){
            if(subStrings[i][j]==s[0]){
                int sIdx=0;
                while(sIdx<s.length() && j<subStrings[i].length() && s[sIdx]==subStrings[i][j]){
                    sIdx++;
                    j++;
                }
                if(sIdx==s.length()) return true;
            }
        }
    }
    return false;
}

//전처리
void init(){
    memset(sameCharCount,0,sizeof(sameCharCount));
    memset(cache,-1,sizeof(cache));
    for(int i=0;i<subStrings.size();i++){
        for(int j=0;j<subStrings.size();j++){
            int i_start=subStrings[i].length()-1,i_element=1;
            int j_start=0,j_element=1;
            string i_sub="",j_sub="";
            while(i_start>=0 && j_start<subStrings[j].length()){
                i_sub=subStrings[i].substr(i_start,i_element);
                j_sub=subStrings[j].substr(j_start,j_element);
                i_start--;
                if(i_sub==j_sub) sameCharCount[i][j]++;
                else break;
                i_element++;
                j_element++;
            }
        }
    }
}

int restore(int last, int used){
    if(used==((1<<subStrings.size())-1)) return 0;
    int& ret=cache[used][last+1];
    if(ret!=-1) return ret;
    ret=0;
    for(int next=0;next<subStrings.size();next++){
        if((used & (1<<next))==0){
            int tempRet=0;
            if(last!=-1) tempRet+=sameCharCount[last][next];
            tempRet+=restore(next, used | (1<<next));
            ret=max(ret,tempRet);
        }
    }
    return ret;
}

string reconstruct(int last, int used){
    if(used==((1<<subStrings.size())-1)) return "";
    for(int next=0;next<subStrings.size();next++){
        if((used & (1<<next))!=0) continue;
        int ifUsed=0;
        if(last!=-1) ifUsed+=sameCharCount[last][next];
        ifUsed+=restore(next, used | (1<<next));
        if(ifUsed==restore(last,used)){
            int nextStart=0;
            if(last!=-1) nextStart=sameCharCount[last][next];
            return subStrings[next].substr(nextStart)+reconstruct(next, used | (1<<next));
        }
    }
    return "??";
}