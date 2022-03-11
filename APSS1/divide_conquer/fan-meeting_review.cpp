#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> stringToInt(const string); //MF->10변환
int getHugCount(const vector<int>&, const vector<int>&);

int main(){
    int testCase;
    cin >> testCase;
    for(int i=0;i<testCase;i++){
        string s;
        vector<int> member,fan;
        cin >> s;
        member=stringToInt(s);
        cin >> s;
        fan=stringToInt(s);
        cout << getHugCount(member, fan) <<"\n";
    }
    return 0;
}

vector<int> stringToInt(const string s){
    vector<int> ret(s.length(),0);
    for(int i=0;i<s.length();i++){
        if(s[i]=='M') ret[i]=1;
    }
    return ret;
}

//각 자릿수가 10이상이거나 음수인 경우 처리
void normalize(vector<int>& v){
    for(int i=0;i+1<v.size();i++){
        if(v[i]<0){
            int borrow=(abs(v[i])+9)/10;
            v[i+1]-=borrow;
            v[i]+=10*borrow;
        }
        else{
            v[i+1]+=v[i]/10;
            v[i]%=10;
        }
    }
}

//a+=b*(10^k)
void addTo(vector<int>& a, const vector<int>& b,const int k){
    a.resize(max(a.size(),b.size()+k));
    for(int i=0;i<b.size();i++){
        a[i+k]+=b[i];
    }
}

//a-=b
void subFrom(vector<int>& a, const vector<int>& b){
    for(int i=0;i<b.size();i++){
        a[i]-=b[i];
    }
    normalize(a);
}

vector<int> multiply(const vector<int>& a, const vector<int>& b){
    vector<int> ret(a.size()+b.size()+1,0);
    for(int i=0;i<a.size();i++){
        for(int j=0;j<b.size();j++){
            ret[i+j]+=(a[i]*b[j]);
        }
    }
    normalize(ret);
    return ret;
}

//karatsuba 곱셈 구현
vector<int> karatsuba(const vector<int>& a, const vector<int>& b){
    //a의 크기가 더 크다고 가정
    if(a.size()<b.size()) return karatsuba(b,a);
    if(a.size()==0 || b.size()==0) return vector<int>();
    if(b.size()<=3){
        return multiply(a,b);
    }


    int half=a.size()/2;
    vector<int> a0(a.begin(),a.begin()+half);
    vector<int> a1(a.begin()+half, a.end());
    vector<int> b0(b.begin(), b.begin()+min<int>(half,b.size()));
    vector<int> b1(b.begin()+min<int>(half,b.size()), b.end());

    vector<int> z0=karatsuba(a0,b0);
    vector<int> z2=karatsuba(a1,b1);
    addTo(a0,a1,0);addTo(b0,b1,0);
    vector<int> z1=karatsuba(a0,b0);
    subFrom(z1,z0);subFrom(z1,z2);
    vector<int> ret;
    addTo(ret,z0,0);
    addTo(ret,z1,half);
    addTo(ret,z2,half+half);
    return ret;
}

int getHugCount(const vector<int>& member, const vector<int>& fan){
    vector<int> reverseFan=fan;
    reverse(reverseFan.begin(),reverseFan.end());
    vector<int> meetingResult1=karatsuba(member, reverseFan);
    vector<int> meetingResult2=multiply(member,reverseFan);
    int ret1=0,ret2=0;
    for(int i=member.size()-1;i<fan.size();i++){
        if(meetingResult1[i]==0) ret1++;
        if(meetingResult2[i]==0) ret2++;
    }
    for(int i=0;i<meetingResult1.size();i++) cout<<meetingResult1[meetingResult1.size()-1-i];
    cout <<"\n";
    for(int i=0;i<meetingResult2.size();i++) cout<<meetingResult2[meetingResult2.size()-1-i];
    cout <<"\n"<<ret2<<"\n";
    return ret1;
}