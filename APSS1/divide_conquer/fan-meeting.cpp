#include <iostream>
#include <vector>
#include <string>

using namespace std;

int getHugCount(string,string);
vector<int> karatsuba(const vector<int>&, const vector<int>&);

int main(){
    int testCase;
    string members,fans;
    cin >> testCase;
    vector<int> res;
    for(int i=0;i<testCase;i++){
        cin >> members;
        cin >> fans;
        int count=getHugCount(members,fans);
        res.push_back(count);
    }
    for(int i=0;i<testCase;i++){
        cout << res[i] <<"\n";
    }
    return 0;
}

void normalize(vector<int>& a){
    a.push_back(0);
    for(int i=0;i<a.size()-1;i++){
        if(a[i]<0){
            int borrow=(abs(a[i])+9)/10;
            a[i+1]-=borrow;
            a[i]+=borrow*10;
        }
        else{
            int up=a[i]/10;
            a[i+1]+=up;
            a[i]-=up*10;
        }
    }
    while(a.size()>1 && a.back()==0) a.pop_back();
}
//a+=b*(10^k)
void addTo(vector<int>& a, vector<int>& b, int k){
    //같은 크기로 맞춰줌
    a.resize(max(a.size(),b.size()+k));
    for(int i=0;i<b.size();i++){
        a[i+k]+=b[i];
    }
    //normalize(a);
}
//a-=b (a>=b 가정)
void subFrom(vector<int>& a, vector<int>& b){
    a.resize(max(a.size(),b.size()+1));
    for(int i=0;i<b.size();i++){
        a[i]-=b[i];
    }
    //normalize(a);
}
/*
a*b=a0*b0+(a1*b0+a0*b1)*(10^(a.size()/2))+a1*b1*(10^(a.size())
z0=a0*b0
z1=a1*b1
z2=(a1*b0+a0*b1)=(a0+a1)*(b0+b1)-z0-z1
=>
a*b=z0+z2*(10*(a.size()/2))+z1*(10*(a.size())
*/
vector<int> multiply(const vector<int>& a, const vector<int>& b){
    vector<int> c(a.size()+b.size()+1,0);
    for(int i=0;i<a.size();i++){
        for(int j=0;j<b.size();j++){
            c[i+j]+=a[i]*b[j];
        }    
    }
    //normalize(c);
    return c;
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b){
    if(a.size()<b.size()) return karatsuba(b,a);
    if(a.size()==0 || b.size()==0) return vector<int>();
    if(a.size()=<100) return multiply(a,b);

    int half=a.size()/2;
    vector<int> a1(a.begin()+half, a.end());
    vector<int> a0(a.begin(),a.begin()+half);
    vector<int> b1(b.begin()+min<int>(half,b.size()),b.end());
    vector<int> b0(b.begin(), b.begin()+min<int>(half,b.size()));
    vector<int> z0=karatsuba(a0,b0);
    vector<int> z1=karatsuba(a1,b1);
    addTo(a0,a1,0);addTo(b0,b1,0);
    vector<int> z2=karatsuba(a1,b1);
    subFrom(z2,z0);subFrom(z2,z1);

    vector<int> ret;
    addTo(ret,z0,0);
    addTo(ret,z2,half);
    addTo(ret,z1,half+half);
    return ret;
}

int getHugCount(string members, string fans){
    int count=0;
    vector<int> membersBinary(members.length()),fansBinary(fans.length());
    for(int i=0;i<members.length();i++) membersBinary[i]=(members[i]=='M');
    for(int i=0;i<fans.length();i++) fansBinary[fans.length()-1-i]=(fans[i]=='M');
    vector<int> res=karatsuba(membersBinary,fansBinary);
    for(int i=membersBinary.size()-1;i<fansBinary.size();i++){
        if(res[i]==0) count++;
    }
    return count;
}