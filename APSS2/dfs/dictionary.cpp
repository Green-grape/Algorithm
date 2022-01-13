#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> words;
typedef char vertex;
vector<char> res;
vector<vector<vertex>> nextVertex(26,vector<vertex>());
vector<vector<bool>> adjacent(26, vector<bool>(26,false));
vector<bool> visit(26,false);

vector<char> topologicalSort(const vector<vector<vertex>>&);
void makeDictionaryGraph(const vector<string>&);
void initialize();

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        int wordCount;
        cin >> wordCount;
        for(int j=0;j<wordCount;j++){
            string word;
            cin >> word;
            words.push_back(word);
        }
        makeDictionaryGraph(words);
        vector<char> result=topologicalSort(nextVertex);
        if(result.size()==0) cout <<"INVALID HYPOTHESIS";
        for(int k=0;k<result.size();k++) cout << result[k];
        cout << "\n";

        initialize();
    }
}

void initialize(){
    words.resize(0);
    res.resize(0);
    for(int k=0;k<nextVertex.size();k++) nextVertex[k].resize(0);
    for(int n=0;n<adjacent.size();n++){
        for(int m=0;m<adjacent[n].size();m++){
            adjacent[n][m]=false;
        }
    }
    for(int k=0;k<visit.size();k++) visit[k]=false;
}

pair<char,char> getPointOfSequence(const string& str1, const string& str2){
    for(int i=0;i<str1.length() && i<str2.length();i++){
        if(str1[i]!=str2[i]){
            return pair<char,char>(str1[i],str2[i]);
        }
    }
    return pair<char,char>(0,0);
}

//v[alpha-'a']=alpha보다 사전상 뒤에 있는 문자들
void makeDictionaryGraph(const vector<string>& words){
    for(int i=1;i<words.size();i++){
        pair<char,char> point=getPointOfSequence(words[i-1],words[i]);
        if(point.first!=0){
            nextVertex[point.first-'a'].push_back(point.second);
            adjacent[point.first-'a'][point.second-'a']=true;
        }
    }
}

void dfs(int i){
    visit[i]=true;
    char c=i+'a';
    for(int j=0;j<nextVertex[i].size();j++){
        vertex v=nextVertex[i][j];
        if(!visit[v-'a']){
            dfs(v-'a');
        }
    }
    res.push_back(c);
}


vector<char> topologicalSort(const vector<vector<vertex>>& graph){
    for(int i=0;i<graph.size();i++){
        if(!visit[i]) dfs(i);
    }
    reverse(res.begin(),res.end());
    for(int i=0;i<graph.size();i++){
        for(int j=0;j<graph[j].size();j++){
            if(adjacent[res[j]-'a'][res[i]]-'a') return vector<char>();
        }
    }
    return res;
}
    