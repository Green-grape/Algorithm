#include <stdio.h>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    int n;
    scanf("%d", &n);
    priority_queue<int,vector<int>,greater<int>> pq;
    int num;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d", &num);
            if(pq.size()<n) pq.push(num);
            else{
                if(pq.top()<num){
                    pq.pop();
                    pq.push(num);
                }
            }
        }
    }
    int ret=pq.top();
    printf("%d\n",ret);
    return 0;
}