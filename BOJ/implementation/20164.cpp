/*
석이는 짝수랑 홀수 중에서 이니셜이 같은 홀수를 더 좋아한다. 운전을 하던 호석이는 앞차의 번호판이 홀수로 가득할 때 사랑스러움을 느낄 정도이다. 전화번호도 홀수만 있고 싶다. 그렇게 홀수 홀릭에 빠진 호석이는 가지고 있는 수 N을 일련의 연산을 거치면서, 등장하는 숫자들에서 홀수를 최대한 많이 많이 보고 싶다.

하나의 수가 주어졌을 때 호석이는 한 번의 연산에서 다음과 같은 순서를 거친다.

1. 수의 각 자리 숫자 중에서 홀수의 개수를 종이에 적는다.
2. 수가 한 자리이면 더 이상 아무것도 하지 못하고 종료한다.
3. 수가 두 자리이면 2개로 나눠서 합을 구하여 새로운 수로 생각한다.
4. 수가 세 자리 이상이면 임의의 위치에서 끊어서 3개의 수로 분할하고, 3개를 더한 값을 새로운 수로 생각한다.

석이가 만들 수 있는 최종값 중에서 최솟값과 최댓값을 구하시오
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int INF=987654321;

vector<int> normalize(vector<int> n){
    for(int i=0;i<n.size();i++){
        if(n[i]>=10){
            n[i+1]+=(n[i]/10);
            n[i]%=10;
        }
        //cout <<n[i];
    }
    int end=n.size()-1;
    while(n[end]==0 && n.size()>1){
        n.pop_back();
        end--;
    }
    return n;
}

vector<int> add(vector<int> n1, vector<int> n2){ //1234=[4,3,2,1]
    if(n1.size()<n2.size()) return add(n2,n1);
    vector<int> ret=n1;
    ret.push_back(0);
    for(int i=0;i<n2.size();i++){
        ret[i]+=n2[i];
    }
    return normalize(ret);
}

pair<int,int> getOddRange(vector<int> n){
    // for(int i=n.size()-1;i>=0;i--){
    //     cout <<n[i] <<" "<<"n.size(): "<<n.size()<<"\n";
    // }
    int oddCount=0;
    for(int i=0;i<n.size();i++) if(n[i]%2) oddCount++;
    if(n.size()==1) return make_pair(oddCount,oddCount);
    vector<int> newN;
    pair<int,int> ret=make_pair(INF,-1);
    if(n.size()==2){
        newN=add(vector<int>(1, n[0]),vector<int>(1,n[1]));
        ret=getOddRange(newN);
    }
    else if(n.size()>=3){
        for(int cut1=1;cut1<n.size();cut1++){
            for(int cut2=cut1+1;cut2<n.size();cut2++){
                vector<int> n1(n.begin(),n.begin()+cut1);
                vector<int> n2(n.begin()+cut1,n.begin()+cut2);
                vector<int> n3(n.begin()+cut2,n.end());
                // cout << "n1 ";
                // for(int i=n1.size()-1;i>=0;i--) cout <<n1[i];
                // cout <<"\nn2 ";
                // for(int i=n2.size()-1;i>=0;i--) cout <<n2[i];
                // cout <<"\nn3 ";
                // for(int i=n3.size()-1;i>=0;i--) cout <<n3[i];
                // cout <<"\n";
                n1=normalize(n1);
                n2=normalize(n2);
                n3=normalize(n3);
                newN=add(n1,n2);
                newN=add(newN,n3);
                // for(int i=newN.size()-1;i>=0;i--){
                //      cout <<newN[i] <<" "<<"newN.size(): "<<newN.size()<<"\n";
                // }
                pair<int,int> tRet=getOddRange(newN);
                if(tRet.first<ret.first) ret.first=tRet.first;
                if(tRet.second>ret.second) ret.second=tRet.second;
            }
        }
    }
    ret.first+=oddCount;
    ret.second+=oddCount;
    return ret;
}

int main(){
    string strNum;
    vector<int> num;
    cin >> strNum;
    num.resize(strNum.length());
    for(int i=num.size()-1;i>=0;i--){
        num[i]=strNum[num.size()-1-i]-'0';
    }
    pair<int,int> ret=getOddRange(num);
    cout << ret.first <<" "<<ret.second<<"\n";
    return 0;
}