#include <bits/stdc++.h>
#define MOD 998244353

using namespace std;

int binpow(int,int);

int main(void)
{
	int n;
	cin>>n;
	int* inv=new int[n+1];
	vector<int> cnt(1000001,0);
	vector<vector<int>> present(n,vector<int>());
	for(int i=0;i<n;i++)
	{
		int k;
		cin >> k;
		present[i].resize(k);
		for(int j=0;j<k;j++)
		{
			cin >>present[i][j];
			cnt[present[i][j]]++;
		}
	}
	for(int i=0;i<n;i++)
	{
		inv[i]=binpow(i,MOD-2);
	}
	int ans=0;
	for(int i=0;i<n;i++)
	{
		int len=present[i].size();
		for(int j=0;j<len;j++)
		{
			ans+=((len*inv[n]%MOD)*(cnt[present[i][j]]*inv[n]%MOD))%MOD;
		}
	}
	cout<<ans<<endl;
	return 0;
}


int binpow(int x, int y)
{
	int res=1;
	while(y)
	{
		if(y & 1) res=res*x%MOD;
		x=x*x%MOD;
		y >>=1;
	}
	return res;
}
