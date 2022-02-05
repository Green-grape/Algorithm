#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> words;
vector<vector<int>> adjacent;
vector<vector<vector<string>>> nextString;
vector<int> inDegree;
vector<int> outDegree;
string getWordChain();

int main(){
    int testCase;
    cin >> testCase;
    vector<string> res;
    for(int i=0;i<testCase;i++){
        words=vector<string>();
        int wordCount;
        cin >> wordCount;
        for(int j=0;j<wordCount;j++){
            string s;
            cin >> s;
            words.push_back(s);
        }
        res.push_back(getWordChain());
    }
    for(int i=0;i<res.size();i++){
        cout << res[i] <<"\n";
    }
    return 0;
}

void makeGraph(){
    adjacent=vector<vector<int>>(26, vector<int>(26,0));
    nextString=vector<vector<vector<string>>>(26,vector<vector<string>>(26,vector<string>()));
    inDegree=vector<int>(26,0);
    outDegree=vector<int>(26,0);
    
    for(int i=0;i<words.size();i++){
        char start=words[i][0]-'a';
        char end=words[i][words[i].length()-1]-'a';
        adjacent[start][end]++;
        nextString[start][end].push_back(words[i]);
        inDegree[end]++;
        outDegree[start]++;
    }
}

void printGraph(){
    for(int i=0;i<adjacent.size();i++){
        for(int j=0;j<adjacent[i].size();j++){
            cout << adjacent[i][j]<<" ";
        }
        cout <<"\n";
    }
}

//circuit에 EulerCircle의 역순이 삽입된다.
void getEulerCircuit(const int vertex, vector<int>& circuit){
    for(int i=0;i<adjacent[vertex].size();i++){
        while(adjacent[vertex][i]!=0){
            adjacent[vertex][i]--;
            getEulerCircuit(i,circuit);
        }
    }
    //circuit에는 vertex의 이후의 점들이 이미 등록이 되어있다. -> why? 
    //vertex에서 갈 수 있는 모든 점들이 이미 circuit에 추가가 되어있다. while문 때문에
    //vertex만 추가해주면 EulerCircle의 vertex~end의 점들이 역순으로 추가되어있다.
    circuit.push_back(vertex);
    
}

//start->end로 가면서 모든 간선을 지나는 경로인 EulerTrail 구하기
//end->start로 간선을 추가한 후 start->start의 EulerCircuit을 구한후 end->start 제거

vector<int> mergeVector(const vector<int>& front, const vector<int>& back){
    if(front.empty()) return back;
    if(back.empty()) return front;
    vector<int> res;
    res.reserve(front.size()+back.size());
    res.insert(res.end(),front.begin(),front.end());
    res.insert(res.end(),back.begin(),back.end());
    return res;
}

vector<int> removeEdge(const int start, const int end, vector<int>& trail){
    for(int i=1;i<trail.size();i++){
        if(trail[i-1]==end && trail[i]==start){
            vector<int> frontTrail;
            if(i-1==0) frontTrail=vector<int>();
            else frontTrail=vector<int>(trail.begin(), trail.begin()+i-1);
            vector<int> backTrail=vector<int>(trail.begin()+i,trail.end());
            return trail=mergeVector(frontTrail,backTrail);
        }
    }
    return trail;
}

vector<int> getEulerTrail(const int start, const int end){
    //addEdge
    adjacent[end][start]++;
    vector<int> trail;
    getEulerCircuit(start, trail);
    for(int i=0;i<trail.size();i++){
        cout <<trail[i]<<" ";
    }
    cout <<"\n";
    vector<int> ret=removeEdge(end,start,trail);
    for(int i=0;i<ret.size();i++){
        cout << ret[i]<<" ";
    }
    cout <<"\n";
    return ret;
}

bool isHaveEulerTrailOrCircle(){
    int trailStart=0,trailEnd=0;
    for(int i=0;i<26;i++){
        int dif=outDegree[i]-inDegree[i];
        if(dif<-1 || 1<dif) return false;
        if(dif==-1) trailEnd++;
        if(dif==1) trailStart++;
    }
    return (trailStart==1 && trailEnd==1) || (trailStart==0 && trailEnd==0);
}

vector<int> getEulerCircuitOrTrail(){
    vector<int> ret;
    //trail존재
    for(int start=0;start<26;start++){
        if(outDegree[start]==inDegree[start]+1){
            for(int end=0;end<26;end++){
                if(inDegree[end]==outDegree[end]+1){
                    char a=start+'a';
                    char b=end+'a';
                    cout <<a <<" "<<b<<"\n";
                    return ret=getEulerTrail(start,end);
                }
            }
        }
    }
    //circuit존재
    for(int start=0;start<26;start++){
        if(outDegree[start]){
            getEulerCircuit(start, ret);
            return ret;
        }
    }
    return ret;
}

string getWordChain(){
    makeGraph();
    vector<int> wordChainInitial;
    string ret;
    if(!isHaveEulerTrailOrCircle()) return "IMPOSSIBLE";
    wordChainInitial=getEulerCircuitOrTrail();
    if(wordChainInitial.size()!=words.size()+1) return "IMPOSSIBLE";
    reverse(wordChainInitial.begin(),wordChainInitial.end());
    // cout <<"wordChain"<<"\n";
    // for(int i=0;i<wordChainInitial.size();i++){
    //     cout << wordChainInitial[i]<<" ";
    // }
    // cout <<"\n";
    // return " ";
    for(int i=1;i<wordChainInitial.size();i++){
        int start=wordChainInitial[i-1];
        int end=wordChainInitial[i];
        if(ret.length()) ret+=" ";
        ret+=nextString[start][end].back();
        nextString[start][end].pop_back();
    }
    return ret;
}




