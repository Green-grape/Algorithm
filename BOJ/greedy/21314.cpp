/*
민겸 숫자는 0 이상의 정수 N에 대해 10^N 또는 5 × 10^N 꼴의 십진수를 대문자 M과 K로 이루어진 문자열로 표기한다. 
10^N 꼴의 십진수는 N + 1개의 M으로, 5 × 10^N 꼴의 십진수는 N개의 M 뒤에 1개의 K를 이어붙인 문자열로 나타낸다
민겸 수는 한 개 이상의 민겸 숫자를 이어붙여 만든다.
변환될 수 있는 십진수 중 가장 큰 값과 가장 작은 값이 궁금해졌다. 
민겸이를 위해 하나의 민겸 수가 십진수로 변환되었을 때 가질 수 있는 최댓값과 최솟값을 구해주자.
*/

#include <iostream>
#include <string>

using namespace std;

pair<string,string> getMaxMinValues(string mgNums){
    string maxValue="",minValue="";
    //maxValue
    int idx=0;
    while(idx<mgNums.length()){
        if(mgNums[idx]=='M'){
            int Mcount=0;
            while(idx<mgNums.length() && mgNums[idx]=='M'){
                Mcount++;
                idx++;
            }
            if(idx==mgNums.length()){ //모두 M
                maxValue+=(string(Mcount,'1'));
                break;
            }else{ //마지막이 K로 종료
                maxValue+=("5"+string(Mcount,'0'));
            }
        }else{
            maxValue+="5";
        }
        idx++;
    }
    idx=0;
    //minValue
    while(idx<mgNums.length()){
        if(mgNums[idx]=='M'){
            int Mcount=0;
            while(idx<mgNums.length() && mgNums[idx]=='M'){
                Mcount++;
                idx++;
            }
            if(idx==mgNums.length()){ //모두 M
                minValue+=("1"+string(Mcount-1,'0'));
                break;
            }else{ //마지막이 K로 종료
                minValue+=("1"+string(Mcount-1,'0'));
                minValue+="5";
            }
        }else{
            minValue+="5";
        }
        idx++;
    }
    return make_pair(maxValue, minValue);
}

int main(){
    string mgNums;
    cin >> mgNums;
    pair<string, string> maxMinValue=getMaxMinValues(mgNums);
    cout << maxMinValue.first <<"\n"<<maxMinValue.second <<"\n";
    return 0;
}