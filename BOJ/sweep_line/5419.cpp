#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N=75000;
int cnt[N+1];
int tree[(N+1)*4];

bool cmpY(pair<int,int> p1, pair<int,int> p2){
    return p1.second<p2.second;
}

bool cmpX(pair<int,int> p1, pair<int,int> p2){
    if(p1.first==p2.first) return p1.second>p2.second;
    return p1.first<p2.first;
}

void compressY(vector<pair<int,int>>& coords){
    sort(coords.begin(), coords.end(), cmpY);
    int temp=-1e9-1, curY=-1;
    for(int i=0;i<coords.size();i++){
        int y=coords[i].second;
        if(temp!=y){
            curY++;
            temp=y;
        }
        coords[i].second=curY;
    }
}

int getSum(int node, int left, int right, int t_left, int t_right){
    if(left>right || right<t_left || t_right<left) return 0;
    if(t_left<=left && right<=t_right) return tree[node];
    int mid=(left+right)/2;
    return getSum(node*2, left, mid, t_left, t_right)+getSum(node*2+1,mid+1,right,t_left,t_right);
}

void update(int node, int left, int right, int idx){
    if(left<=idx && idx<=right){
        tree[node]++;
        if(left!=right){
            int mid=(left+right)/2;
            update(node*2, left, mid, idx);
            update(node*2+1,mid+1,right,idx);
        }
    }
}

long long solve(vector<pair<int,int>>& coords){
    for(int i=0;i<=N;i++){
        for(int j=0;j<4;j++){
            tree[i*4+j]=0;
        }
        cnt[i]=0;
    }
    compressY(coords);
    sort(coords.begin(),coords.end(),cmpX);
    long long ret=0;
    for(int i=0;i<coords.size();i++){
        int y=coords[i].second;
        ret+=getSum(1,0,N-1,y,N-1);
        update(1,0,N-1,y);
    }
    return ret;
}

// 최대개수 주의

int main(){
    int testcase;
    cin >> testcase;
    for(int i=0;i<testcase;i++){
        int n;
        cin >> n;
        vector<pair<int,int>> coords(n);
        for(int j=0;j<coords.size();j++){
            int x,y;
            scanf("%d %d", &x, &y);
            coords[j]={x,y};
        }
        printf("%lld\n", solve(coords));
    }
    return 0;
}