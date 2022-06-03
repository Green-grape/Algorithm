#include <string>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <string.h>

/*
수열 S에서 최대 K번 원소를 삭제한 수열에서 
짝수로 이루어져 있는 연속한 부분 수열 중 가장 긴 길이를 구해보자.
*/

using namespace std;

const int INF=987654321;
const int MAX_N=50000;
const int MAX_DEL=100;
int n,d;
vector<int> evenStringLengths; //evenStringLength[i]=짝수로만 이루어진 i번째 부분 수열의 길이
//{1,2,3,4,5}->{2},{4}->evenStringLength[0]=1;
vector<int> cutCounts; //cutCount[i]=i~i+1번째 evenString 사이에 존재하는 홀수 개수

int getMaxEvenString(){
    if(evenStringLengths.size()==0) return 0;
    int ret=evenStringLengths[0];
    int remainCut=d,end=0;
    for(int i=0;i<cutCounts.size();i++){
        if(remainCut>=cutCounts[i]){
            ret+=evenStringLengths[i+1];
            remainCut-=cutCounts[i];
            if(i==cutCounts.size()-1) return ret; //모두 선택됨
        }else{
            end=i;
            break;
        }
    }
    int tempRet=ret,tempRemainCut=remainCut;
    for(int i=0;i<evenStringLengths.size()-1;i++){
        tempRet-=evenStringLengths[i];
        tempRemainCut+=cutCounts[i];
        int ori_tempRet=tempRet,ori_tempRetCut=tempRemainCut;
        for(int j=end;j<cutCounts.size();j++){
            if(tempRemainCut>=cutCounts[j]){
                tempRet+=evenStringLengths[j+1];
                tempRemainCut-=cutCounts[j];
            }else break;
        }
        ret=max(ret,tempRet);
        tempRet=ori_tempRet;tempRemainCut=ori_tempRetCut;
    }
    return ret;
}

int solve(vector<int>& arr){
    int evenStringLength=0,cutCount=0;
    for(int i=0;i<arr.size();i++){
        if(arr[i]%2==0){
            evenStringLength++;
            if(cutCount!=0 && evenStringLengths.size()!=0){
                cutCounts.push_back(cutCount);
            }
            cutCount=0;
        }else{
            cutCount++;
            if(evenStringLength!=0){
                evenStringLengths.push_back(evenStringLength);
                evenStringLength=0;
            }
        }
    }
    if(evenStringLength!=0) evenStringLengths.push_back(evenStringLength);
    //for(int i=0;i<evenStringLengths.size();i++) printf("%d ", evenStringLengths[i]);
    //printf("\n");
    //for(int i=0;i<cutCounts.size();i++) printf("%d ", cutCounts[i]);
    return getMaxEvenString();
}

int main(){
    scanf("%d %d", &n, &d);
    vector<int> arr(n);
    for(int i=0;i<n;i++){
       scanf("%d", &arr[i]);
    }
    printf("%d\n", solve(arr));
    return 0;
}