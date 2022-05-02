//그룹 단어 체커
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

bool isGroupWord(std::string s){
    int check[26]={0,};
    for(int i=0;i<s.length();i++){
        if(!check[s[i]-'a']){ //아직 한번도 안나온 경우
            check[s[i]-'a']=1;
        }else{ //한번이라도 나온 경우
            if(s[i-1]-'a'!=s[i]-'a') return false;
        }
    }
    return true;
}

int main(){
    int wordCount;
    std::cin >> wordCount;
    int ret=0;
    for(int i=0;i<wordCount;i++){
        std::string s;
        std::cin>> s;
        if(isGroupWord(s)) ret++;
    }
    std::cout << ret <<"\n";
    return 0;
}