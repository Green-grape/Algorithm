#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

vector<vector<bool>> isPalindrome;

void precal(vector<int>& arr){
    //홀수 팰린드롬
    for(int i=0;i<arr.size();i++){
        int left=i,right=i;
        while(0<=left && right<arr.size()){
            if(arr[left]==arr[right]){
                isPalindrome[left][right]=true;
            }else break;
            left--;
            right++;
        }
    }
    //짝수 팰린드롬
    for(int i=0;i<arr.size()-1;i++){
        int left=i,right=i+1;
        while(0<=left && right<arr.size()){
            if(arr[left]==arr[right]){
                isPalindrome[left][right]=true;
            }else break;
            left--;
            right++;
        }
    }
}

int main(){
    int n;
    cin >> n;
    isPalindrome=vector<vector<bool>>(n, vector<bool>(n));
    vector<int> arr(n);
    for(int i=0;i<arr.size();i++){
        scanf("%d", &arr[i]);
    }
    precal(arr);
    int question;
    cin >> question;
    for(int i=0;i<question;i++){
        int start, end;
        scanf("%d %d", &start, &end);
        printf("%d\n", (int)isPalindrome[start-1][end-1]);
    }
    return 0;
}