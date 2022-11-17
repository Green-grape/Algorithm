#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

//복습

map<pair<int,int>,vector<pair<int,int>>> nexts; //nexts[{i,arr[i]}]=lcs를 구성할때 arr[i]바로 뒤에 나오는 수들의 값과 위치
vector<int> prevCnt;

void makeNexts(vector<int>& arr){
    vector<pair<int,int>> ret;
    ret.reserve(arr.size());
    ret.push_back({0,arr[0]});
    for(int i=1;i<arr.size();i++){
        if(ret[ret.size()-1].second<arr[i]){
            map<pair<int,int>,vector<pair<int,int>>>::iterator it=nexts.find({ret[ret.size()-1].first,ret[ret.size()-1].second});
            if(it==nexts.end()){
                vector<pair<int,int>> next=vector<pair<int,int>>(1,{i,arr[i]});
                nexts[{ret[ret.size()-1].first,ret[ret.size()-1].second}]=next;
            }else{
                it->second.push_back({i,arr[i]});
            }
            //cout << ret[ret.size()-1].second << "->" <<arr[i]<<"\n";
            prevCnt[i]++;
            ret.push_back({i,arr[i]});
        }else if(ret[ret.size()-1].second>arr[i]){
            //이분 탐색
            int left=0,right=ret.size()-1,mid=0;
            bool isFind=false;
            while(left<=right){
                mid=(left+right)/2;
                if(ret[mid].second<arr[i]) left=mid+1;
                else if(ret[mid].second>arr[i]) right=mid-1;
                else{
                    isFind=true;
                    break;
                }
            }
            if(isFind) continue;
            int cand=mid;
            if(mid+1<ret.size() && ret[mid].second<arr[i] && arr[i]<=ret[mid+1].second){
                cand=mid+1;
            }
            if(0<cand){
                map<pair<int,int>,vector<pair<int,int>>>::iterator it=nexts.find({ret[cand-1].first,ret[cand-1].second});
                if(it==nexts.end()){
                    vector<pair<int,int>> next=vector<pair<int,int>>(1,{i,arr[i]});
                    nexts[{ret[cand-1].first,ret[cand-1].second}]=next;
                }else{
                    it->second.push_back({i,arr[i]});
                }
                //cout << ret[cand-1].second <<"->"<<arr[i]<<"\n";
                prevCnt[i]++;
            }
            ret[cand]={i,arr[i]};
        }
    }
    // for(map<pair<int,int>,vector<pair<int,int>>>::iterator it=nexts.begin();it!=nexts.end();it++){
    //     cout << it->first.first <<" "<<it->first.second<<": ";
    //     for(int i=0;i<it->second.size();i++){
    //         cout << "{" <<it->second[i].first<<" "<<it->second[i].second<<"} ";
    //     }
    //     cout <<"\n";
    // }
}

vector<int> ret;

void dfs(int cur, vector<int>& status, vector<int>& arr){
    //if(isVisit[cur]) return;
    //isVisit[cur]=true;
    map<pair<int,int>,vector<pair<int,int>>>::iterator it=nexts.find({cur,arr[cur]});
    if(it==nexts.end() || it->second.size()==0){
        if(ret.size()<status.size()) ret=status;
        return;
    }
    for(int i=0;i<it->second.size();i++){
        int next=it->second[i].first;
        status.push_back(arr[next]);
        dfs(next, status, arr);
        status.pop_back();
    }
}

vector<int> solve(vector<int>& arr){
    prevCnt=vector<int>(arr.size());
    makeNexts(arr);
    for(int i=0;i<arr.size();i++){
        if(prevCnt[i]==0){
            vector<int> status(1,arr[i]);
            dfs(i,status,arr);
        }
    }
    return ret;
}

int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    vector<int> ret=solve(arr);
    cout << ret.size() <<"\n";
    for(int i=0;i<ret.size();i++){
        printf("%d ", ret[i]);
    }
    return 0;
}