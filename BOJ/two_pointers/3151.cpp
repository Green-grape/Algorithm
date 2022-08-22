#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> skill;

long long countSum(int left, int right, int sum){//skill이 정렬됨 가정
    long long ret=0;
    while(left<right && left>0 && right<skill.size()){
        if(skill[left]+skill[right]<sum){
            left++;
        }else if(skill[left]+skill[right]>sum){
            right--;
        }else{
            if(skill[left]==skill[right]){
                return ret=right-left+countSum(left+1,right,sum);
            }
            int leftCnt=0,rightCnt=0;
            int leftEnd=left,rightEnd=right;
            while(skill[right]==skill[rightEnd--]){
                rightCnt++;
                if(skill[right]!=skill[rightEnd]) break;
            }
            while(skill[left]==skill[leftEnd++]){
                leftCnt++;
                if(skill[left]!=skill[leftEnd]) break;
            }
            return ret=leftCnt*rightCnt+countSum(leftEnd,rightEnd,sum);
        }
    }
    return ret;
}

long long countThreeSumZero(){
    sort(skill.begin(),skill.end());
    long long ret=0;
    for(int i=0;i<skill.size()-2;i++){
        ret+=countSum(i+1,skill.size()-1,-skill[i]);
        //cout << ret <<"\n";
    }
    return ret;
}

int main(){
    int skillCount;
    scanf("%d", &skillCount);
    skill.resize(skillCount);
    for(int i=0;i<skillCount;i++) scanf("%d", &skill[i]);
    printf("%lld", countThreeSumZero());
    return 0;
}
