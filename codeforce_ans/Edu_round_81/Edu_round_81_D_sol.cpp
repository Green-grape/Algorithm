#include <bits/stdc++.h>

using namespace std;

long long get_gcd(long long,long long);
long long get_result(long long);

int main(void)
{
	int t;
	cin >>t;
	while(t--)
	{
		long long x,y;
		cin>>x>>y;
		long long G=get_gcd(x,y);
		long long res=get_result(y/G);
		cout<<res<<endl;
	}
	return 0;
}

long long get_gcd(long long x,long long y)
{
	while(x%y!=0)
	{
		long long temp=x%y;
		x=y;
		y=temp;
	}
	return y;
}

long long get_result(long long a)
{
	long long d=2;
	long long temp=a,ans=a;
	while(d*d<=temp)
	{
		int cnt=0;
		while(temp%d==0)
		{
			temp/=d;
			cnt=1;
		}
		if(cnt) ans-=ans/d;
		d++;
	}
	if(temp>1) ans-=ans/temp;
	return ans;
}
